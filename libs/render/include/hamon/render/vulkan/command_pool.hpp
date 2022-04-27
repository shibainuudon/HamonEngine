/**
 *	@file	command_pool.hpp
 *
 *	@brief	CommandPool
 */

#ifndef HAMON_RENDER_VULKAN_COMMAND_POOL_HPP
#define HAMON_RENDER_VULKAN_COMMAND_POOL_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <cstdint>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class CommandPool
{
public:
	CommandPool(vulkan::Device* device, std::uint32_t queue_family_index)
		: m_device(device)
	{
		::VkCommandPoolCreateInfo info = {};
		info.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		info.pNext            = nullptr;
		info.queueFamilyIndex = queue_family_index;
		info.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		m_command_pool = m_device->CreateCommandPool(info);
	}

	~CommandPool()
	{
		m_device->DestroyCommandPool(m_command_pool);
	}

	std::vector<::VkCommandBuffer> AllocateCommandBuffers(
		::VkCommandBufferLevel level,
		std::uint32_t count)
	{
		::VkCommandBufferAllocateInfo info = {};
		info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		info.pNext              = nullptr;
		info.commandPool        = m_command_pool;
		info.level              = level;
		info.commandBufferCount = count;
		return m_device->AllocateCommandBuffers(info);
	}

	void FreeCommandBuffers(std::vector<::VkCommandBuffer> const& command_buffers)
	{
		m_device->FreeCommandBuffers(m_command_pool, command_buffers);
	}

private:
	::VkCommandPool m_command_pool;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_COMMAND_POOL_HPP
