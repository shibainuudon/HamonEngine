/**
 *	@file	physical_device.hpp
 *
 *	@brief	PhysicalDevice
 */

#ifndef HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP
#define HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
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

	::VkDevice CreateDevice(::VkDeviceCreateInfo const& info)
	{
		::VkDevice device;
		ThrowIfFailed(vkCreateDevice(m_physical_device, &info, nullptr, &device));
		return device;
	}

	void DestroyDevice(::VkDevice device)
	{
		vkDestroyDevice(device, nullptr);
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
		std::uint32_t count;
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, nullptr));
		std::vector<VkSurfaceFormatKHR> formats(count);
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, formats.data()));
		return formats;
	}

	VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkSurfaceKHR surface) const
	{
		VkSurfaceCapabilitiesKHR capabilities;
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, surface, &capabilities));
		return capabilities;
	}

	std::vector<VkPresentModeKHR> GetSurfacePresentModes(VkSurfaceKHR surface) const
	{
		std::uint32_t count;
		ThrowIfFailed(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, surface, &count, nullptr));
		std::vector<VkPresentModeKHR> present_modes(count);
		ThrowIfFailed(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, surface, &count, present_modes.data()));
		return present_modes;
	}

	VkBool32 GetSurfaceSupport(std::uint32_t queue_family_index, VkSurfaceKHR surface) const
	{
		VkBool32 supported;
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceSupportKHR(
			m_physical_device, queue_family_index, surface, &supported));
		return supported;
	}

	::VkPhysicalDeviceMemoryProperties GetMemoryProperties(void) const
	{
		::VkPhysicalDeviceMemoryProperties memory_properties;
		::vkGetPhysicalDeviceMemoryProperties(m_physical_device, &memory_properties);
		return memory_properties;
	}

	VkPhysicalDevice const& Get(void) const { return m_physical_device; }

private:
	VkPhysicalDevice m_physical_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PHYSICAL_DEVICE_HPP
