/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer
 */

#ifndef HAMON_RENDER_GL_BUFFER_HPP
#define HAMON_RENDER_GL_BUFFER_HPP

#include <hamon/render/gl/glext.hpp>

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
		if (size != 0 && data != nullptr)
		{
			gl::glCreateBuffers(1, &m_id);
			gl::glNamedBufferData(m_id, size, data, usage);
		}
	}

	~Buffer()
	{
		if (m_id != 0)
		{
			gl::glDeleteBuffers(1, &m_id);
		}
	}

	::GLuint GetId(void) const { return m_id; }

private:
	::GLuint		m_id{};
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_BUFFER_HPP
