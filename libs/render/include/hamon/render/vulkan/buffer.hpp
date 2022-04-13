﻿/**
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

	void BindMemory(
		vulkan::DeviceMemory* device_memory,
		::VkDeviceSize        memory_offset)
	{
		device_memory->BindBufferMemory(m_buffer, memory_offset);
	}

	void BindAsVertexBuffers(vulkan::CommandBuffer* command_buffer)
	{
		::VkDeviceSize offset = 0;
		command_buffer->BindVertexBuffers(0, 1, &m_buffer, &offset);
	}

private:
	::VkBuffer		m_buffer;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BUFFER_HPP