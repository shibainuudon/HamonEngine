/**
 *	@file	fence.hpp
 *
 *	@brief	Fence
 */

#ifndef HAMON_RENDER_VULKAN_fence_HPP
#define HAMON_RENDER_VULKAN_fence_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Fence
{
public:
	Fence(vulkan::Device* device)
		: m_device(device)
	{
		VkFenceCreateInfo info;
		info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		m_fence = m_device->CreateFence(info);
	}

	~Fence()
	{
		m_device->DestroyFence(m_fence);
	}

	VkResult Wait(VkBool32 wait_all, std::uint64_t timeout)
	{
		return m_device->WaitForFences(1, &m_fence, wait_all, timeout);
	}

	void Reset()
	{
		m_device->ResetFences(1, &m_fence);
	}

	VkFence const& Get(void) const { return m_fence; }

private:
	VkFence m_fence;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_fence_HPP
