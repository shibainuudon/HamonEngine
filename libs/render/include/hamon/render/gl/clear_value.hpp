/**
 *	@file	clear_value.hpp
 *
 *	@brief	ClearValue
 */

#ifndef HAMON_RENDER_GL_CLEAR_VALUE_HPP
#define HAMON_RENDER_GL_CLEAR_VALUE_HPP

#include <hamon/render/clear_value.hpp>
#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class ClearValue
{
public:
	static void Apply(render::ClearValue const& value)
	{
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		::glDepthMask(GL_TRUE);
		::glStencilMask(~0u);
		::glClearColor(
			value.color.r,
			value.color.g,
			value.color.b,
			value.color.a);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_CLEAR_VALUE_HPP
