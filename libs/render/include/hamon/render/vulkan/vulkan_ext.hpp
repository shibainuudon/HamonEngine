/**
 *	@file	vulkan_ext.hpp
 *
 *	@brief
 */

#ifndef HAMON_RENDER_VULKAN_VULKAN_EXT_HPP
#define HAMON_RENDER_VULKAN_VULKAN_EXT_HPP

#include <hamon/render/vulkan/vulkan.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline VkResult vkCreateDebugReportCallbackEXT(
	VkInstance                                instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	static auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	return func(instance, pCreateInfo, pAllocator, pCallback);
}

inline void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
	VkInstance                   instance,
	VkDebugReportCallbackEXT     callback,
	const VkAllocationCallbacks* pAllocator)
{
	static auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	return func(instance, callback, pAllocator);
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_VULKAN_EXT_HPP
