/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_D3D11_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_D3D11_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/depth_stencil_state.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d11/comparison_func.hpp>
#include <hamon/render/d3d11/stencil_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_DEPTH_STENCIL_DESC DepthStencilState(render::DepthStencilState const& state)
{
	::D3D11_DEPTH_STENCIL_DESC desc{};
	desc.DepthEnable                  = state.depth.enable;
	desc.DepthWriteMask               = state.depth.write ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc                    = d3d11::ComparisonFunc(state.depth.func);
	desc.StencilEnable                = state.stencil.enable;
	desc.StencilReadMask              = state.stencil.read_mask;
	desc.StencilWriteMask             = state.stencil.write_mask;
	desc.FrontFace.StencilFailOp      = d3d11::StencilOperation(state.stencil.fail_operation);
	desc.FrontFace.StencilDepthFailOp = d3d11::StencilOperation(state.stencil.depth_fail_operation);
	desc.FrontFace.StencilPassOp      = d3d11::StencilOperation(state.stencil.pass_operation);
	desc.FrontFace.StencilFunc        = d3d11::ComparisonFunc(state.stencil.func);
		
	// FrontとBackのStencil設定を同じにする
	desc.BackFace = desc.FrontFace;
	
	return desc;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_DEPTH_STENCIL_STATE_HPP
