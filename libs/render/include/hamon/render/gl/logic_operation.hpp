/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation
 */

#ifndef HAMON_RENDER_GL_LOGIC_OPERATION_HPP
#define HAMON_RENDER_GL_LOGIC_OPERATION_HPP

#include <hamon/render/logic_operation.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum LogicOperation(render::LogicOperation op)
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
	case render::LogicOperation::Equivalent:	return GL_EQUIV;
	case render::LogicOperation::AndReverse:	return GL_AND_REVERSE;
	case render::LogicOperation::AndInverted:	return GL_AND_INVERTED;
	case render::LogicOperation::OrReverse:		return GL_OR_REVERSE;
	case render::LogicOperation::OrInverted:	return GL_OR_INVERTED;
	}
	return GL_COPY;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_LOGIC_OPERATION_HPP
