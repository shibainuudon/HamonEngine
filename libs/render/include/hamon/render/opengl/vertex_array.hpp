/**
 *	@file	vertex_array.hpp
 *
 *	@brief	VertexArray
 */

#ifndef HAMON_RENDER_OPENGL_VERTEX_ARRAY_HPP
#define HAMON_RENDER_OPENGL_VERTEX_ARRAY_HPP

#include <hamon/render/vertex_layout.hpp>
#include <hamon/render/opengl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum ToGlType(render::Type type)
{
	switch (type)
	{
	case hamon::render::Type::Int8:		return GL_BYTE;
	case hamon::render::Type::Int16:	return GL_SHORT;
	case hamon::render::Type::Int32:	return GL_INT;
	case hamon::render::Type::UInt8:	return GL_UNSIGNED_BYTE;
	case hamon::render::Type::UInt16:	return GL_UNSIGNED_SHORT;
	case hamon::render::Type::UInt32:	return GL_UNSIGNED_INT;
	case hamon::render::Type::Float:	return GL_FLOAT;
	default:							return GL_BYTE;
	}
}

class VertexArray
{
public:
	VertexArray(render::VertexLayout const& layout, ::GLuint vertex_buffer, ::GLuint index_buffer)
	{
		gl::glCreateVertexArrays(1, &m_id);

		::GLuint binding_index = 0;
		::GLuint index = 0;

		for (auto const& attribute : layout.GetAttributes())
		{
			auto const size = attribute.element_num;
			auto const type = ToGlType(attribute.type);
			auto const normalized = GL_FALSE;
			auto const offset = attribute.offset;

			gl::glEnableVertexArrayAttrib(m_id, index);
			gl::glVertexArrayAttribBinding(m_id, index, binding_index);
			gl::glVertexArrayAttribFormat(m_id, index, size, type, normalized, offset);

			++index;
		}

		auto const stride = layout.GetBytes();
		gl::glVertexArrayVertexBuffer(m_id, binding_index, vertex_buffer, 0, stride);
		if (index_buffer != 0)
		{
			gl::glVertexArrayElementBuffer(m_id, index_buffer);
		}
	}

	~VertexArray()
	{
		gl::glDeleteVertexArrays(1, &m_id);
	}

	void Bind()
	{
		gl::glBindVertexArray(m_id);
	}

	void Unbind()
	{
		gl::glBindVertexArray(0);
	}

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_VERTEX_ARRAY_HPP
