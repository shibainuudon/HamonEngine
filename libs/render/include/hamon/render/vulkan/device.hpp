/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_VULKAN_DEVICE_HPP
#define HAMON_RENDER_VULKAN_DEVICE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <hamon/render/vulkan/physical_device.hpp>
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
		vulkan::PhysicalDevice* phycical_device,
		std::vector<const char*> const& layer_names,
		std::vector<const char*> const& extension_names)
		: m_phycical_device(phycical_device)
	{
		float queue_priorities[1] = { 0.0 };
		::VkDeviceQueueCreateInfo queue_info {};
		queue_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_info.pNext            = nullptr;
		queue_info.queueCount       = 1;
		queue_info.pQueuePriorities = queue_priorities;

		::VkDeviceCreateInfo info {};
		info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		info.pNext                   = nullptr;
		info.queueCreateInfoCount    = 1;
		info.pQueueCreateInfos       = &queue_info;
		info.enabledExtensionCount   = static_cast<std::uint32_t>(extension_names.size());
		info.ppEnabledExtensionNames = extension_names.empty() ? nullptr : extension_names.data();
		info.enabledLayerCount       = static_cast<std::uint32_t>(layer_names.size());
		info.ppEnabledLayerNames     = layer_names.empty() ? nullptr : layer_names.data();
		info.pEnabledFeatures        = nullptr;
		
		m_device = m_phycical_device->CreateDevice(info);
	}

	~Device()
	{
		m_phycical_device->DestroyDevice(m_device);
	}

	::VkCommandPool CreateCommandPool(::VkCommandPoolCreateInfo const& info)
	{
		::VkCommandPool command_pool;
		ThrowIfFailed(vkCreateCommandPool(m_device, &info, nullptr, &command_pool));
		return command_pool;
	}

	void DestroyCommandPool(::VkCommandPool command_pool)
	{
		vkDestroyCommandPool(m_device, command_pool, nullptr);
	}

	std::vector<::VkCommandBuffer> AllocateCommandBuffers(
		::VkCommandBufferAllocateInfo const& info)
	{
		// TODO info.commandBufferCount が０のときどうするか
		std::vector<::VkCommandBuffer> command_buffers(info.commandBufferCount);
		ThrowIfFailed(vkAllocateCommandBuffers(m_device, &info, command_buffers.data()));
		return command_buffers;
	}

	void FreeCommandBuffers(
		::VkCommandPool command_pool,
		std::vector<::VkCommandBuffer> const& command_buffers)
	{
		vkFreeCommandBuffers(
			m_device,
			command_pool,
			static_cast<std::uint32_t>(command_buffers.size()),
			command_buffers.empty() ? nullptr : command_buffers.data());
	}

	::VkQueue GetDeviceQueue(std::uint32_t queue_family_index, std::uint32_t queue_index)
	{
		::VkQueue queue;
		vkGetDeviceQueue(m_device, queue_family_index, queue_index, &queue);
		return queue;
	}

	::VkSwapchainKHR CreateSwapchain(::VkSwapchainCreateInfoKHR const& info)
	{
		::VkSwapchainKHR swapchain;
		ThrowIfFailed(vkCreateSwapchainKHR(m_device, &info, nullptr, &swapchain));
		return swapchain;
	}

	void DestroySwapchain(::VkSwapchainKHR swapchain)
	{
		vkDestroySwapchainKHR(m_device, swapchain, nullptr);
	}

	std::vector<::VkImage> GetSwapchainImages(::VkSwapchainKHR swapchain) const
	{
		std::uint32_t image_count;
		ThrowIfFailed(vkGetSwapchainImagesKHR(m_device, swapchain, &image_count, nullptr));
		std::vector<::VkImage> swapchain_images(image_count);
		ThrowIfFailed(vkGetSwapchainImagesKHR(m_device, swapchain, &image_count, swapchain_images.data()));
		return swapchain_images;
	}

	::VkImageView CreateImageView(::VkImageViewCreateInfo const& info)
	{
		::VkImageView image_view;
		ThrowIfFailed(vkCreateImageView(m_device, &info, nullptr, &image_view));
		return image_view;
	}

	void DestroyImageView(::VkImageView image_view)
	{
		vkDestroyImageView(m_device, image_view, nullptr);
	}

	::VkSemaphore CreateSemaphore(::VkSemaphoreCreateInfo const& info)
	{
		::VkSemaphore semaphore;
		ThrowIfFailed(vkCreateSemaphore(m_device, &info, nullptr, &semaphore));
		return semaphore;
	}

	void DestroySemaphore(::VkSemaphore semaphore)
	{
		vkDestroySemaphore(m_device, semaphore, nullptr);
	}

	::VkRenderPass CreateRenderPass(::VkRenderPassCreateInfo const& info)
	{
		::VkRenderPass render_pass;
		ThrowIfFailed(vkCreateRenderPass(m_device, &info, nullptr, &render_pass));
		return render_pass;
	}

	void DestroyRenderPass(::VkRenderPass render_pass)
	{
		vkDestroyRenderPass(m_device, render_pass, nullptr);
	}

	::VkFramebuffer CreateFramebuffer(::VkFramebufferCreateInfo const& info)
	{
		::VkFramebuffer framebuffer;
		ThrowIfFailed(vkCreateFramebuffer(m_device, &info, nullptr, &framebuffer));
		return framebuffer;
	}

	void DestroyFramebuffer(::VkFramebuffer framebuffer)
	{
		vkDestroyFramebuffer(m_device, framebuffer, nullptr);
	}

	::VkFence CreateFence(::VkFenceCreateInfo const& info)
	{
		::VkFence fence;
		ThrowIfFailed(vkCreateFence(m_device, &info, nullptr, &fence));
		return fence;
	}
	
	void DestroyFence(::VkFence fence)
	{
		vkDestroyFence(m_device, fence, nullptr);
	}

	std::uint32_t AcquireNextImage(
		::VkSwapchainKHR swapchain,
		std::uint64_t timeout,
		::VkSemaphore semaphore,
		::VkFence fence)
	{
		std::uint32_t image_index;
		ThrowIfFailed(vkAcquireNextImageKHR(
			m_device,
			swapchain,
			timeout,
			semaphore,
			fence,
			&image_index));
		return image_index;
	}

	::VkResult WaitForFences(
		std::uint32_t    fence_count,
		::VkFence const* fences,
		::VkBool32       wait_all,
		std::uint64_t    timeout)
	{
		return ThrowIfFailed(vkWaitForFences(m_device, fence_count, fences, wait_all, timeout));
	}
	
	::VkResult ResetFences(
		std::uint32_t    fence_count,
		::VkFence const* fences)
	{
		return ThrowIfFailed(vkResetFences(m_device, fence_count, fences));
	}

	::VkPipelineLayout CreatePipelineLayout(::VkPipelineLayoutCreateInfo const& info)
	{
		::VkPipelineLayout pipeline_layout;
		ThrowIfFailed(::vkCreatePipelineLayout(m_device, &info, nullptr, &pipeline_layout));
		return pipeline_layout;
	}
	
	void DestroyPipelineLayout(::VkPipelineLayout pipeline_layout)
	{
		::vkDestroyPipelineLayout(m_device, pipeline_layout, nullptr);
	}

	::VkBuffer CreateBuffer(::VkBufferCreateInfo const& info)
	{
		::VkBuffer buffer;
		ThrowIfFailed(::vkCreateBuffer(m_device, &info, nullptr, &buffer));
		return buffer;
	}
	
	void DestroyBuffer(::VkBuffer buffer)
	{
		::vkDestroyBuffer(m_device, buffer, nullptr);
	}

	::VkDeviceMemory AllocateMemory(::VkMemoryAllocateInfo const& info)
	{
		::VkDeviceMemory device_memory;
		ThrowIfFailed(::vkAllocateMemory(m_device, &info, nullptr, &device_memory));
		return device_memory;
	}
	
	void FreeMemory(::VkDeviceMemory device_memory)
	{
		::vkFreeMemory(m_device, device_memory, nullptr);
	}

	::VkMemoryRequirements GetBufferMemoryRequirements(::VkBuffer buffer)
	{
		::VkMemoryRequirements mem_reqs;
		::vkGetBufferMemoryRequirements(m_device, buffer, &mem_reqs);
		return mem_reqs;
	}
	
	void* MapMemory(
		::VkDeviceMemory   memory,
		::VkDeviceSize     offset,
		::VkDeviceSize     size,
		::VkMemoryMapFlags flags)
	{
		void* p;
		ThrowIfFailed(::vkMapMemory(m_device, memory, offset, size, flags, &p));
		return p;
	}

	void UnmapMemory(::VkDeviceMemory memory)
	{
		::vkUnmapMemory(m_device, memory);
	}

	void BindBufferMemory(
		::VkBuffer       buffer,
		::VkDeviceMemory memory,
		::VkDeviceSize   memory_offset)
	{
		ThrowIfFailed(::vkBindBufferMemory(m_device, buffer, memory, memory_offset));
	}
	
	::VkShaderModule CreateShaderModule(::VkShaderModuleCreateInfo const& info)
	{
		::VkShaderModule shader_module;
		ThrowIfFailed(::vkCreateShaderModule(m_device, &info, nullptr, &shader_module));
		return shader_module;
	}

	void DestroyShaderModule(::VkShaderModule shader_module)
	{
		::vkDestroyShaderModule(m_device, shader_module, nullptr);
	}

	::VkPipeline CreateGraphicsPipeline(
		::VkPipelineCache	                  pipeline_cache,
		::VkGraphicsPipelineCreateInfo const& create_info)
	{
		::VkPipeline pipeline;
		ThrowIfFailed(::vkCreateGraphicsPipelines(
			m_device,
			pipeline_cache,
			1,
			&create_info,
			nullptr,
			&pipeline));
		return pipeline;
	}

	void DestroyPipeline(::VkPipeline pipeline)
	{
		::vkDestroyPipeline(m_device, pipeline, nullptr);
	}

	::VkDescriptorPool CreateDescriptorPool(
		::VkDescriptorPoolCreateInfo const& create_info)
	{
		::VkDescriptorPool pool;
		ThrowIfFailed(::vkCreateDescriptorPool(
			m_device,
			&create_info,
			nullptr,
			&pool));
		return pool;
	}

	void DestroyDescriptorPool(::VkDescriptorPool pool)
	{
		::vkDestroyDescriptorPool(m_device, pool, nullptr);
	}

	void ResetDescriptorPool(::VkDescriptorPool pool)
	{
		ThrowIfFailed(::vkResetDescriptorPool(m_device, pool, 0));
	}

	std::vector<::VkDescriptorSet>
	AllocateDescriptorSets(::VkDescriptorSetAllocateInfo const& info)
	{
		std::vector<::VkDescriptorSet> descriptor_sets(info.descriptorSetCount);
		ThrowIfFailed(::vkAllocateDescriptorSets(
			m_device,
			&info,
			descriptor_sets.data()));
		return descriptor_sets;
	}

	::VkDescriptorSetLayout CreateDescriptorSetLayout(
		::VkDescriptorSetLayoutCreateInfo const& create_info)
	{
		::VkDescriptorSetLayout layout;
		ThrowIfFailed(::vkCreateDescriptorSetLayout(
			m_device,
			&create_info,
			nullptr,
			&layout));
		return layout;
	}
	
	void DestroyDescriptorSetLayout(::VkDescriptorSetLayout layout)
	{
		::vkDestroyDescriptorSetLayout(m_device, layout, nullptr);
	}

	void UpdateDescriptorSets(
		std::vector<::VkWriteDescriptorSet>	const& descriptor_writes,
		std::vector<::VkCopyDescriptorSet>	const& descriptor_copies)
	{
		::vkUpdateDescriptorSets(
			m_device,
			static_cast<std::uint32_t>(descriptor_writes.size()),
			descriptor_writes.empty() ? nullptr : descriptor_writes.data(),
			static_cast<std::uint32_t>(descriptor_copies.size()),
			descriptor_copies.empty() ? nullptr : descriptor_copies.data());
	}

	::VkSampler CreateSampler(
		::VkSamplerCreateInfo const& create_info)
	{
		::VkSampler sampler;
		ThrowIfFailed(::vkCreateSampler(
			m_device,
			&create_info,
			nullptr,
			&sampler));
		return sampler;
	}

	void DestroySampler(::VkSampler sampler)
	{
		::vkDestroySampler(m_device, sampler, nullptr);
	}

	VkImage CreateImage(::VkImageCreateInfo const& create_info)
	{
		::VkImage image;
		ThrowIfFailed(::vkCreateImage(
			m_device,
			&create_info,
			nullptr,
			&image));
		return image;
	}

	void DestroyImage(::VkImage image)
	{
		::vkDestroyImage(m_device, image, nullptr);
	}

	::VkMemoryRequirements
	GetImageMemoryRequirements(::VkImage image)
	{
		::VkMemoryRequirements requirements;
		::vkGetImageMemoryRequirements(m_device, image, &requirements);
		return requirements;
	}

	void BindImageMemory(
		::VkImage        image,
		::VkDeviceMemory memory,
		::VkDeviceSize   memory_offset)
	{
		ThrowIfFailed(::vkBindImageMemory(m_device, image, memory, memory_offset));
	}

	vulkan::PhysicalDevice* GetPhysicalDevice(void) const
	{
		return m_phycical_device;
	}

private:
	::VkDevice              m_device;
	vulkan::PhysicalDevice* m_phycical_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DEVICE_HPP
