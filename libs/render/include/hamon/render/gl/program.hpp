/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_GL_PROGRAM_HPP
#define HAMON_RENDER_GL_PROGRAM_HPP

#include <hamon/render/shader.hpp>
#include <hamon/render/program.hpp>
#include <hamon/render/gl/shader.hpp>
#include <hamon/render/gl/uniform_block.hpp>
#include <hamon/render/gl/uniform.hpp>
#include <hamon/render/gl/glext.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Program
{
public:
	explicit Program(render::Program const& program)
	{
		m_id = gl::glCreateProgram();

		for (auto&& shader : program.GetShaders())
		{
			m_shaders.emplace_back(m_id, shader);
		}

		gl::glLinkProgram(m_id);

		::GLint linked;
		gl::glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			::GLint log_length;
			gl::glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
			if (log_length != 0)
			{
				std::vector<char> info_log(log_length);
				::GLsizei length;
				gl::glGetProgramInfoLog(m_id, log_length, &length, info_log.data());

				std::cout << info_log.data() << std::endl;
				return;
			}
		}

		::GLint uniform_block_count;
		gl::glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_BLOCKS, &uniform_block_count);
		for (::GLint i = 0; i < uniform_block_count; ++i)
		{
			m_uniform_blocks.emplace_back(m_id, i);
		}

		::GLint uniform_count;
		gl::glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniform_count);
		for (::GLint i = 0; i < uniform_count; ++i)
		{
			m_uniforms.emplace_back(m_id, i);
		}
	}

	~Program()
	{
		m_shaders.clear();
		gl::glDeleteProgram(m_id);
	}

	Program(Program const&) = delete;
	Program& operator=(Program const&) = delete;

	//Program(Program&&) = default;
	//Program& operator=(Program&&) = default;

	void Use()
	{
		gl::glUseProgram(m_id);
		for (auto& uniform_block : m_uniform_blocks)
		{
			uniform_block.Bind();
		}
	}

	void Unuse()
	{
		for (auto& uniform_block : m_uniform_blocks)
		{
			uniform_block.Unbind();
		}
		gl::glUseProgram(0u);
	}

	void LoadUniforms(render::Uniforms const& uniforms, gl::ResourceMap* resource_map)
	{
		for (auto& uniform_block : m_uniform_blocks)
		{
			uniform_block.LoadUniforms(uniforms, m_uniforms);
		}

		for (auto& uniform : m_uniforms)
		{
			uniform.LoadUniforms(uniforms, resource_map);
		}
	}

private:
	::GLuint						m_id;
	std::vector<gl::Shader>			m_shaders;
	std::vector<gl::UniformBlock>	m_uniform_blocks;
	std::vector<gl::Uniform>		m_uniforms;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_PROGRAM_HPP
