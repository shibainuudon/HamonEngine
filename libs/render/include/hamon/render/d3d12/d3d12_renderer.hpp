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
		m_command_allocator = std::make_unique<d3d12::CommandAllocator>(m_device.get());
		m_command_list      = std::make_unique<d3d12::CommandList>(m_device.get(), m_command_allocator.get());
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
	}

	~D3D12Renderer()
	{
		m_fence->WaitForGpu(m_command_queue.get(), m_frame_index);
		m_fence->Close();
	}

	void Begin(void) override
	{
		m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();
		m_command_allocator->Reset();
		m_command_list->Reset(m_command_allocator.get());

		ComPtr<::ID3D12Resource2> resource;
		m_swap_chain->GetBuffer(m_frame_index, IID_PPV_ARGS(&resource));
		m_command_list->ResourceBarrier(
			resource.Get(),
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);
	}

	void End(void) override
	{
		ComPtr<::ID3D12Resource2> resource;
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

	void BeginRenderPass(ClearValue const& clear_value, Viewport const& /*viewport*/) override
	{
		auto const rtv_handle = m_render_target_view->GetHandle(m_frame_index);
		m_command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

		float const clear_color[] =
		{
			clear_value.r,
			clear_value.g,
			clear_value.b,
			clear_value.a,
		};
		m_command_list->ClearRenderTargetView(rtv_handle, clear_color, 0, nullptr);
	}

	void EndRenderPass(void) override
	{
	}

	void Render(
		Geometry const& geometry,
		std::vector<Shader> const& shaders,
		RasterizerState const& rasterizer_state) override
	{
		(void)geometry;
		(void)shaders;
		(void)rasterizer_state;
	}

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d12::Device>				m_device;
	std::unique_ptr<d3d12::CommandQueue>		m_command_queue;
	std::unique_ptr<d3d12::CommandAllocator>	m_command_allocator;
	std::unique_ptr<d3d12::CommandList>			m_command_list;
	std::unique_ptr<d3d12::Fence>				m_fence;
	std::unique_ptr<d3d12::RenderTargetView>	m_render_target_view;
	::UINT										m_frame_index;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_D3D12_RENDERER_HPP
