/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState
 */

#ifndef HAMON_RENDER_GL_SCISSOR_STATE_HPP
#define HAMON_RENDER_GL_SCISSOR_STATE_HPP

#include <hamon/render/scissor_state.hpp>
#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class ScissorState
{
public:
	static void Apply(render::ScissorState const& scissor_state)
	{
		if (scissor_state.enable)
		{
			::glEnable(GL_SCISSOR_TEST);
			::glScissor(
				static_cast<::GLint>(scissor_state.left),
				static_cast<::GLint>(scissor_state.top),
				static_cast<::GLsizei>(scissor_state.width),
				static_cast<::GLsizei>(scissor_state.height));
		}
		else
		{
			::glDisable(GL_SCISSOR_TEST);
		}
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_SCISSOR_STATE_HPP
