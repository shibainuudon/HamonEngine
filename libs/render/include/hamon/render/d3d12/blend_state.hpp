/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_D3D12_BLEND_STATE_HPP
#define HAMON_RENDER_D3D12_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/d3d12/blend_factor.hpp>
#include <hamon/render/d3d12/blend_operation.hpp>
#include <hamon/render/d3d12/logic_operation.hpp>
#include <hamon/render/d3d12/color_write_mask.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_BLEND_DESC BlendState(render::BlendState const& blend_state)
{
	::D3D12_BLEND_DESC desc{};
	desc.AlphaToCoverageEnable  = FALSE;
	desc.IndependentBlendEnable = blend_state.independent_blend_enable;
	for (std::size_t i = 0; i < std::ranges::size(blend_state.render_target); ++i)
	{
		auto& rt = desc.RenderTarget[i];
		auto const& s = blend_state.render_target[i];
		rt.BlendEnable           = s.blend_enable;
		rt.SrcBlend              = d3d12::BlendFactor(s.color_src_factor);
		rt.DestBlend             = d3d12::BlendFactor(s.color_dest_factor);
		rt.BlendOp               = d3d12::BlendOperation(s.color_operation);
		rt.SrcBlendAlpha         = d3d12::BlendFactor(s.alpha_src_factor);
		rt.DestBlendAlpha        = d3d12::BlendFactor(s.alpha_dest_factor);
		rt.BlendOpAlpha          = d3d12::BlendOperation(s.alpha_operation);

		rt.RenderTargetWriteMask = d3d12::ColorWriteMask(s.color_write_mask);

		// LogicOpは全て同じ
		rt.LogicOpEnable         = blend_state.logic_op_enable;
		rt.LogicOp               = d3d12::LogicOperation(blend_state.logic_operation);
	}

	return desc;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_BLEND_STATE_HPP
