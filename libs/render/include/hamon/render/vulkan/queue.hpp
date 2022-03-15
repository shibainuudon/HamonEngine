/**
 *	@file	queue.hpp
 *
 *	@brief	Queue
 */

#ifndef HAMON_RENDER_VULKAN_QUEUE_HPP
#define HAMON_RENDER_VULKAN_QUEUE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Queue
{
public:
	Queue(VkQueue queue)
		: m_queue(queue)
	{
	}

	~Queue()
	{
	}

	void Submit(VkCommandBuffer command_buffer, VkSemaphore semaphore, VkFence fence)
	{
		VkPipelineStageFlags const pipe_stage_flags =
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		
		VkSubmitInfo info = {};
		info.pNext                = nullptr;
		info.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		info.waitSemaphoreCount   = 1;
		info.pWaitSemaphores      = &semaphore;
		info.pWaitDstStageMask    = &pipe_stage_flags;
		info.commandBufferCount   = 1;
		info.pCommandBuffers      = &command_buffer;
		info.signalSemaphoreCount = 0;
		info.pSignalSemaphores    = nullptr;
		ThrowIfFailed(vkQueueSubmit(m_queue, 1, &info, fence));
	}

	void Present(VkSwapchainKHR swapchain, std::uint32_t image_index)
	{
		VkPresentInfoKHR info;
		info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		info.pNext              = nullptr;
		info.swapchainCount     = 1;
		info.pSwapchains        = &swapchain;
		info.pImageIndices      = &image_index;
		info.pWaitSemaphores    = nullptr;
		info.waitSemaphoreCount = 0;
		info.pResults           = nullptr;
		ThrowIfFailed(vkQueuePresentKHR(m_queue, &info));
	}

private:
	VkQueue m_queue;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_QUEUE_HPP
