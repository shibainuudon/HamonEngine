/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_D3D11_RASTERIZER_STATE_HPP
#define HAMON_RENDER_D3D11_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d11/fill_mode.hpp>
#include <hamon/render/d3d11/cull_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_RASTERIZER_DESC RasterizerState(render::RasterizerState const& state)
{
	::D3D11_RASTERIZER_DESC	desc{};
	desc.FillMode              = d3d11::FillMode(state.fill_mode);
	desc.CullMode              = d3d11::CullMode(state.cull_mode);
	desc.FrontCounterClockwise = (state.front_face == FrontFace::CounterClockwise);
	desc.DepthBias             = D3D11_DEFAULT_DEPTH_BIAS;
	desc.DepthBiasClamp        = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	desc.SlopeScaledDepthBias  = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	desc.DepthClipEnable       = FALSE;
	desc.ScissorEnable         = FALSE;
	desc.MultisampleEnable     = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	return desc;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_RASTERIZER_STATE_HPP
