/**
 *	@file	queue.hpp
 *
 *	@brief	Queue
 */

#ifndef HAMON_RENDER_VULKAN_QUEUE_HPP
#define HAMON_RENDER_VULKAN_QUEUE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <hamon/render/vulkan/array_proxy.hpp>
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
	Queue(::VkQueue queue)
		: m_queue(queue)
	{
	}

	~Queue()
	{
	}

	void Submit(
		vulkan::ArrayProxy<::VkSemaphore> wait_semaphores,
		vulkan::ArrayProxy<::VkCommandBuffer> command_buffers,
		vulkan::ArrayProxy<::VkSemaphore> signal_semaphores,
		::VkFence fence)
	{
		::VkPipelineStageFlags const pipe_stage_flags =
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		
		::VkSubmitInfo info{};
		info.pNext                = nullptr;
		info.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		info.waitSemaphoreCount   = wait_semaphores.GetSize();
		info.pWaitSemaphores      = wait_semaphores.GetData();
		info.pWaitDstStageMask    = &pipe_stage_flags;
		info.commandBufferCount   = command_buffers.GetSize();
		info.pCommandBuffers      = command_buffers.GetData();
		info.signalSemaphoreCount = signal_semaphores.GetSize();
		info.pSignalSemaphores    = signal_semaphores.GetData();
		ThrowIfFailed(::vkQueueSubmit(m_queue, 1, &info, fence));
	}

	void Present(
		vulkan::ArrayProxy<::VkSemaphore> wait_semaphores,
		vulkan::ArrayProxy<::VkSwapchainKHR> swapchains,
		std::uint32_t image_index)
	{
		::VkPresentInfoKHR info{};
		info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		info.pNext              = nullptr;
		info.waitSemaphoreCount = wait_semaphores.GetSize();
		info.pWaitSemaphores    = wait_semaphores.GetData();
		info.swapchainCount     = swapchains.GetSize();
		info.pSwapchains        = swapchains.GetData();
		info.pImageIndices      = &image_index;
		info.pResults           = nullptr;
		ThrowIfFailed(::vkQueuePresentKHR(m_queue, &info));
	}

	void WaitIdle(void)
	{
		ThrowIfFailed(::vkQueueWaitIdle(m_queue));
	}

private:
	::VkQueue m_queue;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_QUEUE_HPP
