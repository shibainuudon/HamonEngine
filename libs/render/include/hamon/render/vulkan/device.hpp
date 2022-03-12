/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_VULKAN_DEVICE_HPP
#define HAMON_RENDER_VULKAN_DEVICE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Device
{
public:
	Device(
		VkPhysicalDevice phycical_device,
		std::vector<const char*> const& layer_names,
		std::vector<const char*> const& extension_names)
	{
		float queue_priorities[1] = { 0.0 };
		VkDeviceQueueCreateInfo queue_info = {};
		queue_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_info.pNext            = nullptr;
		queue_info.queueCount       = 1;
		queue_info.pQueuePriorities = queue_priorities;

		VkDeviceCreateInfo info = {};
		info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		info.pNext                   = nullptr;
		info.queueCreateInfoCount    = 1;
		info.pQueueCreateInfos       = &queue_info;
		info.enabledExtensionCount   = static_cast<std::uint32_t>(extension_names.size());
		info.ppEnabledExtensionNames = extension_names.empty() ? nullptr : extension_names.data();
		info.enabledLayerCount       = static_cast<std::uint32_t>(layer_names.size());
		info.ppEnabledLayerNames     = layer_names.empty() ? nullptr : layer_names.data();
		info.pEnabledFeatures        = nullptr;
		auto res = vkCreateDevice(phycical_device, &info, nullptr, &m_device);
		(void)res;	// TODO
	}

	~Device()
	{
		vkDestroyDevice(m_device, nullptr);
	}

	VkCommandPool CreateCommandPool(VkCommandPoolCreateInfo const& info)
	{
		VkCommandPool command_pool;
		auto res = vkCreateCommandPool(m_device, &info, nullptr, &command_pool);
		(void)res;	// TODO
		return command_pool;
	}

	void DestroyCommandPool(VkCommandPool command_pool)
	{
		vkDestroyCommandPool(m_device, command_pool, nullptr);
	}

	std::vector<VkCommandBuffer> AllocateCommandBuffers(
		VkCommandBufferAllocateInfo const& info)
	{
		// TODO info.commandBufferCount が０のときどうするか
		std::vector<VkCommandBuffer> command_buffers(info.commandBufferCount);
		auto res = vkAllocateCommandBuffers(m_device, &info, command_buffers.data());
		(void)res;	// TODO
		return command_buffers;
	}

	void FreeCommandBuffers(
		VkCommandPool command_pool,
		std::vector<VkCommandBuffer> const& command_buffers)
	{
		vkFreeCommandBuffers(
			m_device,
			command_pool,
			static_cast<std::uint32_t>(command_buffers.size()),
			command_buffers.empty() ? nullptr : command_buffers.data());
	}

	VkQueue GetDeviceQueue(std::uint32_t queue_family_index, std::uint32_t queue_index)
	{
		VkQueue queue;
		vkGetDeviceQueue(m_device, queue_family_index, queue_index, &queue);
		return queue;
	}

	VkSwapchainKHR CreateSwapchain(VkSwapchainCreateInfoKHR const& info)
	{
		VkSwapchainKHR swapchain;
		auto res = vkCreateSwapchainKHR(m_device, &info, nullptr, &swapchain);
		(void)res;	// TODO
		return swapchain;
	}

	void DestroySwapchain(VkSwapchainKHR swapchain)
	{
		vkDestroySwapchainKHR(m_device, swapchain, nullptr);
	}

	std::vector<VkImage> GetSwapchainImages(VkSwapchainKHR swapchain) const
	{
		VkResult res;
		std::uint32_t image_count;
		res = vkGetSwapchainImagesKHR(m_device, swapchain, &image_count, nullptr);
		std::vector<VkImage> swapchain_images(image_count);
		res = vkGetSwapchainImagesKHR(m_device, swapchain, &image_count, swapchain_images.data());
		return swapchain_images;
	}

	VkImageView CreateImageView(VkImageViewCreateInfo const& info)
	{
		VkImageView image_view;
		auto res = vkCreateImageView(m_device, &info, nullptr, &image_view);
		(void)res;	// TODO
		return image_view;
	}

	void DestroyImageView(VkImageView image_view)
	{
		vkDestroyImageView(m_device, image_view, nullptr);
	}

	VkSemaphore CreateSemaphore(VkSemaphoreCreateInfo const& info)
	{
		VkSemaphore semaphore;
		auto res = vkCreateSemaphore(m_device, &info, nullptr, &semaphore);
		(void)res;	// TODO
		return semaphore;
	}

	void DestroySemaphore(VkSemaphore semaphore)
	{
		vkDestroySemaphore(m_device, semaphore, nullptr);
	}

	VkRenderPass CreateRenderPass(VkRenderPassCreateInfo const& info)
	{
		VkRenderPass render_pass;
		auto res = vkCreateRenderPass(m_device, &info, nullptr, &render_pass);
		(void)res;	// TODO
		return render_pass;
	}

	void DestroyRenderPass(VkRenderPass render_pass)
	{
		vkDestroyRenderPass(m_device, render_pass, nullptr);
	}

	VkFramebuffer CreateFramebuffer(VkFramebufferCreateInfo const& info)
	{
		VkFramebuffer framebuffer;
		auto res = vkCreateFramebuffer(m_device, &info, nullptr, &framebuffer);
		(void)res;	// TODO
		return framebuffer;
	}

	void DestroyFramebuffer(VkFramebuffer framebuffer)
	{
		vkDestroyFramebuffer(m_device, framebuffer, nullptr);
	}

	VkFence CreateFence(VkFenceCreateInfo const& info)
	{
		VkFence fence;
		auto res = vkCreateFence(m_device, &info, nullptr, &fence);
		(void)res;	// TODO
		return fence;
	}
	
	void DestroyFence(VkFence fence)
	{
		vkDestroyFence(m_device, fence, nullptr);
	}

	std::uint32_t AcquireNextImage(
		VkSwapchainKHR swapchain,
		std::uint64_t timeout,
		VkSemaphore semaphore,
		VkFence fence)
	{
		std::uint32_t image_index;
		auto res = vkAcquireNextImageKHR(
			m_device,
			swapchain,
			timeout,
			semaphore,
			fence,
			&image_index);
		(void)res;	// TODO
		return image_index;
	}

	VkResult WaitForFences(
		std::uint32_t  fence_count,
		const VkFence* fences,
		VkBool32       wait_all,
		uint64_t       timeout)
	{
		auto res = vkWaitForFences(m_device, fence_count, fences, wait_all, timeout);
		return res;
	}

private:
	VkDevice m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DEVICE_HPP
