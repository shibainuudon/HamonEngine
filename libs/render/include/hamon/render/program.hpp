/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_PROGRAM_HPP
#define HAMON_RENDER_PROGRAM_HPP

#include <hamon/render/shader.hpp>
#include <hamon/render/shader_language.hpp>
#include <hamon/render/detail/identifiable.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

class Program : public detail::Identifiable
{
public:
	Program(ShaderLanguage language, std::vector<Shader> shaders)
		: m_language(language)
		, m_shaders(std::move(shaders))
	{}

	ShaderLanguage GetLanguage(void) const
	{
		return m_language;
	}

	std::vector<Shader> const&
	GetShaders(void) const
	{
		return m_shaders;
	}

private:
	ShaderLanguage		m_language;
	std::vector<Shader>	m_shaders;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_PROGRAM_HPP
