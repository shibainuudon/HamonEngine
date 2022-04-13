/**
 *	@file	shader_module.hpp
 *
 *	@brief	ShaderModule
 */

#ifndef HAMON_RENDER_VULKAN_SHADER_MODULE_HPP
#define HAMON_RENDER_VULKAN_SHADER_MODULE_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class ShaderModule
{
public:
	explicit ShaderModule(vulkan::Device* device, std::vector<std::uint32_t> const& spv)
		: m_device(device)
	{
		::VkShaderModuleCreateInfo info{};
		info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize = spv.size() * sizeof(std::uint32_t);
		info.pCode    = spv.data();

		m_shader_module = m_device->CreateShaderModule(info);
	}

	~ShaderModule()
	{
		m_device->DestroyShaderModule(m_shader_module);
	}

	::VkShaderModule		Get(void) const { return m_shader_module; }

private:
	::VkShaderModule		m_shader_module;
	vulkan::Device*			m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SHADER_MODULE_HPP
