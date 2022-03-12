/**
 *	@file	render_pass.hpp
 *
 *	@brief	RenderPass
 */

#ifndef HAMON_RENDER_VULKAN_RENDER_PASS_HPP
#define HAMON_RENDER_VULKAN_RENDER_PASS_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class RenderPass
{
public:
	RenderPass(vulkan::Device* device, VkFormat format, VkSampleCountFlagBits samples)
		: m_device(device)
	{
		VkAttachmentDescription attachment;
		attachment.format         = format;
		attachment.samples        = samples;
		attachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		attachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		attachment.flags          = 0;

		VkAttachmentReference color_reference = {};
		color_reference.attachment = 0;
		color_reference.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.flags                   = 0;
		subpass.inputAttachmentCount    = 0;
		subpass.pInputAttachments       = nullptr;
		subpass.colorAttachmentCount    = 1;
		subpass.pColorAttachments       = &color_reference;
		subpass.pResolveAttachments     = nullptr;
		subpass.pDepthStencilAttachment = nullptr;
		subpass.preserveAttachmentCount = 0;
		subpass.pPreserveAttachments    = nullptr;

		VkSubpassDependency subpass_dependency = {};
		subpass_dependency.srcSubpass      = VK_SUBPASS_EXTERNAL;
		subpass_dependency.dstSubpass      = 0;
		subpass_dependency.srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpass_dependency.dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpass_dependency.srcAccessMask   = 0;
		subpass_dependency.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		subpass_dependency.dependencyFlags = 0;

		VkRenderPassCreateInfo info = {};
		info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.pNext           = nullptr;
		info.attachmentCount = 1;
		info.pAttachments    = &attachment;
		info.subpassCount    = 1;
		info.pSubpasses      = &subpass;
		info.dependencyCount = 1;
		info.pDependencies   = &subpass_dependency;
		m_render_pass = m_device->CreateRenderPass(info);
	}

	~RenderPass()
	{
		m_device->DestroyRenderPass(m_render_pass);
	}

	VkRenderPass const& Get(void) const { return m_render_pass; }

private:
	VkRenderPass m_render_pass;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_RENDER_PASS_HPP
