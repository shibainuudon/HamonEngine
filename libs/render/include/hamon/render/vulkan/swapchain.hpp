/**
 *	@file	swapchain.hpp
 *
 *	@brief	Swapchain
 */

#ifndef HAMON_RENDER_VULKAN_SWAPCHAIN_HPP
#define HAMON_RENDER_VULKAN_SWAPCHAIN_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/physical_device.hpp>
#include <hamon/render/vulkan/surface.hpp>
#include <hamon/render/vulkan/image_view.hpp>
#include <hamon/render/vulkan/queue.hpp>
#include <cstdint>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Swapchain
{
public:
	Swapchain(
		vulkan::Device* device,
		vulkan::Surface* surface,
		std::uint32_t width,
		std::uint32_t height,
		std::uint32_t graphics_queue_family_index)
		: m_device(device)
	{
		auto physical_device = device->GetPhysicalDevice();

		auto const present_queue_family_index =
			physical_device->GetPresentQueueFamilyIndex(surface->Get());

		auto const surface_capabilities = physical_device->GetSurfaceCapabilities(surface->Get());
		
		auto const surface_formats = physical_device->GetSurfaceFormats(surface->Get());
		::VkFormat format;
		if (surface_formats.size() == 1 &&
			surface_formats[0].format == VK_FORMAT_UNDEFINED)
		{
			format = VK_FORMAT_B8G8R8A8_UNORM;
		}
		else
		{
			format = surface_formats[0].format;
		}
		m_format = format;

		// width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
		if (surface_capabilities.currentExtent.width == 0xFFFFFFFF)
		{
			// If the surface size is undefined, the size is set to
			// the size of the images requested.
			m_extent.width = width;
			m_extent.height = height;
			if (m_extent.width < surface_capabilities.minImageExtent.width)
			{
				m_extent.width = surface_capabilities.minImageExtent.width;
			}
			else if (m_extent.width > surface_capabilities.maxImageExtent.width)
			{
				m_extent.width = surface_capabilities.maxImageExtent.width;
			}

			if (m_extent.height < surface_capabilities.minImageExtent.height)
			{
				m_extent.height = surface_capabilities.minImageExtent.height;
			}
			else if (m_extent.height > surface_capabilities.maxImageExtent.height)
			{
				m_extent.height = surface_capabilities.maxImageExtent.height;
			}
		}
		else
		{
			// If the surface size is defined, the swap chain size must match
			m_extent = surface_capabilities.currentExtent;
		}

		::VkSurfaceTransformFlagBitsKHR preTransform;
		if (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		{
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		}
		else
		{
			preTransform = surface_capabilities.currentTransform;
		}

		::VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		::VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] =
		{
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		};

		for (auto compositeAlphaFlag : compositeAlphaFlags)
		{
			if (surface_capabilities.supportedCompositeAlpha & compositeAlphaFlag)
			{
				compositeAlpha = compositeAlphaFlag;
				break;
			}
		}

		::VkSwapchainCreateInfoKHR info {};
		info.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		info.pNext                 = nullptr;
		info.surface               = surface->Get();
		info.minImageCount         = surface_capabilities.minImageCount;
		info.imageFormat           = format;
		info.imageExtent.width     = m_extent.width;
		info.imageExtent.height    = m_extent.height;
		info.preTransform          = preTransform;
		info.compositeAlpha        = compositeAlpha;
		info.imageArrayLayers      = 1;
		info.presentMode           = VK_PRESENT_MODE_FIFO_KHR;
		info.oldSwapchain          = VK_NULL_HANDLE;
		info.clipped               = true;
		info.imageColorSpace       = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		info.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		info.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
		info.queueFamilyIndexCount = 0;
		info.pQueueFamilyIndices   = nullptr;

		std::uint32_t const queueFamilyIndices[] =
		{
			graphics_queue_family_index,
			present_queue_family_index
		};

		if (graphics_queue_family_index != present_queue_family_index)
		{
			// If the graphics and present queues are from different queue families,
			// we either have to explicitly transfer ownership of images between
			// the queues, or we have to create the swapchain with imageSharingMode
			// as VK_SHARING_MODE_CONCURRENT
			info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			info.queueFamilyIndexCount = 2;
			info.pQueueFamilyIndices = queueFamilyIndices;
		}

		m_swapchain = m_device->CreateSwapchain(info);

		for (auto const& image : this->GetImages())
		{
			m_image_views.emplace_back(m_device, image, m_format);
		}

		m_present_queue = std::make_unique<vulkan::Queue>(
			m_device->GetDeviceQueue(present_queue_family_index, 0));
	}

	~Swapchain()
	{
		m_device->DestroySwapchain(m_swapchain);
	}
	
	std::uint32_t AcquireNextImage(
		std::uint64_t timeout,
		::VkSemaphore semaphore,
		::VkFence fence)
	{
		return m_device->AcquireNextImage(m_swapchain, timeout, semaphore, fence);
	}
	
	void Present(
		vulkan::ArrayProxy<::VkSemaphore> wait_semaphores,
		std::uint32_t image_index)
	{
		m_present_queue->Present(wait_semaphores, m_swapchain, image_index);
	}

	std::vector<::VkImage> GetImages(void) const
	{
		return m_device->GetSwapchainImages(m_swapchain);
	}

	::VkExtent2D const& GetExtent(void) const
	{
		return m_extent;
	}

	::VkFormat const& GetFormat(void) const
	{
		return m_format;
	}

	std::vector<vulkan::ImageView> const& GetImageViews(void) const
	{
		return m_image_views;
	}

	::VkSwapchainKHR const& Get(void) const
	{
		return m_swapchain;
	}

private:
	::VkSwapchainKHR               m_swapchain;
	::VkExtent2D                   m_extent;
	::VkFormat                     m_format;
	std::vector<vulkan::ImageView> m_image_views;
	std::unique_ptr<vulkan::Queue> m_present_queue;
	vulkan::Device*                m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SWAPCHAIN_HPP
