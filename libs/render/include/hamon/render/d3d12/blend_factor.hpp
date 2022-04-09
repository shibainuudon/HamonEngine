/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor
 */

#ifndef HAMON_RENDER_D3D12_BLEND_FACTOR_HPP
#define HAMON_RENDER_D3D12_BLEND_FACTOR_HPP

#include <hamon/render/blend_factor.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_BLEND BlendFactor(render::BlendFactor factor)
{
	switch (factor)
	{
	case render::BlendFactor::Zero:				return D3D12_BLEND_ZERO;
	case render::BlendFactor::One:				return D3D12_BLEND_ONE;
	case render::BlendFactor::SrcColor:			return D3D12_BLEND_SRC_COLOR;
	case render::BlendFactor::InvSrcColor:		return D3D12_BLEND_INV_SRC_COLOR;
	case render::BlendFactor::SrcAlpha:			return D3D12_BLEND_SRC_ALPHA;
	case render::BlendFactor::InvSrcAlpha:		return D3D12_BLEND_INV_SRC_ALPHA;
	case render::BlendFactor::DestAlpha:		return D3D12_BLEND_DEST_ALPHA;
	case render::BlendFactor::InvDestAlpha:		return D3D12_BLEND_INV_DEST_ALPHA;
	case render::BlendFactor::DestColor:		return D3D12_BLEND_DEST_COLOR;
	case render::BlendFactor::InvDestColor:		return D3D12_BLEND_INV_DEST_COLOR;
	case render::BlendFactor::SrcAlphaSat:		return D3D12_BLEND_SRC_ALPHA_SAT;
	case render::BlendFactor::BlendFactor:		return D3D12_BLEND_BLEND_FACTOR;
	case render::BlendFactor::InvBlendFactor:	return D3D12_BLEND_INV_BLEND_FACTOR;
	case render::BlendFactor::Src1Color:		return D3D12_BLEND_SRC1_COLOR;
	case render::BlendFactor::InvSrc1Color:		return D3D12_BLEND_INV_SRC1_COLOR;
	case render::BlendFactor::Src1Alpha:		return D3D12_BLEND_SRC1_ALPHA;
	case render::BlendFactor::InvSrc1Alpha:		return D3D12_BLEND_INV_SRC1_ALPHA;
	}
	return D3D12_BLEND_ZERO;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_BLEND_FACTOR_HPP
