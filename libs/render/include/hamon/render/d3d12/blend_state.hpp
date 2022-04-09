/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_D3D12_BLEND_STATE_HPP
#define HAMON_RENDER_D3D12_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/blend_factor.hpp>
#include <hamon/render/d3d12/blend_operation.hpp>
#include <hamon/render/d3d12/logic_operation.hpp>
#include <hamon/render/d3d12/color_write_mask.hpp>

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
	desc.IndependentBlendEnable = FALSE;
	for (auto& rt : desc.RenderTarget)
	{
		rt.BlendEnable           = blend_state.blend_enable;
		rt.SrcBlend              = d3d12::BlendFactor(blend_state.color_src_factor);
		rt.DestBlend             = d3d12::BlendFactor(blend_state.color_dest_factor);
		rt.BlendOp               = d3d12::BlendOperation(blend_state.color_operation);
		rt.SrcBlendAlpha         = d3d12::BlendFactor(blend_state.alpha_src_factor);
		rt.DestBlendAlpha        = d3d12::BlendFactor(blend_state.alpha_dest_factor);
		rt.BlendOpAlpha          = d3d12::BlendOperation(blend_state.alpha_operation);

		rt.LogicOpEnable         = blend_state.logic_op_enable;
		rt.LogicOp               = d3d12::LogicOperation(blend_state.logic_operation);
			
		rt.RenderTargetWriteMask = d3d12::ColorWriteMask(blend_state.color_write_mask);
	}

	return desc;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_BLEND_STATE_HPP
