/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor
 */

#ifndef HAMON_RENDER_GL_BORDER_COLOR_HPP
#define HAMON_RENDER_GL_BORDER_COLOR_HPP

#include <hamon/render/border_color.hpp>
#include <hamon/render/gl/gl.hpp>
#include <array>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline std::array<float, 4> BorderColor(render::BorderColor border_color)
{
	switch (border_color)
	{
	case render::BorderColor::TransparentBlack:
		return { 0, 0, 0, 0 };
	case render::BorderColor::OpaqueBlack:
		return { 0, 0, 0, 1 };
	case render::BorderColor::OpaqueWhite:
		return { 1, 1, 1, 1 };
	}
	return { 0, 0, 0, 0 };
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_BORDER_COLOR_HPP
