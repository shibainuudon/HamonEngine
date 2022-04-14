/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation
 */

#ifndef HAMON_RENDER_OPENGL_STENCIL_OPERATION_HPP
#define HAMON_RENDER_OPENGL_STENCIL_OPERATION_HPP

#include <hamon/render/stencil_operation.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum StencilOperation(render::StencilOperation op)
{
	switch (op)
	{
	case render::StencilOperation::Keep:				return GL_KEEP;
	case render::StencilOperation::Zero:				return GL_ZERO;
	case render::StencilOperation::Replace:				return GL_REPLACE;
	case render::StencilOperation::IncrementAndClamp:	return GL_INCR;
	case render::StencilOperation::DecrementAndClamp:	return GL_DECR;
	case render::StencilOperation::Invert:				return GL_INVERT;
	case render::StencilOperation::IncrementAndWrap:	return GL_INCR_WRAP;
	case render::StencilOperation::DecrementAndWrap:	return GL_DECR_WRAP;
	}
	return GL_KEEP;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_STENCIL_OPERATION_HPP
