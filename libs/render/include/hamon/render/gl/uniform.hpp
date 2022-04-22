/**
 *	@file	uniform.hpp
 *
 *	@brief	Uniform
 */

#ifndef HAMON_RENDER_GL_UNIFORM_HPP
#define HAMON_RENDER_GL_UNIFORM_HPP

#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/uniforms.hpp>
#include <string>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Uniform
{
public:
	explicit Uniform(::GLuint program, ::GLuint index)
	{
		::GLint max_length;
		gl::glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);

		::GLint size;
		std::vector<::GLchar> buf(max_length + 1);
		gl::glGetActiveUniform(program, index, max_length, nullptr, &size, &m_type, buf.data());
		m_name = buf.data();

		m_location = gl::glGetUniformLocation(program, m_name.c_str());

		gl::glGetActiveUniformsiv(program, 1, &index, GL_UNIFORM_OFFSET, &m_offset);

		switch (m_type)
		{
		case GL_FLOAT:				m_size = sizeof(float) * 1; break;
		case GL_FLOAT_VEC2:			m_size = sizeof(float) * 2; break;
		case GL_FLOAT_VEC3:			m_size = sizeof(float) * 3; break;
		case GL_FLOAT_VEC4:			m_size = sizeof(float) * 4; break;
		case GL_DOUBLE:				m_size = sizeof(double) * 1; break;
		case GL_DOUBLE_VEC2:		m_size = sizeof(double) * 2; break;
		case GL_DOUBLE_VEC3:		m_size = sizeof(double) * 3; break;
		case GL_DOUBLE_VEC4:		m_size = sizeof(double) * 4; break;
		case GL_INT:				m_size = sizeof(int) * 1; break;
		case GL_INT_VEC2:			m_size = sizeof(int) * 2; break;
		case GL_INT_VEC3:			m_size = sizeof(int) * 3; break;
		case GL_INT_VEC4:			m_size = sizeof(int) * 4; break;
		case GL_UNSIGNED_INT:		m_size = sizeof(unsigned int) * 1; break;
		case GL_UNSIGNED_INT_VEC2:	m_size = sizeof(unsigned int) * 2; break;
		case GL_UNSIGNED_INT_VEC3:	m_size = sizeof(unsigned int) * 3; break;
		case GL_UNSIGNED_INT_VEC4:	m_size = sizeof(unsigned int) * 4; break;
		case GL_BOOL:				m_size = sizeof(bool) * 1; break;
		case GL_BOOL_VEC2:			m_size = sizeof(bool) * 2; break;
		case GL_BOOL_VEC3:			m_size = sizeof(bool) * 3; break;
		case GL_BOOL_VEC4:			m_size = sizeof(bool) * 4; break;
		case GL_FLOAT_MAT2:			m_size = sizeof(float) * 2 * 2; break;
		case GL_FLOAT_MAT2x3:		m_size = sizeof(float) * 2 * 3; break;
		case GL_FLOAT_MAT2x4:		m_size = sizeof(float) * 2 * 4; break;
		case GL_FLOAT_MAT3x2:		m_size = sizeof(float) * 3 * 2; break;
		case GL_FLOAT_MAT3:			m_size = sizeof(float) * 3 * 3; break;
		case GL_FLOAT_MAT3x4:		m_size = sizeof(float) * 3 * 4; break;
		case GL_FLOAT_MAT4x2:		m_size = sizeof(float) * 4 * 2; break;
		case GL_FLOAT_MAT4x3:		m_size = sizeof(float) * 4 * 3; break;
		case GL_FLOAT_MAT4:			m_size = sizeof(float) * 4 * 4; break;
		case GL_DOUBLE_MAT2:		m_size = sizeof(double) * 2 * 2; break;
		case GL_DOUBLE_MAT2x3:		m_size = sizeof(double) * 2 * 3; break;
		case GL_DOUBLE_MAT2x4:		m_size = sizeof(double) * 2 * 4; break;
		case GL_DOUBLE_MAT3x2:		m_size = sizeof(double) * 3 * 2; break;
		case GL_DOUBLE_MAT3:		m_size = sizeof(double) * 3 * 3; break;
		case GL_DOUBLE_MAT3x4:		m_size = sizeof(double) * 3 * 4; break;
		case GL_DOUBLE_MAT4x2:		m_size = sizeof(double) * 4 * 2; break;
		case GL_DOUBLE_MAT4x3:		m_size = sizeof(double) * 4 * 3; break;
		case GL_DOUBLE_MAT4:		m_size = sizeof(double) * 4 * 4; break;
		}
	}

	void LoadUniforms(render::Uniforms const& uniforms)
	{
		auto uniform = uniforms[m_name];
		if (uniform == nullptr)
		{
			return;
		}

		switch (m_type)
		{
		case GL_FLOAT:				gl::glUniform1fv(m_location, 1, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_VEC2:			gl::glUniform2fv(m_location, 1, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_VEC3:			gl::glUniform3fv(m_location, 1, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_VEC4:			gl::glUniform4fv(m_location, 1, static_cast<float const*>(uniform->GetData())); break;
		case GL_DOUBLE:				gl::glUniform1dv(m_location, 1, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_VEC2:		gl::glUniform2dv(m_location, 1, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_VEC3:		gl::glUniform3dv(m_location, 1, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_VEC4:		gl::glUniform4dv(m_location, 1, static_cast<double const*>(uniform->GetData())); break;
		case GL_INT:				gl::glUniform1iv(m_location, 1, static_cast<int const*>(uniform->GetData())); break;
		case GL_INT_VEC2:			gl::glUniform2iv(m_location, 1, static_cast<int const*>(uniform->GetData())); break;
		case GL_INT_VEC3:			gl::glUniform3iv(m_location, 1, static_cast<int const*>(uniform->GetData())); break;
		case GL_INT_VEC4:			gl::glUniform4iv(m_location, 1, static_cast<int const*>(uniform->GetData())); break;
		case GL_UNSIGNED_INT:		gl::glUniform1uiv(m_location, 1, static_cast<unsigned int const*>(uniform->GetData())); break;
		case GL_UNSIGNED_INT_VEC2:	gl::glUniform2uiv(m_location, 1, static_cast<unsigned int const*>(uniform->GetData())); break;
		case GL_UNSIGNED_INT_VEC3:	gl::glUniform3uiv(m_location, 1, static_cast<unsigned int const*>(uniform->GetData())); break;
		case GL_UNSIGNED_INT_VEC4:	gl::glUniform4uiv(m_location, 1, static_cast<unsigned int const*>(uniform->GetData())); break;
		//case GL_BOOL:				gl::glUniform1iv(m_location, 1, static_cast<bool const*>(uniform->GetData())); break;
		//case GL_BOOL_VEC2:			gl::glUniform2iv(m_location, 1, static_cast<bool const*>(uniform->GetData())); break;
		//case GL_BOOL_VEC3:			gl::glUniform3iv(m_location, 1, static_cast<bool const*>(uniform->GetData())); break;
		//case GL_BOOL_VEC4:			gl::glUniform4iv(m_location, 1, static_cast<bool const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT2:			gl::glUniformMatrix2fv  (m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT2x3:		gl::glUniformMatrix2x3fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT2x4:		gl::glUniformMatrix2x4fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT3x2:		gl::glUniformMatrix3x2fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT3:			gl::glUniformMatrix3fv  (m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT3x4:		gl::glUniformMatrix3x4fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT4x2:		gl::glUniformMatrix4x2fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT4x3:		gl::glUniformMatrix4x3fv(m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_FLOAT_MAT4:			gl::glUniformMatrix4fv  (m_location, 1, GL_FALSE, static_cast<float const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT2:		gl::glUniformMatrix2dv  (m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT2x3:		gl::glUniformMatrix2x3dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT2x4:		gl::glUniformMatrix2x4dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT3x2:		gl::glUniformMatrix3x2dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT3:		gl::glUniformMatrix3dv  (m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT3x4:		gl::glUniformMatrix3x4dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT4x2:		gl::glUniformMatrix4x2dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT4x3:		gl::glUniformMatrix4x3dv(m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		case GL_DOUBLE_MAT4:		gl::glUniformMatrix4dv  (m_location, 1, GL_FALSE, static_cast<double const*>(uniform->GetData())); break;
		}
	}

	void UniformBufferSubData(render::Uniforms const& uniforms, gl::Buffer const* buffer) const
	{
		auto uniform = uniforms[m_name];
		if (uniform == nullptr)
		{
			return;
		}

		auto p = static_cast<float const*>(uniform->GetData());
		buffer->SubData(m_offset, m_size, p);
	}

private:
	std::string		m_name;
	::GLenum		m_type;
	::GLint			m_location;
	::GLint			m_offset;
	::GLsizeiptr	m_size;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_UNIFORM_HPP
