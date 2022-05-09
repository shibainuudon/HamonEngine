/**
 *	@file	render_target_view.hpp
 *
 *	@brief	RenderTargetView
 */

#ifndef HAMON_RENDER_D3D11_RENDER_TARGET_VIEW_HPP
#define HAMON_RENDER_D3D11_RENDER_TARGET_VIEW_HPP

#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class RenderTargetView
{
public:
	explicit RenderTargetView(d3d11::Device* device, DXGISwapChain* swap_chain)
	{
		ComPtr<::ID3D11Texture2D> back_buffer;
		swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));

		m_render_target_view = device->CreateRenderTargetView(
			back_buffer.Get(),
			nullptr);
	}

	::ID3D11RenderTargetView1* Get(void) const
	{
		return m_render_target_view.Get();
	}

private:
	ComPtr<::ID3D11RenderTargetView1>	m_render_target_view;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_RENDER_TARGET_VIEW_HPP
