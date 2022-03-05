/**
 *	@file	d3d11_renderer_inl.hpp
 *
 *	@brief	D3D11Renderer
 */

#ifndef HAMON_RENDER_D3D11_D3D11_RENDERER_INL_HPP
#define HAMON_RENDER_D3D11_D3D11_RENDERER_INL_HPP

#include <memory>

namespace hamon
{

inline namespace render
{

inline
D3D11Renderer::D3D11Renderer(Window const& window)
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

inline
D3D11Renderer::~D3D11Renderer()
{
	m_device_context->ClearState();
}

inline void
D3D11Renderer::Begin(void)
{
	float clear_color[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	m_device_context->ClearRenderTargetView(
		m_render_target_view->Get(),
		clear_color);
}

inline void
D3D11Renderer::End(void)
{
	m_swap_chain->Present(1, 0);
}

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_D3D11_RENDERER_INL_HPP
