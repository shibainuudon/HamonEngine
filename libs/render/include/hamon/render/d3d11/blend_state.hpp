/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_D3D11_BLEND_STATE_HPP
#define HAMON_RENDER_D3D11_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d11/blend_factor.hpp>
#include <hamon/render/d3d11/blend_operation.hpp>
#include <hamon/render/d3d11/logic_operation.hpp>
#include <hamon/render/d3d11/color_write_mask.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_BLEND_DESC1 BlendState(render::BlendState const& state)
{
	::D3D11_BLEND_DESC1	desc{};
	desc.AlphaToCoverageEnable = FALSE;
	desc.IndependentBlendEnable = state.independent_blend_enable;
	for (std::size_t i = 0; i < std::ranges::size(state.render_target); ++i)
	{
		auto& rt = desc.RenderTarget[i];
		auto const& s = state.render_target[i];
		rt.BlendEnable           = s.blend_enable;
		rt.SrcBlend              = d3d11::BlendFactor(s.color_src_factor);
		rt.DestBlend             = d3d11::BlendFactor(s.color_dest_factor);
		rt.BlendOp               = d3d11::BlendOperation(s.color_operation);
		rt.SrcBlendAlpha         = d3d11::BlendFactor(s.alpha_src_factor);
		rt.DestBlendAlpha        = d3d11::BlendFactor(s.alpha_dest_factor);
		rt.BlendOpAlpha          = d3d11::BlendOperation(s.alpha_operation);

		rt.RenderTargetWriteMask = d3d11::ColorWriteMask(s.color_write_mask);

		// LogicOpは全て同じ
		rt.LogicOpEnable         = state.logic_op_enable;
		rt.LogicOp               = d3d11::LogicOperation(state.logic_operation);
	}

	return desc;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_BLEND_STATE_HPP
