/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_VULKAN_SHADER_HPP
#define HAMON_RENDER_VULKAN_SHADER_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/shader_module.hpp>
#include <hamon/render/vulkan/shader_stage.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Shader
{
public:
	explicit Shader(
		vulkan::Device* device,
		render::ShaderStage stage,
		std::vector<std::uint32_t> const& spv)
		: m_shader_module(device, spv)
		, m_stage(vulkan::ShaderStage(stage))
	{
	}

	::VkShaderModule GetModule(void) const
	{
		return m_shader_module.Get();
	}

	::VkShaderStageFlagBits	GetStage(void) const
	{
		return m_stage;
	}

private:
	vulkan::ShaderModule	m_shader_module;
	::VkShaderStageFlagBits	m_stage;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SHADER_HPP
