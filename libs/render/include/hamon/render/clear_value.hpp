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
	struct
	{
		float         r;
		float         g;
		float         b;
		float         a;
	}				color{0, 0, 0, 0};
	float			depth{1.0f};
	std::uint8_t	stencil{0};
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_CLEAR_VALUE_HPP
