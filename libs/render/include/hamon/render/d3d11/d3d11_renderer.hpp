/**
 *	@file	d3d11_renderer.hpp
 *
 *	@brief	D3D11Renderer
 */

#ifndef HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
#define HAMON_RENDER_D3D11_D3D11_RENDERER_HPP

#include <hamon/render/renderer.hpp>
#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/render_target_view.hpp>
#include <memory>

namespace hamon
{

class Window;

inline namespace render
{

class D3D11Renderer : public Renderer
{
public:
	explicit D3D11Renderer(Window const& window)
	{
		m_factory = std::make_unique<DXGIFactory>();
		m_device = std::make_unique<d3d11::Device>(m_factory->EnumAdapters());
		m_device_context = std::make_unique<d3d11::DeviceContext>(m_device->GetImmediateContext());

		::UINT const buffer_count = 2;	// TODO
		::UINT const width  = window.GetClientWidth();
		::UINT const height = window.GetClientHeight();
		::HWND const hwnd   = window.GetNativeHandle();

		m_swap_chain = std::make_unique<DXGISwapChain>(
			m_factory.get(), m_device->Get(), buffer_count, width, height, hwnd);

		m_factory->MakeWindowAssociation(
			hwnd,
			DXGI_MWA_NO_WINDOW_CHANGES |
			DXGI_MWA_NO_ALT_ENTER |
			DXGI_MWA_NO_PRINT_SCREEN);

		m_render_target_view = std::make_unique<d3d11::RenderTargetView>(m_device.get(), m_swap_chain.get());
	}

	~D3D11Renderer()
	{
		m_device_context->ClearState();
	}

	void Begin(void) override
	{
	}

	void End(void) override
	{
		m_swap_chain->Present(1, 0);
	}

	void BeginRenderPass(ClearValue const& clear_value) override
	{
		float const clear_color[] =
		{
			clear_value.r,
			clear_value.g,
			clear_value.b,
			clear_value.a,
		};
		m_device_context->ClearRenderTargetView(
			m_render_target_view->Get(),
			clear_color);
	}

	void EndRenderPass(void) override
	{
	}

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d11::Device>				m_device;
	std::unique_ptr<d3d11::DeviceContext>		m_device_context;
	std::unique_ptr<d3d11::RenderTargetView>	m_render_target_view;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
