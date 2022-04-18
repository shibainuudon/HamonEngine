/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_GL_SHADER_HPP
#define HAMON_RENDER_GL_SHADER_HPP

#include <hamon/render/shader.hpp>
#include <hamon/render/gl/shader_stage.hpp>
#include <hamon/render/gl/glext.hpp>
#include <iostream>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Shader
{
public:
	explicit Shader(::GLuint program, render::Shader const& shader)
	{
		m_id = gl::glCreateShader(gl::ShaderStage(shader.GetStage()));

		char const* src = shader.GetSource().c_str();
		gl::glShaderSource(m_id, 1, &src, nullptr);
		gl::glCompileShader(m_id);

		::GLint compiled;
		gl::glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			::GLint log_length;
			gl::glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
			if (log_length != 0)
			{
				std::vector<char> info_log(log_length);
				::GLsizei length;
				gl::glGetShaderInfoLog(m_id, log_length, &length, info_log.data());

				std::cout << info_log.data() << std::endl;
				return;
			}
		}

		gl::glAttachShader(program, m_id);
	}

	~Shader()
	{
		gl::glDeleteShader(m_id);
	}

	Shader(Shader const&) = delete;
	Shader& operator=(Shader const&) = delete;

	Shader(Shader &&) = default;
	Shader& operator=(Shader &&) = default;

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_SHADER_HPP
