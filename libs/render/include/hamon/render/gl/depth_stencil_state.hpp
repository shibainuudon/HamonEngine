/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_GL_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_GL_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/depth_stencil_state.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/gl/stencil_operation.hpp>
#include <hamon/render/gl/comparison_func.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class DepthStencilState
{
public:
	static void Apply(render::DepthStencilState const& state)
	{
		if (state.depth.enable)
		{
			::glEnable(GL_DEPTH_TEST);
		}
		else
		{
			::glDisable(GL_DEPTH_TEST);
		}
		::glDepthMask(state.depth.write);
		::glDepthFunc(gl::ComparisonFunc(state.depth.func));

		if (state.stencil.enable)
		{
			::glEnable(GL_STENCIL_TEST);
		}
		else
		{
			::glDisable(GL_STENCIL_TEST);
		}
		::glStencilFunc(
			gl::ComparisonFunc(state.stencil.func),
			state.stencil.reference,
			state.stencil.read_mask);
		::glStencilMask(state.stencil.write_mask);
		::glStencilOp(
			gl::StencilOperation(state.stencil.fail_operation),
			gl::StencilOperation(state.stencil.depth_fail_operation),
			gl::StencilOperation(state.stencil.pass_operation));
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_DEPTH_STENCIL_STATE_HPP
