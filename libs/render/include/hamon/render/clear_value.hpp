/**
 *	@file	clear_value.hpp
 *
 *	@brief	ClearValue
 */

#ifndef HAMON_RENDER_CLEAR_VALUE_HPP
#define HAMON_RENDER_CLEAR_VALUE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

struct ClearValue
{
	float         r;
	float         g;
	float         b;
	float         a;
	float         depth;
	std::uint32_t stencil;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_CLEAR_VALUE_HPP
