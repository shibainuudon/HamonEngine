/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_OPENGL_PROGRAM_HPP
#define HAMON_RENDER_OPENGL_PROGRAM_HPP

#include <hamon/render/shader.hpp>
#include <hamon/render/opengl/shader.hpp>
#include <hamon/render/opengl/glext.hpp>
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
	explicit Program(std::vector<render::Shader> const& shaders)
	{
		m_id = gl::glCreateProgram();

		for (auto&& shader : shaders)
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
	}

	void Unuse()
	{
		gl::glUseProgram(0u);
	}

private:
	::GLuint	m_id;
	std::vector<gl::Shader>	m_shaders;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_PROGRAM_HPP
