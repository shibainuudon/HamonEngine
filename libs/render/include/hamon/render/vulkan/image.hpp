/**
 *	@file	image.hpp
 *
 *	@brief	Image
 */

#ifndef HAMON_RENDER_VULKAN_IMAGE_HPP
#define HAMON_RENDER_VULKAN_IMAGE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Image
{
public:
	explicit Image(
		vulkan::Device* device,
		::VkFormat format,
		::VkExtent3D const& extent,
		::uint32_t mip_levels,
		::VkImageUsageFlags usage)
		: m_device(device)
		, m_format(format)
		, m_extent(extent)
		, m_mipmap_count(mip_levels)
		, m_aspect_mask(VK_IMAGE_ASPECT_COLOR_BIT)	// TODO
		, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	{
		::VkImageCreateInfo info{};
		info.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		info.pNext                 = nullptr;
		info.flags                 = 0;
		info.imageType             = VK_IMAGE_TYPE_2D;
		info.format                = format;
		info.extent                = extent;
		info.mipLevels             = mip_levels;
		info.arrayLayers           = 1;
		info.samples               = VK_SAMPLE_COUNT_1_BIT;
		info.tiling                = VK_IMAGE_TILING_OPTIMAL;
		info.usage                 = usage;
		info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		info.queueFamilyIndexCount = 0;
		info.pQueueFamilyIndices   = nullptr;
		info.initialLayout         = m_layout;

		m_image = m_device->CreateImage(info);
	}

	~Image()
	{
		m_device->DestroyImage(m_image);
	}

private:
	static ::VkAccessFlags GetAccessMask(::VkImageLayout layout)
	{
		switch (layout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			return 0;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			return VK_ACCESS_TRANSFER_WRITE_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			return VK_ACCESS_TRANSFER_READ_BIT;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			return VK_ACCESS_SHADER_READ_BIT;
		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			return
				VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
				VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			return
				VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
				VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		case VK_IMAGE_LAYOUT_GENERAL:
			return
				VK_ACCESS_SHADER_READ_BIT |
				VK_ACCESS_SHADER_WRITE_BIT;
		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			return VK_ACCESS_HOST_WRITE_BIT;
		}
		return 0;
	}

	static ::VkPipelineStageFlags GetPipelineStage(::VkImageLayout layout)
	{
		switch (layout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			return VK_PIPELINE_STAGE_TRANSFER_BIT;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			return VK_PIPELINE_STAGE_TRANSFER_BIT;
		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		case VK_IMAGE_LAYOUT_GENERAL:
			return VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			return VK_PIPELINE_STAGE_HOST_BIT;
		}
		return 0;
	}

public:
	void TransitionLayout(vulkan::CommandBuffer* command_buffer, ::VkImageLayout new_layout)
	{
		auto const old_layout = m_layout;
		m_layout = new_layout;

		::VkImageMemoryBarrier barrier{};
		barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.pNext                           = nullptr;
		barrier.srcAccessMask                   = GetAccessMask(old_layout);
		barrier.dstAccessMask                   = GetAccessMask(new_layout);
		barrier.oldLayout                       = old_layout;
		barrier.newLayout                       = new_layout;
		barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
		barrier.image                           = m_image;
		barrier.subresourceRange.aspectMask     = m_aspect_mask;
		barrier.subresourceRange.baseMipLevel   = 0;
		barrier.subresourceRange.levelCount     = m_mipmap_count;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount     = 1;

		command_buffer->PipelineBarrier(
			GetPipelineStage(old_layout),
			GetPipelineStage(new_layout),
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier);
	}

	void CopyFromBuffer(vulkan::CommandBuffer* command_buffer, ::VkBuffer buffer)
	{
		::VkDeviceSize src_offset = 0;
		auto extent = m_extent;
		for (std::uint32_t i = 0; i < m_mipmap_count; ++i)
		{
			::VkBufferImageCopy region{};
			region.bufferOffset = src_offset;
			region.bufferRowLength = 0;
			region.bufferImageHeight = 0;
			region.imageSubresource.aspectMask = m_aspect_mask;
			region.imageSubresource.baseArrayLayer = 0;
			region.imageSubresource.layerCount = 1;
			region.imageSubresource.mipLevel = i;
			region.imageOffset = {0, 0, 0};
			region.imageExtent = extent;

			command_buffer->CopyBufferToImage(
				buffer,
				m_image,
				m_layout,
				1, &region);

			src_offset += GetSizeInBytes(m_format, extent.width, extent.height);
			extent.width  = (std::max)(extent.width  / 2, 1u);
			extent.height = (std::max)(extent.height / 2, 1u);
		}
	}

	::VkImage const& Get(void) const
	{
		return m_image;
	}

	::VkFormat const& GetFormat(void) const
	{
		return m_format;
	}
	
	::VkImageLayout const& GetLayout(void) const
	{
		return m_layout;
	}

private:
	::VkImage		m_image;
	::VkFormat		m_format;
	::VkExtent3D	m_extent;
	std::uint32_t	m_mipmap_count;
	::VkImageAspectFlags	m_aspect_mask;
	::VkImageLayout	m_layout;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_image_HPP
