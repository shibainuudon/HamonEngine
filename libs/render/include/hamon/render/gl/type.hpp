/**
 *	@file	type.hpp
 *
 *	@brief	Type
 */

#ifndef HAMON_RENDER_GL_TYPE_HPP
#define HAMON_RENDER_GL_TYPE_HPP

#include <hamon/render/type.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum Type(render::Type type)
{
	switch (type)
	{
	case render::Type::Int8:	return GL_BYTE;
	case render::Type::Int16:	return GL_SHORT;
	case render::Type::Int32:	return GL_INT;
	case render::Type::UInt8:	return GL_UNSIGNED_BYTE;
	case render::Type::UInt16:	return GL_UNSIGNED_SHORT;
	case render::Type::UInt32:	return GL_UNSIGNED_INT;
	case render::Type::Float:	return GL_FLOAT;
	default:					return GL_BYTE;
	}
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_TYPE_HPP
