/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_GL_BLEND_STATE_HPP
#define HAMON_RENDER_GL_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/gl/blend_factor.hpp>
#include <hamon/render/gl/blend_operation.hpp>
#include <hamon/render/gl/logic_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class BlendState
{
public:
	static void Apply(render::BlendState const& state)
	{
		if (state.blend_enable)
		{
			::glEnable(GL_BLEND);
		}
		else
		{
			::glDisable(GL_BLEND);
		}

		gl::glBlendFuncSeparate(
			gl::BlendFactor(state.color_src_factor),
			gl::BlendFactor(state.color_dest_factor),
			gl::BlendFactor(state.alpha_src_factor),
			gl::BlendFactor(state.alpha_dest_factor));

		gl::glBlendEquationSeparate(
			gl::BlendOperation(state.color_operation),
			gl::BlendOperation(state.alpha_operation));

		if (state.logic_op_enable)
		{
			::glEnable(GL_COLOR_LOGIC_OP);
		}
		else
		{
			::glDisable(GL_COLOR_LOGIC_OP);
		}

		::glLogicOp(gl::LogicOperation(state.logic_operation));

		::glColorMask(
			state.color_write_mask & ColorWriteMask::Red,
			state.color_write_mask & ColorWriteMask::Green,
			state.color_write_mask & ColorWriteMask::Blue,
			state.color_write_mask & ColorWriteMask::Alpha);

		gl::glBlendColor(
			state.constant_color.r,
			state.constant_color.g,
			state.constant_color.b,
			state.constant_color.a);
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_BLEND_STATE_HPP
