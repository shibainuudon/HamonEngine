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
	explicit ShaderModule(vulkan::Device* device, std::vector<unsigned int> const& spv)
		: m_device(device)
	{
		::VkShaderModuleCreateInfo info{};
		info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize = spv.size() * sizeof(unsigned int);
		info.pCode    = spv.data();

		m_shader_module = m_device->CreateShaderModule(info);
	}

	~ShaderModule()
	{
		if (m_device && m_shader_module != VK_NULL_HANDLE)
		{
			m_device->DestroyShaderModule(m_shader_module);
		}
	}

	// コピー不可
	ShaderModule(ShaderModule const&) = delete;
	ShaderModule& operator=(ShaderModule const&) = delete;

	// ムーブコンストラクト可能
	ShaderModule(ShaderModule && rhs)
		: m_shader_module(rhs.m_shader_module)
		, m_device(rhs.m_device)
	{
		rhs.m_shader_module = VK_NULL_HANDLE;
		rhs.m_device = nullptr;
	}

	// ムーブ代入不可
	ShaderModule& operator=(ShaderModule &&) = delete;

	::VkShaderModule Get(void) const
	{
		return m_shader_module;
	}

private:
	::VkShaderModule  m_shader_module { VK_NULL_HANDLE };
	vulkan::Device*   m_device        { nullptr };
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SHADER_MODULE_HPP
