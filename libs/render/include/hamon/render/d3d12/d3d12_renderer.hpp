/**
 *	@file	d3d12_renderer.hpp
 *
 *	@brief	D3D12Renderer
 */

#ifndef HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
#define HAMON_RENDER_D3D12_D3D12_RENDERER_HPP

#include <hamon/render/renderer.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/render_pass_state.hpp>
#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_queue.hpp>
#include <hamon/render/d3d12/command_allocator.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d12/fence.hpp>
#include <hamon/render/d3d12/render_target_view.hpp>
#include <hamon/render/d3d12/root_signature.hpp>
#include <hamon/render/d3d12/shader.hpp>
#include <hamon/render/d3d12/program.hpp>
#include <hamon/render/d3d12/input_layout.hpp>
#include <hamon/render/d3d12/pipeline_state.hpp>
#include <hamon/render/d3d12/geometry.hpp>
#include <hamon/render/d3d12/descriptor_heap.hpp>
#include <memory>
#include <unordered_map>

namespace hamon
{

class Window;

inline namespace render
{

class D3D12Renderer : public Renderer
{
public:
	explicit D3D12Renderer(Window const& window)
	{
#if defined(_DEBUG)
		// Enable the debug layer (requires the Graphics Tools "optional feature").
		// NOTE: Enabling the debug layer after device creation will invalidate the active device.
		{
			ComPtr<::ID3D12Debug> debug;
			if (SUCCEEDED(::D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
			{
				debug->EnableDebugLayer();
			}
		}
#endif

		::UINT const buffer_count = 2;	// TODO
		::UINT const width  = window.GetClientWidth();
		::UINT const height = window.GetClientHeight();
		::HWND const hwnd   = window.GetNativeHandle();

		m_factory           = std::make_unique<DXGIFactory>();
		m_device            = std::make_unique<d3d12::Device>(m_factory->EnumAdapters());
		m_command_queue     = std::make_unique<d3d12::CommandQueue>(m_device.get());
		for (::UINT i = 0; i < buffer_count; ++i)
		{
			m_command_allocators.push_back(std::make_unique<d3d12::CommandAllocator>(m_device.get()));
		}
		m_command_list      = std::make_unique<d3d12::CommandList>(m_device.get(), m_command_allocators[0].get());
		m_fence             = std::make_unique<d3d12::Fence>(m_device.get(), buffer_count);

		m_command_list->Close();

		m_resource_map = std::make_unique<d3d12::ResourceMap>(m_device.get());

		m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV] =
			std::make_unique<d3d12::DescriptorHeap>(
				m_device.get(),
				D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				100,
				D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

		m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER] =
			std::make_unique<d3d12::DescriptorHeap>(
				m_device.get(),
				D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
				100,
				D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

		m_swap_chain = std::make_unique<DXGISwapChain>(
			m_factory.get(), m_command_queue->Get(), buffer_count, width, height, hwnd);
		m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();

		m_factory->MakeWindowAssociation(
			hwnd,
			DXGI_MWA_NO_WINDOW_CHANGES |
			DXGI_MWA_NO_ALT_ENTER |
			DXGI_MWA_NO_PRINT_SCREEN);

		m_fence->WaitForGpu(m_command_queue.get(), m_frame_index);

		m_render_target_view = std::make_unique<d3d12::RenderTargetView>(m_device.get(), m_swap_chain.get());

		m_constant_buffer =
			std::make_unique<d3d12::ConstantBuffer>(
				m_device.get(),
				1024 * 1024);	// TODO
	}

	~D3D12Renderer()
	{
		m_fence->WaitForGpu(m_command_queue.get(), m_frame_index);
		m_fence->Close();
	}

	void Begin(void) override
	{
		m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();
		m_command_allocators[m_frame_index]->Reset();
		m_command_list->Reset(m_command_allocators[m_frame_index].get());

		ComPtr<::ID3D12Resource1> resource;
		m_swap_chain->GetBuffer(m_frame_index, IID_PPV_ARGS(&resource));
		m_command_list->ResourceBarrier(
			resource.Get(),
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);

		std::vector<::ID3D12DescriptorHeap*> heaps;
		for (auto& descriptor_heap : m_descriptor_heaps)
		{
			if (descriptor_heap)
			{
				descriptor_heap->Reset();
				heaps.push_back(descriptor_heap->Get());
			}
		}
		m_command_list->SetDescriptorHeaps(
			static_cast<::UINT>(heaps.size()),
			heaps.data());

		m_constant_buffer->Reset();
	}

	void End(void) override
	{
		ComPtr<::ID3D12Resource1> resource;
		m_swap_chain->GetBuffer(m_frame_index, IID_PPV_ARGS(&resource));
		m_command_list->ResourceBarrier(
			resource.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT);
		m_command_list->Close();
		m_command_queue->ExecuteCommandList(m_command_list.get());
		m_swap_chain->Present(1, 0);
		m_fence->MoveToNextFrame(m_command_queue.get(), m_frame_index);
	}

	void BeginRenderPass(RenderPassState const& render_pass_state) override
	{
		auto const rtv_handle = m_render_target_view->GetHandle(m_frame_index);
		m_command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

		float const clear_color[] =
		{
			render_pass_state.clear_value.color.r,
			render_pass_state.clear_value.color.g,
			render_pass_state.clear_value.color.b,
			render_pass_state.clear_value.color.a,
		};
		m_command_list->ClearRenderTargetView(rtv_handle, clear_color, 0, nullptr);

		{
			::D3D12_VIEWPORT vp;
			vp.TopLeftX = render_pass_state.viewport.left;
			vp.TopLeftY = render_pass_state.viewport.top;
			vp.Width    = render_pass_state.viewport.width;
			vp.Height   = render_pass_state.viewport.height;
			vp.MinDepth = render_pass_state.viewport.min_depth;
			vp.MaxDepth = render_pass_state.viewport.max_depth;
			m_command_list->RSSetViewports(1, &vp);
		}

		{
			::D3D12_RECT rect;
			if (render_pass_state.scissor.enable)
			{
				rect.left   = static_cast<::LONG>(render_pass_state.scissor.left);
				rect.top    = static_cast<::LONG>(render_pass_state.scissor.top);
				rect.right  = static_cast<::LONG>(render_pass_state.scissor.left + render_pass_state.scissor.width);
				rect.bottom = static_cast<::LONG>(render_pass_state.scissor.top  + render_pass_state.scissor.height);
			}
			else
			{
				rect.left   = 0;
				rect.top    = 0;
				rect.right  = static_cast<::LONG>(render_pass_state.viewport.width);
				rect.bottom = static_cast<::LONG>(render_pass_state.viewport.height);
			}
			m_command_list->RSSetScissorRects(1, &rect);
		}
	}

	void EndRenderPass(void) override
	{
	}

	void Render(
		Geometry const& geometry,
		Program const& program,
		Uniforms const& uniforms,
		RenderState const& render_state) override
	{
		auto d3d12_geometry = m_resource_map->GetGeometry(m_device.get(), geometry);
		auto d3d12_program = m_resource_map->GetProgram(m_device.get(), program);

		d3d12::InputLayout input_layout(geometry.GetLayout());

		auto d3d12_pipeline = m_resource_map->GetPipelineState(
			m_device.get(), geometry, program, render_state);


		m_command_list->OMSetStencilRef(render_state.depth_stencil_state.stencil.reference);
		{
			float const blend_factor[]
			{
				render_state.blend_state.constant_color.r,
				render_state.blend_state.constant_color.g,
				render_state.blend_state.constant_color.b,
				render_state.blend_state.constant_color.a,
			};
			m_command_list->OMSetBlendFactor(blend_factor);
		}
		m_command_list->SetGraphicsRootSignature(d3d12_program->GetRootSignature());
		m_command_list->SetPipelineState(d3d12_pipeline->Get());

		{
			auto const& descriptor_heap_types = d3d12_program->GetDescriptorHeapTypes();
			auto const& root_parameters = d3d12_program->GetRootParameters();
			for (std::size_t i = 0; i < root_parameters.size(); ++i)
			{
				auto const descriptor_heap_type = descriptor_heap_types[i];
				auto& descriptor_heap = m_descriptor_heaps[descriptor_heap_type];
				m_command_list->SetGraphicsRootDescriptorTable(
					static_cast<::UINT>(i),
					descriptor_heap->AssignGpuDescriptorHandle());
			}
		}

		d3d12_program->LoadUniforms(
			m_device.get(),
			m_resource_map.get(),
			m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV].get(),
			m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER].get(),
			m_constant_buffer.get(),
			uniforms);
		d3d12_geometry->Draw(m_command_list.get());
	}

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d12::Device>				m_device;
	std::unique_ptr<d3d12::CommandQueue>		m_command_queue;
	std::vector<std::unique_ptr<d3d12::CommandAllocator>>	m_command_allocators;
	std::unique_ptr<d3d12::CommandList>			m_command_list;
	std::unique_ptr<d3d12::DescriptorHeap>		m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	std::unique_ptr<d3d12::Fence>				m_fence;
	std::unique_ptr<d3d12::RenderTargetView>	m_render_target_view;
	::UINT										m_frame_index;
	std::unique_ptr<d3d12::ConstantBuffer>		m_constant_buffer;
	std::unique_ptr<d3d12::ResourceMap>			m_resource_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
