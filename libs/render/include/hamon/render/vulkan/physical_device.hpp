/**
 *	@file	physical_device.hpp
 *
 *	@brief	PhysicalDevice
 */

#ifndef HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP
#define HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class PhysicalDevice
{
public:
	PhysicalDevice(VkPhysicalDevice physical_device)
		: m_physical_device(physical_device)
	{
	}

	~PhysicalDevice()
	{
	}

	std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties(void) const
	{
		std::uint32_t count;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &count, nullptr);
		std::vector<VkQueueFamilyProperties> props(count);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &count, props.data());
		return props;
	}

	std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(VkSurfaceKHR surface) const
	{
		VkResult res;
		std::uint32_t count;
		res = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, nullptr);
		std::vector<VkSurfaceFormatKHR> formats(count);
		res = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, formats.data());
		return formats;
	}

	VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkSurfaceKHR surface) const
	{
		VkSurfaceCapabilitiesKHR capabilities;
		auto res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, surface, &capabilities);
		(void)res;	// TODO
		return capabilities;
	}

	std::vector<VkPresentModeKHR> GetSurfacePresentModes(VkSurfaceKHR surface) const
	{
		VkResult res;
		std::uint32_t count;
		res = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, surface, &count, nullptr);
		std::vector<VkPresentModeKHR> present_modes(count);
		res = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, surface, &count, present_modes.data());
		return present_modes;
	}

	VkBool32 GetSurfaceSupport(std::uint32_t queue_family_index, VkSurfaceKHR surface) const
	{
		VkBool32 supported;
		auto res = vkGetPhysicalDeviceSurfaceSupportKHR(
			m_physical_device, queue_family_index, surface, &supported);
		(void)res;	// TODO
		return supported;
	}

	VkPhysicalDevice const& Get(void) const { return m_physical_device; }

private:
	VkPhysicalDevice m_physical_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP
