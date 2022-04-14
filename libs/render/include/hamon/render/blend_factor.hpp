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
    OneMinusSrcColor,
    DstColor,
    OneMinusDstColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha,
    SrcAlphaSaturate,
    Src1Color,
    OneMinusSrc1Color,
    Src1Alpha,
    OneMinusSrc1Alpha,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_BLEND_FACTOR_HPP
