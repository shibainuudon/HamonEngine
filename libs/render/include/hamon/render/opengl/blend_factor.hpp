/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor
 */

#ifndef HAMON_RENDER_OPENGL_BLEND_FACTOR_HPP
#define HAMON_RENDER_OPENGL_BLEND_FACTOR_HPP

#include <hamon/render/blend_factor.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum BlendFactor(render::BlendFactor factor)
{
	switch (factor)
	{
	case render::BlendFactor::Zero:					return GL_ZERO;
	case render::BlendFactor::One:					return GL_ONE;
	case render::BlendFactor::SrcColor:				return GL_SRC_COLOR;
	case render::BlendFactor::OneMinusSrcColor:		return GL_ONE_MINUS_SRC_COLOR;
	case render::BlendFactor::DstColor:				return GL_DST_COLOR;
	case render::BlendFactor::OneMinusDstColor:		return GL_ONE_MINUS_DST_COLOR;
	case render::BlendFactor::SrcAlpha:				return GL_SRC_ALPHA;
	case render::BlendFactor::OneMinusSrcAlpha:		return GL_ONE_MINUS_SRC_ALPHA;
	case render::BlendFactor::DstAlpha:				return GL_DST_ALPHA;
	case render::BlendFactor::OneMinusDstAlpha:		return GL_ONE_MINUS_DST_ALPHA;
	case render::BlendFactor::ConstantColor:		return GL_CONSTANT_COLOR;
	case render::BlendFactor::OneMinusConstantColor:return GL_ONE_MINUS_CONSTANT_COLOR;
	case render::BlendFactor::ConstantAlpha:		return GL_CONSTANT_ALPHA;
	case render::BlendFactor::OneMinusConstantAlpha:return GL_ONE_MINUS_CONSTANT_ALPHA;
	case render::BlendFactor::SrcAlphaSaturate:		return GL_SRC_ALPHA_SATURATE;
	case render::BlendFactor::Src1Color:			return GL_SRC1_COLOR;
	case render::BlendFactor::OneMinusSrc1Color:	return GL_ONE_MINUS_SRC1_COLOR;
	case render::BlendFactor::Src1Alpha:			return GL_SRC1_ALPHA;
	case render::BlendFactor::OneMinusSrc1Alpha:	return GL_ONE_MINUS_SRC1_ALPHA;
	}
	return GL_ZERO;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_BLEND_FACTOR_HPP
