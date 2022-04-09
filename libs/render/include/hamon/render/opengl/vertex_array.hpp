﻿/**
 *	@file	vertex_array.hpp
 *
 *	@brief	VertexArray
 */

#ifndef HAMON_RENDER_OPENGL_VERTEX_ARRAY_HPP
#define HAMON_RENDER_OPENGL_VERTEX_ARRAY_HPP

#include <hamon/render/vertex_layout.hpp>
#include <hamon/render/opengl/type.hpp>
#include <hamon/render/opengl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class VertexArray
{
public:
	explicit VertexArray(render::VertexLayout const& layout, ::GLuint vertex_buffer, ::GLuint index_buffer)
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

		auto const stride = layout.GetBytes();
		gl::glVertexArrayVertexBuffer(m_id, binding_index, vertex_buffer, 0, static_cast<::GLsizei>(stride));
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
