/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP
#define HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/opengl/cull_mode.hpp>
#include <hamon/render/opengl/fill_mode.hpp>
#include <hamon/render/opengl/front_face.hpp>
#include <hamon/render/opengl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class RasterizerState
{
public:
	static void Apply(render::RasterizerState const& state)
	{
		if (state.cull_mode != render::CullMode::None)
		{
			::glEnable(GL_CULL_FACE);
			::glCullFace(gl::CullMode(state.cull_mode));
		}
		else
		{
			::glDisable(GL_CULL_FACE);
		}

		::glFrontFace(gl::FrontFace(state.front_face));

		::glPolygonMode(GL_FRONT_AND_BACK, gl::FillMode(state.fill_mode));
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP
