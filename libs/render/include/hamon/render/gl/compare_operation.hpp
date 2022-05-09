/**
 *	@file	compare_operation.hpp
 *
 *	@brief	CompareOperation
 */

#ifndef HAMON_RENDER_GL_COMPARE_OPERATION_HPP
#define HAMON_RENDER_GL_COMPARE_OPERATION_HPP

#include <hamon/render/compare_operation.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum CompareOperation(render::CompareOperation op)
{
	switch (op)
	{
	case render::CompareOperation::Never:			return GL_NEVER;
	case render::CompareOperation::Less:			return GL_LESS;
	case render::CompareOperation::Equal:			return GL_EQUAL;
	case render::CompareOperation::LessEqual:		return GL_LEQUAL;
	case render::CompareOperation::Greater:			return GL_GREATER;
	case render::CompareOperation::NotEqual:		return GL_NOTEQUAL;
	case render::CompareOperation::GreaterEqual:	return GL_GEQUAL;
	case render::CompareOperation::Always:			return GL_ALWAYS;
	}
	return GL_LESS;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_COMPARE_OPERATION_HPP
