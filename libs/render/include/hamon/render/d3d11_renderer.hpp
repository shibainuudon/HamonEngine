/**
 *	@file	d3d11_renderer.hpp
 *
 *	@brief	D3D11Renderer
 */

#ifndef HAMON_RENDER_D3D11_RENDERER_HPP
#define HAMON_RENDER_D3D11_RENDERER_HPP

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
	explicit D3D11Renderer(Window const& window);
	~D3D11Renderer();

	void Begin(void) override;
	void End(void) override;

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d11::Device>				m_device;
	std::unique_ptr<d3d11::DeviceContext>		m_device_context;
	std::unique_ptr<d3d11::RenderTargetView>	m_render_target_view;
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/d3d11/d3d11_renderer_inl.hpp>

#endif // HAMON_RENDER_D3D11_RENDERER_HPP
