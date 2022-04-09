/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_OPENGL_BLEND_STATE_HPP
#define HAMON_RENDER_OPENGL_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/opengl/glext.hpp>

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
			ToGlBlendFactor(state.color_src_factor),
			ToGlBlendFactor(state.color_dest_factor),
			ToGlBlendFactor(state.alpha_src_factor),
			ToGlBlendFactor(state.alpha_dest_factor));

		gl::glBlendEquationSeparate(
			ToGlBlendOperation(state.color_operation),
			ToGlBlendOperation(state.alpha_operation));

		if (state.logic_op_enable)
		{
			::glEnable(GL_COLOR_LOGIC_OP);
		}
		else
		{
			::glDisable(GL_COLOR_LOGIC_OP);
		}

		::glLogicOp(ToGlLogicOperation(state.logic_operation));

		::glColorMask(
			state.color_write_mask & ColorWriteMask::Red,
			state.color_write_mask & ColorWriteMask::Green,
			state.color_write_mask & ColorWriteMask::Blue,
			state.color_write_mask & ColorWriteMask::Alpha);
	}

private:
	static ::GLenum ToGlBlendFactor(render::BlendFactor factor)
	{
		switch (factor)
		{
		case render::BlendFactor::Zero:				return GL_ZERO;
		case render::BlendFactor::One:				return GL_ONE;
		case render::BlendFactor::SrcColor:			return GL_SRC_COLOR;
		case render::BlendFactor::InvSrcColor:		return GL_ONE_MINUS_SRC_COLOR;
		case render::BlendFactor::SrcAlpha:			return GL_SRC_ALPHA;
		case render::BlendFactor::InvSrcAlpha:		return GL_ONE_MINUS_SRC_ALPHA;
		case render::BlendFactor::DestAlpha:		return GL_DST_ALPHA;
		case render::BlendFactor::InvDestAlpha:		return GL_ONE_MINUS_DST_ALPHA;
		case render::BlendFactor::DestColor:		return GL_DST_COLOR;
		case render::BlendFactor::InvDestColor:		return GL_ONE_MINUS_DST_COLOR;
		case render::BlendFactor::SrcAlphaSat:		return GL_SRC_ALPHA_SATURATE;
		case render::BlendFactor::BlendFactor:		return GL_CONSTANT_COLOR;
		case render::BlendFactor::InvBlendFactor:	return GL_ONE_MINUS_CONSTANT_COLOR;
		case render::BlendFactor::Src1Color:		return GL_SRC1_COLOR;
		case render::BlendFactor::InvSrc1Color:		return GL_ONE_MINUS_SRC1_COLOR;
		case render::BlendFactor::Src1Alpha:		return GL_SRC1_ALPHA;
		case render::BlendFactor::InvSrc1Alpha:		return GL_ONE_MINUS_SRC1_ALPHA;
		}
		return GL_ZERO;
	}

	static ::GLenum ToGlBlendOperation(render::BlendOperation op)
	{
		switch (op)
		{
		case render::BlendOperation::Add:				return GL_FUNC_ADD;
		case render::BlendOperation::Subtract:			return GL_FUNC_SUBTRACT;
		case render::BlendOperation::ReverseSubtract:	return GL_FUNC_REVERSE_SUBTRACT;
		case render::BlendOperation::Min:				return GL_MIN;
		case render::BlendOperation::Max:				return GL_MAX;
		}
		return GL_FUNC_ADD;
	}

	static ::GLenum ToGlLogicOperation(render::LogicOperation op)
	{
		switch (op)
		{
		case render::LogicOperation::Clear:			return GL_CLEAR;
		case render::LogicOperation::Set:			return GL_SET;
		case render::LogicOperation::Copy:			return GL_COPY;
		case render::LogicOperation::CopyInverted:	return GL_COPY_INVERTED;
		case render::LogicOperation::Noop:			return GL_NOOP;
		case render::LogicOperation::Invert:		return GL_INVERT;
		case render::LogicOperation::And:			return GL_AND;
		case render::LogicOperation::Nand:			return GL_NAND;
		case render::LogicOperation::Or:			return GL_OR;
		case render::LogicOperation::Nor:			return GL_NOR;
		case render::LogicOperation::Xor:			return GL_XOR;
		case render::LogicOperation::Equiv:			return GL_EQUIV;
		case render::LogicOperation::AndReverse:	return GL_AND_REVERSE;
		case render::LogicOperation::AndInverted:	return GL_AND_INVERTED;
		case render::LogicOperation::OrReverse:		return GL_OR_REVERSE;
		case render::LogicOperation::OrInverted:	return GL_OR_INVERTED;
		}
		return GL_COPY;
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_BLEND_STATE_HPP
