/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_GL_VERTEX_BUFFER_HPP
#define HAMON_RENDER_GL_VERTEX_BUFFER_HPP

#include <hamon/render/gl/buffer.hpp>
#include <hamon/render/gl/gl.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class VertexBuffer
{
public:
	explicit VertexBuffer(render::Geometry const& geometry)
		: m_buffer(geometry.GetVertexArrayBytes(), geometry.GetVertexArrayData(), GL_STATIC_DRAW)
		, m_count(static_cast<::GLsizei>(geometry.GetVertexArrayCount()))
	{
	}

	void Draw(::GLenum topology)
	{
		::glDrawArrays(topology, 0, m_count);
	}
	
	::GLuint GetId(void) const { return m_buffer.GetId(); }

private:
	gl::Buffer		m_buffer;
	::GLsizei		m_count;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_VERTEX_BUFFER_HPP
