/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor
 */

#ifndef HAMON_RENDER_BLEND_FACTOR_HPP
#define HAMON_RENDER_BLEND_FACTOR_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class BlendFactor : std::uint32_t
{
	Zero,
	One,
	SrcColor,
	InvSrcColor,
	SrcAlpha,
	InvSrcAlpha,
	DestAlpha,
	InvDestAlpha,
	DestColor,
	InvDestColor,
	SrcAlphaSat,
	BlendFactor,
	InvBlendFactor,
	Src1Color,
	InvSrc1Color,
	Src1Alpha,
	InvSrc1Alpha,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_BLEND_FACTOR_HPP
