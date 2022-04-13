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

	ShaderStage GetStage(void) const
	{
		return m_stage;
	}
	
	std::string const& GetSource(void) const
	{
		return m_source;
	}

private:
	ShaderStage		m_stage;
	std::string		m_source;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SHADER_HPP
