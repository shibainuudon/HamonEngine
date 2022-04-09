/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP
#define HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/fill_mode.hpp>
#include <hamon/render/d3d12/cull_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_RASTERIZER_DESC
RasterizerState(render::RasterizerState const& rasterizer_state)
{
	::D3D12_RASTERIZER_DESC	desc{};
	desc.FillMode              = d3d12::FillMode(rasterizer_state.fill_mode);
	desc.CullMode              = d3d12::CullMode(rasterizer_state.cull_mode);
	desc.FrontCounterClockwise = rasterizer_state.front_face == FrontFace::CounterClockwise;
	desc.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
	desc.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	desc.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	desc.DepthClipEnable       = TRUE;
	desc.MultisampleEnable     = FALSE;
	desc.AntialiasedLineEnable = FALSE;
	desc.ForcedSampleCount     = 0;
	desc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return desc;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP
