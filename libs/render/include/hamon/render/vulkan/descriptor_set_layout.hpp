/**
 *	@file	descriptor_set_layout.hpp
 *
 *	@brief	DescriptorSetLayout
 */

#ifndef HAMON_RENDER_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP
#define HAMON_RENDER_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/array_proxy.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class DescriptorSetLayout
{
public:
	DescriptorSetLayout(
		vulkan::Device* device,
		vulkan::ArrayProxy<::VkDescriptorSetLayoutBinding> layout_bindings)
		: m_device(device)
	{
		::VkDescriptorSetLayoutCreateInfo info{};
		info.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		info.pNext        = NULL;
		info.flags        = 0;
		info.bindingCount = layout_bindings.GetSize();
		info.pBindings    = layout_bindings.GetData();

		m_descriptor_set_layout = m_device->CreateDescriptorSetLayout(info);
	}

	~DescriptorSetLayout()
	{
		m_device->DestroyDescriptorSetLayout(m_descriptor_set_layout);
	}

	::VkDescriptorSetLayout const& Get(void) const
	{
		return m_descriptor_set_layout;
	}

private:
	::VkDescriptorSetLayout	m_descriptor_set_layout;
	vulkan::Device*			m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP
