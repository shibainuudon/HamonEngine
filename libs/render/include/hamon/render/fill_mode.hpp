/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode
 */

#ifndef HAMON_RENDER_FILL_MODE_HPP
#define HAMON_RENDER_FILL_MODE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class FillMode : std::uint32_t
{
	Solid,
	Wireframe,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_FILL_MODE_HPP
