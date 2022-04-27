/**
 *	@file	debug_report_callback.hpp
 *
 *	@brief	DebugReportCallback
 */

#ifndef HAMON_RENDER_VULKAN_DEBUG_REPORT_CALLBACK_HPP
#define HAMON_RENDER_VULKAN_DEBUG_REPORT_CALLBACK_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/instance.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class DebugReportCallback
{
public:
	DebugReportCallback(
		vulkan::Instance* instance,
		::VkDebugReportFlagsEXT flags,
		::PFN_vkDebugReportCallbackEXT callback)
		: m_instance(instance)
	{
		::VkDebugReportCallbackCreateInfoEXT info{};
		info.sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		info.flags       = flags;
		info.pfnCallback = callback;
		m_callback = m_instance->CreateDebugReportCallback(info);
	}

	~DebugReportCallback()
	{
		m_instance->DestroyDebugReportCallback(m_callback);
	}

private:
	::VkDebugReportCallbackEXT	m_callback;
	vulkan::Instance*			m_instance;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_DEBUG_REPORT_CALLBACK_HPP
