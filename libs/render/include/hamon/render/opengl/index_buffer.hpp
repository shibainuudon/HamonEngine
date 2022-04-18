/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP
#define HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP

#include <hamon/render/opengl/buffer.hpp>
#include <hamon/render/opengl/gl.hpp>
#include <hamon/render/opengl/index_type.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class IndexBuffer
{
public:
	explicit IndexBuffer(render::detail::IndexArrayBase const* index_array)
		: m_buffer(index_array->GetBytes(), index_array->GetData(), GL_STATIC_DRAW)
		, m_count(static_cast<::GLsizei>(index_array->GetCount()))
		, m_type(gl::IndexType(index_array->GetType()))
	{
	}

	void Draw(::GLenum topology)
	{
		::glDrawElements(topology, m_count, m_type, 0);
	}

	::GLuint GetId(void) const { return m_buffer.GetId(); }

private:
	gl::Buffer		m_buffer;
	::GLsizei		m_count;
	::GLenum		m_type;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP
