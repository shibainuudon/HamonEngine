/**
 *	@file	uniform_block.hpp
 *
 *	@brief	UniformBlock
 */

#ifndef HAMON_RENDER_GL_UNIFORM_BLOCK_HPP
#define HAMON_RENDER_GL_UNIFORM_BLOCK_HPP

#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/gl/buffer.hpp>
#include <hamon/render/gl/uniform.hpp>
#include <string>
#include <vector>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace gl
{

class UniformBlock
{
public:
	explicit UniformBlock(::GLuint program, ::GLint index)
	{
		::GLint name_length;
		gl::glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_NAME_LENGTH, &name_length);

		std::vector<::GLchar> buf(name_length + 1);
		gl::glGetActiveUniformBlockName(program, index, name_length, nullptr, buf.data());
		m_name = buf.data();

		::GLint size;
		gl::glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
		gl::glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_BINDING, &m_binding);

		m_uniform_buffer = std::make_unique<gl::Buffer>(size, nullptr, GL_DYNAMIC_DRAW);
		gl::glUniformBlockBinding(program, index, m_binding);

		::GLint member_count;
		gl::glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &member_count);

		m_member_indices.resize(member_count);
		gl::glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, m_member_indices.data());
	}

	void LoadUniforms(render::Uniforms const& uniforms, std::vector<gl::Uniform> const& gl_uniforms)
	{
		for (auto index : m_member_indices)
		{
			gl_uniforms[index].UniformBufferSubData(uniforms, m_uniform_buffer.get());
		}
	}

	void Bind(void)
	{
		gl::glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, m_uniform_buffer->GetId());
	}

	void Unbind(void)
	{
		gl::glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, 0);
	}

private:
	std::string					m_name;
	::GLint						m_binding;
	std::unique_ptr<gl::Buffer>	m_uniform_buffer;
	std::vector<GLint>			m_member_indices;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_UNIFORM_BLOCK_HPP
