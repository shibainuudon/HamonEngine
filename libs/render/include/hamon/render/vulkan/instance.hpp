/**
 *	@file	instance.hpp
 *
 *	@brief	Instance
 */

#ifndef HAMON_RENDER_VULKAN_INSTANCE_HPP
#define HAMON_RENDER_VULKAN_INSTANCE_HPP

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Instance
{
public:
	Instance(
		const char* app_name,
		std::vector<const char*> const& layer_names,
		std::vector<const char*> const& extension_names)
	{
		VkApplicationInfo app_info = {};
		app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext              = nullptr;
		app_info.pApplicationName   = app_name;
		app_info.applicationVersion = 1;
		app_info.pEngineName        = app_name;
		app_info.engineVersion      = 1;
		app_info.apiVersion         = VK_API_VERSION_1_0;

		VkInstanceCreateInfo inst_info = {};
		inst_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		inst_info.pNext                   = nullptr;
		inst_info.flags                   = 0;
		inst_info.pApplicationInfo        = &app_info;
		inst_info.enabledExtensionCount   = extension_names.size();
		inst_info.ppEnabledExtensionNames = extension_names.empty() ? nullptr : extension_names.data();
		inst_info.enabledLayerCount       = layer_names.size();
		inst_info.ppEnabledLayerNames     = layer_names.empty() ? nullptr : layer_names.data();

		auto res = vkCreateInstance(&inst_info, nullptr, &m_instance);
	}

	~Instance()
	{
		vkDestroyInstance(m_instance, nullptr);
	}

	std::vector<VkPhysicalDevice> EnumeratePhysicalDevices()
	{
		VkResult res;
		std::uint32_t gpu_count;
		res = vkEnumeratePhysicalDevices(m_instance, &gpu_count, nullptr);
		std::vector<VkPhysicalDevice> gpus(gpu_count);
		res = vkEnumeratePhysicalDevices(m_instance, &gpu_count, gpus.data());
		return gpus;
	}

	VkDebugReportCallbackEXT CreateDebugReportCallback(
		VkDebugReportCallbackCreateInfoEXT const& info)
	{
		VkDebugReportCallbackEXT callback;
		auto res = vkCreateDebugReportCallbackEXT(m_instance, &info, nullptr, &callback);
		return callback;
	}
	
	void DestroyDebugReportCallback(VkDebugReportCallbackEXT const& callback)
	{
		vkDestroyDebugReportCallbackEXT(m_instance, callback, nullptr);
	}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkSurfaceKHR CreateSurface(VkWin32SurfaceCreateInfoKHR const& info)
	{
		VkSurfaceKHR surface;
		auto res = vkCreateWin32SurfaceKHR(m_instance, &info, nullptr, &surface);
		return surface;
	}
#endif

	void DestroySurface(VkSurfaceKHR const& surface)
	{
		vkDestroySurfaceKHR(m_instance, surface, nullptr);
	}

private:
	VkInstance m_instance;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_INSTANCE_HPP
