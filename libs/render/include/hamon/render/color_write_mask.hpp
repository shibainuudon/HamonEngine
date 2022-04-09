/**
 *	@file	color_write_mask.hpp
 *
 *	@brief	ColorWriteMask
 */

#ifndef HAMON_RENDER_COLOR_WRITE_MASK_HPP
#define HAMON_RENDER_COLOR_WRITE_MASK_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum ColorWriteMask : std::uint32_t
{
	Red   = (1 << 0),
	Green = (1 << 1),
	Blue  = (1 << 2),
	Alpha = (1 << 3),
	All   = (Red | Green | Blue | Alpha),
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_COLOR_WRITE_MASK_HPP
