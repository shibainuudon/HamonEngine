/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor
 */

#ifndef HAMON_RENDER_D3D11_BLEND_FACTOR_HPP
#define HAMON_RENDER_D3D11_BLEND_FACTOR_HPP

#include <hamon/render/blend_factor.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_BLEND BlendFactor(render::BlendFactor factor)
{
	switch (factor)
	{
	case render::BlendFactor::Zero:					return D3D11_BLEND_ZERO;
	case render::BlendFactor::One:					return D3D11_BLEND_ONE;
	case render::BlendFactor::SrcColor:				return D3D11_BLEND_SRC_COLOR;
	case render::BlendFactor::OneMinusSrcColor:		return D3D11_BLEND_INV_SRC_COLOR;
	case render::BlendFactor::DstColor:				return D3D11_BLEND_DEST_COLOR;
	case render::BlendFactor::OneMinusDstColor:		return D3D11_BLEND_INV_DEST_COLOR;
	case render::BlendFactor::SrcAlpha:				return D3D11_BLEND_SRC_ALPHA;
	case render::BlendFactor::OneMinusSrcAlpha:		return D3D11_BLEND_INV_SRC_ALPHA;
	case render::BlendFactor::DstAlpha:				return D3D11_BLEND_DEST_ALPHA;
	case render::BlendFactor::OneMinusDstAlpha:		return D3D11_BLEND_INV_DEST_ALPHA;
	case render::BlendFactor::ConstantColor:		return D3D11_BLEND_BLEND_FACTOR;
	case render::BlendFactor::OneMinusConstantColor:return D3D11_BLEND_INV_BLEND_FACTOR;
	case render::BlendFactor::ConstantAlpha:		return D3D11_BLEND_BLEND_FACTOR;
	case render::BlendFactor::OneMinusConstantAlpha:return D3D11_BLEND_INV_BLEND_FACTOR;
	case render::BlendFactor::SrcAlphaSaturate:		return D3D11_BLEND_SRC_ALPHA_SAT;
	case render::BlendFactor::Src1Color:			return D3D11_BLEND_SRC1_COLOR;
	case render::BlendFactor::OneMinusSrc1Color:	return D3D11_BLEND_INV_SRC1_COLOR;
	case render::BlendFactor::Src1Alpha:			return D3D11_BLEND_SRC1_ALPHA;
	case render::BlendFactor::OneMinusSrc1Alpha:	return D3D11_BLEND_INV_SRC1_ALPHA;
	}
	return D3D11_BLEND_ZERO;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_BLEND_FACTOR_HPP
