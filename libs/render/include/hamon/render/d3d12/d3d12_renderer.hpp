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
			::D3D12_RECT scissor_rect;
			scissor_rect.left   = static_cast<::LONG>(render_pass_state.viewport.left);
			scissor_rect.top    = static_cast<::LONG>(render_pass_state.viewport.top);
			scissor_rect.right  = static_cast<::LONG>(render_pass_state.viewport.left + render_pass_state.viewport.width);
			scissor_rect.bottom = static_cast<::LONG>(render_pass_state.viewport.top  + render_pass_state.viewport.height);
			m_command_list->RSSetScissorRects(1, &scissor_rect);
		}
	}

	void EndRenderPass(void) override
	{
	}

private:
	template <typename T, typename Map, typename Id, typename... Args>
	typename Map::mapped_type
	GetOrCreate(Map& map, Id const& id, Args&&... args)
	{
		auto it = map.find(id);
		if (it != map.end())
		{
			return it->second;
		}
		else
		{
			auto p = std::make_shared<T>(std::forward<Args>(args)...);
			map[id] = p;
			return p;
		}
	}

public:
	void Render(
		Geometry const& geometry,
		Program const& program,
		Uniforms const& /*uniforms*/,
		RenderState const& render_state) override
	{
		auto d3d12_geometry = GetOrCreate<d3d12::Geometry>(
			m_geometry_map, geometry.GetID(), m_device.get(), geometry);
		auto d3d12_program = GetOrCreate<d3d12::Program>(
			m_program_map, program.GetID(), program);

		d3d12::InputLayout input_layout(geometry.GetLayout());

		auto id = render::detail::HashCombine(
			geometry.GetID(),
			program.GetID(),
			render_state.rasterizer_state,
			render_state.blend_state,
			render_state.depth_stencil_state);
		auto d3d12_pipeline = GetOrCreate<d3d12::PipelineState>(
			m_pipeline_state_map,
			id,
			m_device.get(),
			input_layout,
			*m_root_signature,
			*d3d12_program,
			geometry.GetPrimitiveTopology(),
			render_state.rasterizer_state,
			render_state.blend_state,
			render_state.depth_stencil_state);

		m_command_list->OMSetStencilRef(render_state.depth_stencil_state.stencil.reference);
		m_command_list->SetGraphicsRootSignature(m_root_signature->Get());
		m_command_list->SetPipelineState(d3d12_pipeline->Get());

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

	std::unordered_map<detail::Identifier, std::shared_ptr<d3d12::Program>>		m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d12::Geometry>>	m_geometry_map;
	std::unordered_map<std::size_t, std::shared_ptr<d3d12::PipelineState>>		m_pipeline_state_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
