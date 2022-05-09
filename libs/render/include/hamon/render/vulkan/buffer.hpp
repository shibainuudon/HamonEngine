/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer
 */

#ifndef HAMON_RENDER_VULKAN_BUFFER_HPP
#define HAMON_RENDER_VULKAN_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Buffer
{
public:
	explicit Buffer(vulkan::Device* device, ::VkDeviceSize size, ::VkBufferUsageFlags usage)
		: m_device(device)
	{
		::VkBufferCreateInfo info{};
		info.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		info.pNext                 = nullptr;
		info.usage                 = usage;
		info.size                  = size;
		info.queueFamilyIndexCount = 0;
		info.pQueueFamilyIndices   = nullptr;
		info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		info.flags                 = 0;

		m_buffer = m_device->CreateBuffer(info);
	}

	~Buffer()
	{
		m_device->DestroyBuffer(m_buffer);
	}

	::VkMemoryRequirements GetMemoryRequirements(void) const
	{
		return m_device->GetBufferMemoryRequirements(m_buffer);
	}

	::VkBuffer const& Get(void) const
	{
		return m_buffer;
	}

private:
	::VkBuffer		m_buffer;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BUFFER_HPP
