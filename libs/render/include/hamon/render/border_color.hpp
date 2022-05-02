/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor
 */

#ifndef HAMON_RENDER_BORDER_COLOR_HPP
#define HAMON_RENDER_BORDER_COLOR_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class BorderColor : std::uint32_t
{
	TransparentBlack,
	OpaqueBlack,
	OpaqueWhite,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_BORDER_COLOR_HPP
