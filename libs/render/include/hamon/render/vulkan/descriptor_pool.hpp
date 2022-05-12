/**
 *	@file	info.hpp
 *
 *	@brief	DescriptorPool
 */

#ifndef HAMON_RENDER_VULKAN_DESCRIPTOR_POOL_HPP
#define HAMON_RENDER_VULKAN_DESCRIPTOR_POOL_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/array_proxy.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class DescriptorPool
{
public:
	DescriptorPool(vulkan::Device* device)
		: m_device(device)
	{
		::VkDescriptorPoolSize type_count[1];
		type_count[0].type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		type_count[0].descriptorCount = 1024;	// TODO

		::VkDescriptorPoolCreateInfo info {};
		info.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		info.pNext         = NULL;
		info.flags         = 0;
		info.maxSets       = 100;	// TODO
		info.poolSizeCount = 1;
		info.pPoolSizes    = type_count;

		m_descriptor_pool = device->CreateDescriptorPool(info);
	}

	~DescriptorPool()
	{
		m_device->DestroyDescriptorPool(m_descriptor_pool);
	}

	std::vector<::VkDescriptorSet>
	AllocateDescriptorSets(
		vulkan::ArrayProxy<::VkDescriptorSetLayout> descriptor_set_layouts)
	{
		::VkDescriptorSetAllocateInfo info{};
		info.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		info.pNext              = NULL;
		info.descriptorPool     = m_descriptor_pool;
		info.descriptorSetCount = descriptor_set_layouts.GetSize();
		info.pSetLayouts        = descriptor_set_layouts.GetData();
		return m_device->AllocateDescriptorSets(info);
	}

	void Reset(void)
	{
		m_device->ResetDescriptorPool(m_descriptor_pool);
	}

private:
	::VkDescriptorPool	m_descriptor_pool;
	vulkan::Device*		m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DESCRIPTOR_POOL_HPP
