/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP
#define HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP

#include <hamon/render/opengl/buffer.hpp>
#include <hamon/render/opengl/gl.hpp>
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
	explicit IndexBuffer(render::Geometry const& geometry)
		: m_buffer(geometry.GetIndexArrayBytes(), geometry.GetIndexArrayData(), GL_STATIC_DRAW)
		, m_count(static_cast<::GLsizei>(geometry.GetIndexArrayCount()))
	{
	}

	void Draw(::GLenum topology)
	{
		::glDrawElements(topology, m_count, GL_UNSIGNED_SHORT, 0);
	}

	::GLuint GetId(void) const { return m_buffer.GetId(); }

private:
	gl::Buffer		m_buffer;
	::GLsizei		m_count;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_INDEX_BUFFER_HPP
