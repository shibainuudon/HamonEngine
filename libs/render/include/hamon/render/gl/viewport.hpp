/**
 *	@file	viewport.hpp
 *
 *	@brief	Viewport
 */

#ifndef HAMON_RENDER_GL_VIEWPORT_HPP
#define HAMON_RENDER_GL_VIEWPORT_HPP

#include <hamon/render/viewport.hpp>
#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Viewport
{
public:
	static void Apply(render::Viewport const& viewport)
	{
		::glViewport(
			static_cast<::GLint>(viewport.left),
			static_cast<::GLint>(viewport.top),
			static_cast<::GLsizei>(viewport.width),
			static_cast<::GLsizei>(viewport.height));
		gl::glDepthRangef(
			viewport.min_depth,
			viewport.max_depth);
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_VIEWPORT_HPP
