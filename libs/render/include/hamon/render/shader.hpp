/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_SHADER_HPP
#define HAMON_RENDER_SHADER_HPP

#include <hamon/render/shader_stage.hpp>
#include <string>
#include <utility>

namespace hamon
{

inline namespace render
{

class Shader
{
public:
	Shader(ShaderStage stage, std::string source)
		: m_stage(stage)
		, m_source(std::move(source))
	{}

	Shader(ShaderStage stage, std::string source, std::string entry_point)
		: m_stage(stage)
		, m_source(std::move(source))
		, m_entry_point(std::move(entry_point))
	{}

	ShaderStage GetStage(void) const
	{
		return m_stage;
	}
	
	std::string const& GetSource(void) const
	{
		return m_source;
	}

	std::string const& GetEntryPoint(void) const
	{
		return m_entry_point;
	}

private:
	ShaderStage		m_stage;
	std::string		m_source;
	std::string		m_entry_point {"main"};
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SHADER_HPP
