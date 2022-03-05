/**
 *	@file	device_context.hpp
 *
 *	@brief	DeviceContext
 */

#ifndef HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP
#define HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class DeviceContext
{
public:
	explicit DeviceContext(ComPtr<ID3D11DeviceContext4> device_context)
		: m_device_context(device_context)
	{
	}

	void ClearState(void)
	{
		m_device_context->ClearState();
	}

	void ClearRenderTargetView(
		::ID3D11RenderTargetView* render_target_view,
		::FLOAT const* color_rgba)
	{
		m_device_context->ClearRenderTargetView(render_target_view, color_rgba);
	}

private:
	ComPtr<ID3D11DeviceContext4>	m_device_context;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP
