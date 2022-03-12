/**
 *	@file	semaphore.hpp
 *
 *	@brief	Semaphore
 */

#ifndef HAMON_RENDER_VULKAN_SEMAPHORE_HPP
#define HAMON_RENDER_VULKAN_SEMAPHORE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Semaphore
{
public:
	Semaphore(vulkan::Device* device)
		: m_device(device)
	{
		VkSemaphoreCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		m_semaphore = m_device->CreateSemaphore(info);
	}

	~Semaphore()
	{
		m_device->DestroySemaphore(m_semaphore);
	}

	VkSemaphore const& Get(void) const { return m_semaphore; }

private:
	VkSemaphore     m_semaphore;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SEMAPHORE_HPP
