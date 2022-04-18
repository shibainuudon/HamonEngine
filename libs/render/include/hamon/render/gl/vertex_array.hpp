/**
 *	@file	vertex_array.hpp
 *
 *	@brief	VertexArray
 */

#ifndef HAMON_RENDER_GL_VERTEX_ARRAY_HPP
#define HAMON_RENDER_GL_VERTEX_ARRAY_HPP

#include <hamon/render/vertex_layout.hpp>
#include <hamon/render/gl/type.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/gl/vertex_buffer.hpp>
#include <hamon/render/gl/index_buffer.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class VertexArray
{
public:
	explicit VertexArray(
		render::VertexLayout const& layout,
		gl::VertexBuffer const* vertex_buffer,
		gl::IndexBuffer const* index_buffer)
	{
		gl::glCreateVertexArrays(1, &m_id);

		::GLuint binding_index = 0;
		::GLuint index = 0;

		for (auto const& attribute : layout.GetAttributes())
		{
			auto const size = attribute.element_num;
			auto const type = gl::Type(attribute.type);
			auto const normalized = GL_FALSE;
			auto const offset = attribute.offset;

			gl::glEnableVertexArrayAttrib(m_id, index);
			gl::glVertexArrayAttribBinding(m_id, index, binding_index);
			gl::glVertexArrayAttribFormat(
				m_id,
				index,
				static_cast<::GLint>(size),
				type,
				normalized,
				static_cast<::GLuint>(offset));

			++index;
		}

		if (vertex_buffer)
		{
			auto const stride = layout.GetBytes();
			gl::glVertexArrayVertexBuffer(m_id, binding_index, vertex_buffer->GetId(), 0, static_cast<::GLsizei>(stride));
		}
		
		if (index_buffer)
		{
			gl::glVertexArrayElementBuffer(m_id, index_buffer->GetId());
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

#endif // HAMON_RENDER_GL_VERTEX_ARRAY_HPP
