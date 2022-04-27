/**
 *	@file	image_view.hpp
 *
 *	@brief	ImageView
 */

#ifndef HAMON_RENDER_VULKAN_IMAGE_VIEW_HPP
#define HAMON_RENDER_VULKAN_IMAGE_VIEW_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class ImageView
{
public:
	ImageView(vulkan::Device* device, ::VkImage image, ::VkFormat format)
		: m_device(device)
	{
		::VkImageViewCreateInfo info {};
		info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		info.pNext                           = nullptr;
		info.flags                           = 0;
		info.image                           = image;
		info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		info.format                          = format;
		info.components.r                    = VK_COMPONENT_SWIZZLE_R;
		info.components.g                    = VK_COMPONENT_SWIZZLE_G;
		info.components.b                    = VK_COMPONENT_SWIZZLE_B;
		info.components.a                    = VK_COMPONENT_SWIZZLE_A;
		info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		info.subresourceRange.baseMipLevel   = 0;
		info.subresourceRange.levelCount     = 1;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount     = 1;

		m_image_view = m_device->CreateImageView(info);
	}

	~ImageView()
	{
		m_device->DestroyImageView(m_image_view);
	}

	::VkImageView const& Get(void) const
	{
		return m_image_view;
	}

private:
	::VkImageView	m_image_view;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_IMAGE_VIEW_HPP
