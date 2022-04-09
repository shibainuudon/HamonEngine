/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer
 */

#ifndef HAMON_RENDER_OPENGL_BUFFER_HPP
#define HAMON_RENDER_OPENGL_BUFFER_HPP

#include <hamon/render/opengl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Buffer
{
public:
	explicit Buffer(::GLsizeiptr size, void const* data, ::GLenum usage)
	{
		gl::glCreateBuffers(1, &m_id);
		gl::glNamedBufferData(m_id, size, data, usage);
	}

	~Buffer()
	{
		gl::glDeleteBuffers(1, &m_id);
	}

	::GLuint GetId(void) const { return m_id; }

private:
	::GLuint		m_id;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_BUFFER_HPP
