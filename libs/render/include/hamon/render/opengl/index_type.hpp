/**
 *	@file	index_type.hpp
 *
 *	@brief	IndexType
 */

#ifndef HAMON_RENDER_GL_INDEX_TYPE_HPP
#define HAMON_RENDER_GL_INDEX_TYPE_HPP

#include <hamon/render/opengl/gl.hpp>
#include <hamon/render/index_type.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum
IndexType(render::IndexType type)
{
	switch (type)
	{
	case render::IndexType::UInt16:	return GL_UNSIGNED_SHORT;
	case render::IndexType::UInt32:	return GL_UNSIGNED_INT;
	}
	return GL_UNSIGNED_SHORT;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_INDEX_TYPE_HPP
