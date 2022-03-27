/**
 *	@file	viewport.hpp
 *
 *	@brief	Viewport
 */

#ifndef HAMON_RENDER_VIEWPORT_HPP
#define HAMON_RENDER_VIEWPORT_HPP

namespace hamon
{

inline namespace render
{

struct Viewport
{
	float	left      {0.0f};
	float	top       {0.0f};
	float	width     {0.0f};
	float	height    {0.0f};
	float	min_depth {0.0f};
	float	max_depth {1.0f};
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VIEWPORT_HPP
