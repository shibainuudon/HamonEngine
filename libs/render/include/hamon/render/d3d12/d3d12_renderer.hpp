/**
 *	@file	d3d12_renderer.hpp
 *
 *	@brief	D3D12Renderer
 */

#ifndef HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
#define HAMON_RENDER_D3D12_D3D12_RENDERER_HPP


#include <hamon/render/renderer.hpp>
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
#include <hamon/render/d3d12/input_layout.hpp>
#include <hamon/render/d3d12/pipeline_state.hpp>
#include <hamon/render/d3d12/geometry.hpp>
#include <memory>

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
		m_command_list->Close();
		m_fence             = std::make_unique<d3d12::Fence>(m_device.get(), buffer_count);

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

		m_root_signature = std::make_unique<d3d12::RootSignature>(m_device.get());
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

	void BeginRenderPass(ClearValue const& clear_value, Viewport const& viewport) override
	{
		auto const rtv_handle = m_render_target_view->GetHandle(m_frame_index);
		m_command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

		float const clear_color[] =
		{
			clear_value.color.r,
			clear_value.color.g,
			clear_value.color.b,
			clear_value.color.a,
		};
		m_command_list->ClearRenderTargetView(rtv_handle, clear_color, 0, nullptr);

		{
			::D3D12_VIEWPORT vp;
			vp.TopLeftX = viewport.left;
			vp.TopLeftY = viewport.top;
			vp.Width    = viewport.width;
			vp.Height   = viewport.height;
			vp.MinDepth = viewport.min_depth;
			vp.MaxDepth = viewport.max_depth;
			m_command_list->RSSetViewports(1, &vp);
		}

		{
			::D3D12_RECT scissor_rect;
			scissor_rect.left   = static_cast<::LONG>(viewport.left);
			scissor_rect.top    = static_cast<::LONG>(viewport.top);
			scissor_rect.right  = static_cast<::LONG>(viewport.left + viewport.width);
			scissor_rect.bottom = static_cast<::LONG>(viewport.top + viewport.height);
			m_command_list->RSSetScissorRects(1, &scissor_rect);
		}
	}

	void EndRenderPass(void) override
	{
	}

	void Render(
		Geometry const& geometry,
		std::vector<Shader> const& shaders,
		RasterizerState const& rasterizer_state,
		BlendState const& blend_state,
		DepthStencilState const& depth_stencil_state) override
	{
		std::vector<d3d12::Shader*> d3d12_shaders;
		for (auto const& shader : shaders)
		{
			auto d3d12_shader = std::make_shared<d3d12::Shader>(shader);
			m_shaders.push_back(d3d12_shader);
			d3d12_shaders.emplace_back(d3d12_shader.get());
		}

		d3d12::InputLayout input_layout(geometry.GetLayout());

		auto pipeline = std::make_shared<d3d12::PipelineState>(
			m_device.get(),
			input_layout,
			*m_root_signature.get(),
			d3d12_shaders,
			geometry.GetPrimitiveTopology(),
			rasterizer_state,
			blend_state,
			depth_stencil_state);
		m_pipeline_states.push_back(pipeline);

		m_command_list->OMSetStencilRef(depth_stencil_state.stencil.reference);
		m_command_list->SetGraphicsRootSignature(m_root_signature->Get());
		m_command_list->SetPipelineState(pipeline->Get());

		auto d3d12_geometry = std::make_shared<d3d12::Geometry>(m_device.get(), geometry);
		m_geometries.push_back(d3d12_geometry);
		d3d12_geometry->Draw(m_command_list.get());
	}

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d12::Device>				m_device;
	std::unique_ptr<d3d12::CommandQueue>		m_command_queue;
	std::vector<std::unique_ptr<d3d12::CommandAllocator>>	m_command_allocators;
	std::unique_ptr<d3d12::CommandList>			m_command_list;
	std::unique_ptr<d3d12::Fence>				m_fence;
	std::unique_ptr<d3d12::RenderTargetView>	m_render_target_view;
	std::unique_ptr<d3d12::RootSignature>		m_root_signature;
	::UINT										m_frame_index;

	std::vector<std::shared_ptr<d3d12::Shader>>	m_shaders;
	std::vector<std::shared_ptr<d3d12::PipelineState>>	m_pipeline_states;
	std::vector<std::shared_ptr<d3d12::Geometry>>	m_geometries;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
