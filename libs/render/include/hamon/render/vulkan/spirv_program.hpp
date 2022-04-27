/**
 *	@file	spirv_program.hpp
 *
 *	@brief	SpirvProgram
 */

#ifndef HAMON_RENDER_VULKAN_SPIRV_PROGRAM_HPP
#define HAMON_RENDER_VULKAN_SPIRV_PROGRAM_HPP

#include <hamon/render/vulkan/spirv_shader.hpp>
#include <hamon/render/program.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class SpirvProgram
{
public:
	explicit SpirvProgram(render::Program const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			m_shaders.emplace_back(shader);
		}
	}

	std::vector<SpirvShader> const& GetShaders(void) const
	{
		return m_shaders;
	}

private:
	std::vector<SpirvShader>	m_shaders;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SPIRV_PROGRAM_HPP
