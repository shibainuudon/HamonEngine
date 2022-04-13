/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_VULKAN_PROGRAM_HPP
#define HAMON_RENDER_VULKAN_PROGRAM_HPP

#include <hamon/render/vulkan/shader.hpp>
#include <hamon/render/program.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Program
{
public:
	explicit Program(vulkan::Device* device, render::Program const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			m_shaders.emplace_back(device, shader);
		}
	}

	std::vector<vulkan::Shader>	const&
	GetShaders(void) const
	{
		return m_shaders;
	}

private:
	std::vector<vulkan::Shader>	m_shaders;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PROGRAM_HPP
