/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation
 */

#ifndef HAMON_RENDER_GL_BLEND_OPERATION_HPP
#define HAMON_RENDER_GL_BLEND_OPERATION_HPP

#include <hamon/render/blend_operation.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum BlendOperation(render::BlendOperation op)
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

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_BLEND_OPERATION_HPP
