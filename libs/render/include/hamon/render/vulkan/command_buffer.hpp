/**
 *	@file	command_buffer.hpp
 *
 *	@brief	CommandBuffer
 */

#ifndef HAMON_RENDER_VULKAN_COMMAND_BUFFER_HPP
#define HAMON_RENDER_VULKAN_COMMAND_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/command_pool.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <hamon/render/clear_value.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class CommandBuffer
{
public:
	CommandBuffer(vulkan::CommandPool* command_pool)
		: m_command_pool(command_pool)
	{
		m_command_buffer = m_command_pool->AllocateCommandBuffers(
			VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1)[0];
	}

	~CommandBuffer()
	{
		m_command_pool->FreeCommandBuffers({m_command_buffer});
	}

	void Begin(void)
	{
		VkCommandBufferBeginInfo cmd_buf_info = {};
		cmd_buf_info.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmd_buf_info.pNext            = nullptr;
		cmd_buf_info.flags            = 0;
		cmd_buf_info.pInheritanceInfo = nullptr;
		ThrowIfFailed(vkBeginCommandBuffer(m_command_buffer, &cmd_buf_info));
	}

	void End(void)
	{
		ThrowIfFailed(vkEndCommandBuffer(m_command_buffer));
	}

	void BeginRenderPass(
		VkRenderPass render_pass,
		VkFramebuffer framebuffer,
		VkExtent2D const& extent,
		ClearValue const& clear_value)
	{
		VkClearValue clear_values[2];
		clear_values[0].color.float32[0] = clear_value.r;
		clear_values[0].color.float32[1] = clear_value.g;
		clear_values[0].color.float32[2] = clear_value.b;
		clear_values[0].color.float32[3] = clear_value.a;
		clear_values[1].depthStencil.depth = 1.0f;
		clear_values[1].depthStencil.stencil = 0;

		VkRenderPassBeginInfo info;
		info.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		info.pNext             = nullptr;
		info.renderPass        = render_pass;
		info.framebuffer       = framebuffer;
		info.renderArea.offset = {0, 0};
		info.renderArea.extent = extent;
		info.clearValueCount   = 2;
		info.pClearValues      = clear_values;
		vkCmdBeginRenderPass(m_command_buffer, &info, VK_SUBPASS_CONTENTS_INLINE);
	}

	void EndRenderPass(void)
	{
		vkCmdEndRenderPass(m_command_buffer);
	}

	VkCommandBuffer const& Get(void) const { return m_command_buffer; }

private:
	VkCommandBuffer m_command_buffer;
	vulkan::CommandPool* m_command_pool;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_COMMAND_BUFFER_HPP
