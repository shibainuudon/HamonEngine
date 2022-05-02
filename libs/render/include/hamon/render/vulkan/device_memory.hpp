/**
 *	@file	device_memory.hpp
 *
 *	@brief	DeviceMemory
 */

#ifndef HAMON_RENDER_VULKAN_DEVICE_MEMORY_HPP
#define HAMON_RENDER_VULKAN_DEVICE_MEMORY_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class DeviceMemory
{
public:
	explicit DeviceMemory(
		vulkan::Device* device,
		::VkMemoryRequirements const& mem_reqs,
		::VkFlags requirements_mask)
		: m_device(device)
	{
		::VkMemoryAllocateInfo info{};
		info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		info.pNext           = nullptr;
		info.allocationSize  = mem_reqs.size;
		info.memoryTypeIndex = GetMemoryTypeIndex(
			m_device->GetPhysicalDevice()->GetMemoryProperties(),
			mem_reqs.memoryTypeBits,
			requirements_mask);

		m_device_memory = m_device->AllocateMemory(info);
	}

	~DeviceMemory()
	{
		m_device->FreeMemory(m_device_memory);
	}

	void* Map(
		::VkDeviceSize     offset,
		::VkDeviceSize     size,
		::VkMemoryMapFlags flags)
	{
		return m_device->MapMemory(m_device_memory, offset, size, flags);
	}

	void Unmap(void)
	{
		return m_device->UnmapMemory(m_device_memory);
	}

	void BindBufferMemory(
		::VkBuffer     buffer,
		::VkDeviceSize memory_offset)
	{
		m_device->BindBufferMemory(buffer, m_device_memory, memory_offset);
	}
	
	void BindImageMemory(
		::VkImage      image,
		::VkDeviceSize memory_offset)
	{
		m_device->BindImageMemory(image, m_device_memory, memory_offset);
	}

private:
	static std::uint32_t GetMemoryTypeIndex(
		::VkPhysicalDeviceMemoryProperties const& props,
		std::uint32_t type_bits,
		::VkFlags mask)
	{
		// Search memtypes to find first index with those properties
		for (std::uint32_t i = 0; i < props.memoryTypeCount; i++)
		{
			if ((type_bits & 1) == 1)
			{
				// Type is available, does it match user properties?
				if ((props.memoryTypes[i].propertyFlags & mask) == mask)
				{
					return i;
				}
			}
			type_bits >>= 1;
		}

		// No memory types matched, return failure
		return std::uint32_t(-1);
	}

private:
	::VkDeviceMemory	m_device_memory;
	vulkan::Device*		m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DEVICE_MEMORY_HPP
