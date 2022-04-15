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
		clear_values[0].color.float32[0] = clear_value.color.r;
		clear_values[0].color.float32[1] = clear_value.color.g;
		clear_values[0].color.float32[2] = clear_value.color.b;
		clear_values[0].color.float32[3] = clear_value.color.a;
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

	void BindVertexBuffers(
		std::uint32_t         first_binding,
		std::uint32_t         binding_count,
		const ::VkBuffer*     buffers,
		const ::VkDeviceSize* offsets)
	{
		::vkCmdBindVertexBuffers(m_command_buffer, first_binding, binding_count, buffers, offsets);
	}

	void BindIndexBuffer(
		::VkBuffer      buffer,
		::VkDeviceSize  offset,
		::VkIndexType   index_type)
	{
		::vkCmdBindIndexBuffer(m_command_buffer, buffer, offset, index_type);
	}

	void BindPipeline(
		::VkPipelineBindPoint pipeline_bind_point,
		::VkPipeline          pipeline)
	{
		::vkCmdBindPipeline(m_command_buffer, pipeline_bind_point, pipeline);
	}

	void Draw(
		std::uint32_t vertex_count,
		std::uint32_t instance_count,
		std::uint32_t first_vertex,
		std::uint32_t first_instance)
	{
		::vkCmdDraw(m_command_buffer, vertex_count, instance_count, first_vertex, first_instance);
	}

	void DrawIndexed(
		std::uint32_t index_count,
		std::uint32_t instance_count,
		std::uint32_t first_index,
		std::int32_t  vertex_offset,
		std::uint32_t first_instance)
	{
		::vkCmdDrawIndexed(
			m_command_buffer,
			index_count,
			instance_count,
			first_index,
			vertex_offset,
			first_instance);
	}

	void SetViewport(
		std::uint32_t       first_viewport,
		std::uint32_t       viewport_count,
		::VkViewport const* viewports)
	{
		::vkCmdSetViewport(m_command_buffer, first_viewport, viewport_count, viewports);
	}

	void SetScissor(
		std::uint32_t     first_scissor,
		std::uint32_t     scissor_count,
		::VkRect2D const* scissors)
	{
		::vkCmdSetScissor(m_command_buffer, first_scissor, scissor_count, scissors);
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
