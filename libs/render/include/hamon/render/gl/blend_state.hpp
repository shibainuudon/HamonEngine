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
		for (std::size_t i = 0; i < std::ranges::size(state.render_target); ++i)
		{
			auto const index = static_cast<::GLuint>(i);
			auto const& rt = state.render_target[i];
			if (rt.blend_enable)
			{
				gl::glEnablei(GL_BLEND, index);
			}
			else
			{
				gl::glDisablei(GL_BLEND, index);
			}

			gl::glBlendFuncSeparatei(
				index,
				gl::BlendFactor(rt.color_src_factor),
				gl::BlendFactor(rt.color_dest_factor),
				gl::BlendFactor(rt.alpha_src_factor),
				gl::BlendFactor(rt.alpha_dest_factor));

			gl::glBlendEquationSeparatei(
				index,
				gl::BlendOperation(rt.color_operation),
				gl::BlendOperation(rt.alpha_operation));

			gl::glColorMaski(
				index,
				rt.color_write_mask & ColorWriteMask::Red,
				rt.color_write_mask & ColorWriteMask::Green,
				rt.color_write_mask & ColorWriteMask::Blue,
				rt.color_write_mask & ColorWriteMask::Alpha);
		}

		if (state.logic_op_enable)
		{
			::glEnable(GL_COLOR_LOGIC_OP);
		}
		else
		{
			::glDisable(GL_COLOR_LOGIC_OP);
		}

		::glLogicOp(gl::LogicOperation(state.logic_operation));

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
