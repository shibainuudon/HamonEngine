/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_OPENGL_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_OPENGL_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/depth_stencil_state.hpp>
#include <hamon/render/opengl/glext.hpp>

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
		::glDepthFunc(ToGlComparisonFunc(state.depth.func));

		if (state.stencil.enable)
		{
			::glEnable(GL_STENCIL_TEST);
		}
		else
		{
			::glDisable(GL_STENCIL_TEST);
		}
		::glStencilFunc(
			ToGlComparisonFunc(state.stencil.func),
			state.stencil.reference,
			state.stencil.read_mask);
		::glStencilMask(state.stencil.write_mask);
		::glStencilOp(
			ToGlStencilOperation(state.stencil.fail_operation),
			ToGlStencilOperation(state.stencil.depth_fail_operation),
			ToGlStencilOperation(state.stencil.pass_operation));
	}

private:
	static ::GLenum ToGlStencilOperation(render::StencilOperation op)
	{
		switch (op)
		{
		case render::StencilOperation::Keep:				return GL_KEEP;
		case render::StencilOperation::Zero:				return GL_ZERO;
		case render::StencilOperation::Replace:				return GL_REPLACE;
		case render::StencilOperation::IncrementSaturate:	return GL_INCR;
		case render::StencilOperation::DecrementSaturate:	return GL_DECR;
		case render::StencilOperation::Invert:				return GL_INVERT;
		case render::StencilOperation::Increment:			return GL_INCR_WRAP;
		case render::StencilOperation::Decrement:			return GL_DECR_WRAP;
		}
		return GL_KEEP;
	}

	static ::GLenum ToGlComparisonFunc(render::ComparisonFunc func)
	{
		switch (func)
		{
		case render::ComparisonFunc::Never:			return GL_NEVER;
		case render::ComparisonFunc::Less:			return GL_LESS;
		case render::ComparisonFunc::Equal:			return GL_EQUAL;
		case render::ComparisonFunc::LessEqual:		return GL_LEQUAL;
		case render::ComparisonFunc::Greater:		return GL_GREATER;
		case render::ComparisonFunc::NotEqual:		return GL_NOTEQUAL;
		case render::ComparisonFunc::GreaterEqual:	return GL_GEQUAL;
		case render::ComparisonFunc::Always:		return GL_ALWAYS;
		}
		return GL_LESS;
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_DEPTH_STENCIL_STATE_HPP
