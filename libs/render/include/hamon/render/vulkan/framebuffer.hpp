/**
 *	@file	framebuffer.hpp
 *
 *	@brief	Framebuffer
 */

#ifndef HAMON_RENDER_VULKAN_FRAMEBUFFER_HPP
#define HAMON_RENDER_VULKAN_FRAMEBUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Framebuffer
{
public:
	Framebuffer(
		vulkan::Device* device,
		::VkRenderPass render_pass,
		std::vector<::VkImageView> const& image_views,
		::VkExtent2D const& extent)
		: m_device(device)
	{
		::VkFramebufferCreateInfo info {};
		info.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		info.pNext           = nullptr;
		info.renderPass      = render_pass;
		info.attachmentCount = static_cast<std::uint32_t>(image_views.size());
		info.pAttachments    = image_views.empty() ? nullptr : image_views.data();
		info.width           = extent.width;
		info.height          = extent.height;
		info.layers          = 1;
		m_framebuffer = m_device->CreateFramebuffer(info);
	}

	~Framebuffer()
	{
		m_device->DestroyFramebuffer(m_framebuffer);
	}

	::VkFramebuffer const& Get(void) const
	{
		return m_framebuffer;
	}

private:
	::VkFramebuffer m_framebuffer;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_FRAMEBUFFER_HPP
