/**
 *	@file	surface.hpp
 *
 *	@brief	Surface
 */

#ifndef HAMON_RENDER_VULKAN_SURFACE_HPP
#define HAMON_RENDER_VULKAN_SURFACE_HPP

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Surface
{
public:
	Surface(vulkan::Instance* instance, ::HWND hwnd)
		: m_instance(instance)
	{
#ifdef _WIN32
		VkWin32SurfaceCreateInfoKHR info = {};
		info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		info.pNext = nullptr;
		info.hinstance = GetModuleHandle(nullptr);
		info.hwnd = hwnd;
#elif defined(__ANDROID__)
		VkAndroidSurfaceCreateInfoKHR info;
		info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
		info.pNext = nullptr;
		info.flags = 0;
		info.window = AndroidGetApplicationWindow();
		res = vkCreateAndroidSurfaceKHR(info.inst, &info, nullptr, &m_surface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
		VkWaylandSurfaceCreateInfoKHR info = {};
		info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
		info.pNext = nullptr;
		info.display = info.display;
		info.surface = info.window;
		res = vkCreateWaylandSurfaceKHR(info.inst, &info, nullptr, &m_surface);
#else
		VkXcbSurfaceCreateInfoKHR info = {};
		info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
		info.pNext = nullptr;
		info.connection = info.connection;
		info.window = info.window;
		res = vkCreateXcbSurfaceKHR(info.inst, &info, nullptr, &m_surface);
#endif  // _WIN32
		m_surface = m_instance->CreateSurface(info);
	}

	~Surface()
	{
		m_instance->DestroySurface(m_surface);
	}

	VkSurfaceKHR const& Get(void) const { return m_surface; }

private:
	VkSurfaceKHR m_surface;
	vulkan::Instance* m_instance;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SURFACE_HPP
