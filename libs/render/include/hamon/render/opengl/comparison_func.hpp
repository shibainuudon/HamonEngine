/**
 *	@file	comparison_func.hpp
 *
 *	@brief	ComparisonFunc
 */

#ifndef HAMON_RENDER_OPENGL_COMPARISON_FUNC_HPP
#define HAMON_RENDER_OPENGL_COMPARISON_FUNC_HPP

#include <hamon/render/comparison_func.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum ComparisonFunc(render::ComparisonFunc func)
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

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_COMPARISON_FUNC_HPP
