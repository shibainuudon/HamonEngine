/**
 *	@file	instance.hpp
 *
 *	@brief	Instance
 */

#ifndef HAMON_RENDER_VULKAN_INSTANCE_HPP
#define HAMON_RENDER_VULKAN_INSTANCE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/vulkan_ext.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <hamon/render/vulkan/array_proxy.hpp>
#include <vector>
#include <cstdint>
#include <algorithm>

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
		std::vector<const char*> const& required_layer_names,
		std::vector<const char*> const& required_extension_names)
	{
		std::vector<const char*> layer_names;
		auto const available_layer_names = EnumerateInstanceLayerNames();
		for (auto const& required_layer_name : required_layer_names)
		{
			if (std::ranges::find(
				available_layer_names,
				required_layer_name) != available_layer_names.end())
			{
				layer_names.push_back(required_layer_name);
			}
		}

		std::vector<const char*> extension_names;
		auto const available_extension_names = EnumerateInstanceExtensionNames();
		for (auto const& required_extension_name : required_extension_names)
		{
			if (std::ranges::find(
				available_extension_names,
				required_extension_name) != available_extension_names.end())
			{
				extension_names.push_back(required_extension_name);
			}
		}

		Create(app_name, layer_names, extension_names);
	}

private:
	static std::vector<std::string>
	EnumerateInstanceLayerNames()
	{
		std::vector<std::string> layer_names;
		for (auto const& layer_property : EnumerateInstanceLayerProperties())
		{
			layer_names.push_back(layer_property.layerName);
		}
		return layer_names;
	}

	static std::vector<std::string>
	EnumerateInstanceExtensionNames()
	{
		std::vector<std::string> extension_names;
		for (auto const& extension_property : EnumerateInstanceExtensionProperties(nullptr))
		{
			extension_names.push_back(extension_property.extensionName);
		}
		for (auto const& layer_names : EnumerateInstanceLayerNames())
		{
			for (auto const& extension_property : EnumerateInstanceExtensionProperties(layer_names.c_str()))
			{
				extension_names.push_back(extension_property.extensionName);
			}
		}
		return extension_names;
	}

	static std::vector<::VkLayerProperties>
	EnumerateInstanceLayerProperties()
	{
		std::uint32_t property_count;
		ThrowIfFailed(::vkEnumerateInstanceLayerProperties(&property_count, nullptr));
		std::vector<::VkLayerProperties> properties(property_count);
		ThrowIfFailed(::vkEnumerateInstanceLayerProperties(&property_count, properties.data()));
		return properties;
	}

	static std::vector<::VkExtensionProperties>
	EnumerateInstanceExtensionProperties(const char* layer_name)
	{
		std::uint32_t property_count;
		ThrowIfFailed(::vkEnumerateInstanceExtensionProperties(layer_name, &property_count, nullptr));
		std::vector<::VkExtensionProperties> properties(property_count);
		ThrowIfFailed(::vkEnumerateInstanceExtensionProperties(layer_name, &property_count, properties.data()));
		return properties;
	}

	void Create(
		const char* app_name,
		vulkan::ArrayProxy<const char*> layer_names,
		vulkan::ArrayProxy<const char*> extension_names)
	{
		::VkApplicationInfo app_info {};
		app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext              = nullptr;
		app_info.pApplicationName   = app_name;
		app_info.applicationVersion = 1;
		app_info.pEngineName        = app_name;
		app_info.engineVersion      = 1;
		app_info.apiVersion         = VK_API_VERSION_1_0;

		::VkInstanceCreateInfo inst_info {};
		inst_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		inst_info.pNext                   = nullptr;
		inst_info.flags                   = 0;
		inst_info.pApplicationInfo        = &app_info;
		inst_info.enabledExtensionCount   = extension_names.GetSize();
		inst_info.ppEnabledExtensionNames = extension_names.GetData();
		inst_info.enabledLayerCount       = layer_names.GetSize();
		inst_info.ppEnabledLayerNames     = layer_names.GetData();

		ThrowIfFailed(::vkCreateInstance(&inst_info, nullptr, &m_instance));
	}

public:
	~Instance()
	{
		::vkDestroyInstance(m_instance, nullptr);
	}

	std::vector<::VkPhysicalDevice> EnumeratePhysicalDevices()
	{
		std::uint32_t gpu_count;
		ThrowIfFailed(vkEnumeratePhysicalDevices(m_instance, &gpu_count, nullptr));
		std::vector<::VkPhysicalDevice> gpus(gpu_count);
		ThrowIfFailed(vkEnumeratePhysicalDevices(m_instance, &gpu_count, gpus.data()));
		return gpus;
	}

	::VkDebugReportCallbackEXT CreateDebugReportCallback(
		::VkDebugReportCallbackCreateInfoEXT const& info)
	{
		::VkDebugReportCallbackEXT callback;
		ThrowIfFailed(vulkan::vkCreateDebugReportCallbackEXT(m_instance, &info, nullptr, &callback));
		return callback;
	}
	
	void DestroyDebugReportCallback(::VkDebugReportCallbackEXT const& callback)
	{
		vulkan::vkDestroyDebugReportCallbackEXT(m_instance, callback, nullptr);
	}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
	::VkSurfaceKHR CreateSurface(::VkWin32SurfaceCreateInfoKHR const& info)
	{
		::VkSurfaceKHR surface;
		ThrowIfFailed(vkCreateWin32SurfaceKHR(m_instance, &info, nullptr, &surface));
		return surface;
	}
#endif

	void DestroySurface(::VkSurfaceKHR const& surface)
	{
		vkDestroySurfaceKHR(m_instance, surface, nullptr);
	}

private:
	::VkInstance m_instance;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_INSTANCE_HPP
