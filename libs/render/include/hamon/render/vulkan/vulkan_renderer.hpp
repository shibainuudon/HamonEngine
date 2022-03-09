/**
 *	@file	vulkan_renderer.hpp
 *
 *	@brief	VulkanRenderer
 */

#ifndef HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP
#define HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include <hamon/render/vulkan/instance.hpp>
#include <hamon/render/vulkan/debug_report_callback.hpp>
#include <hamon/render/vulkan/surface.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/command_pool.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/vulkan/semaphore.hpp>
#include <hamon/render/vulkan/fence.hpp>
#include <hamon/render/vulkan/swapchain.hpp>
#include <hamon/render/vulkan/physical_device.hpp>
#include <hamon/render/vulkan/image_view.hpp>
#include <hamon/render/vulkan/render_pass.hpp>
#include <hamon/render/vulkan/framebuffer.hpp>
#include <hamon/render/vulkan/queue.hpp>

inline VkResult vkCreateDebugReportCallbackEXT(
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	static auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	return func(instance, pCreateInfo, pAllocator, pCallback);
}

inline void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
	VkInstance                                  instance,
	VkDebugReportCallbackEXT                    callback,
	const VkAllocationCallbacks* pAllocator)
{
	static auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	return func(instance, callback, pAllocator);
}

namespace hamon
{

inline namespace render
{

#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT
#define FENCE_TIMEOUT 100000000

class VulkanRenderer : public Renderer
{
public:
	static VKAPI_ATTR VkBool32 VKAPI_CALL
	DebugCallback(
		VkDebugReportFlagsEXT                       flags,
		VkDebugReportObjectTypeEXT                  objectType,
		uint64_t                                    object,
		size_t                                      location,
		int32_t                                     messageCode,
		const char* pLayerPrefix,
		const char* pMessage,
		void* pUserData)
	{
		std::printf("%s", pMessage);
		return VK_FALSE;
	}
	
	explicit VulkanRenderer(Window const& window)
	{
		VkResult res;
		const char* app_name = "HamonEngine";
		
		std::vector<const char*> instance_layer_name;

		std::vector<const char*> instance_extension_names;
		instance_extension_names.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		instance_extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef __ANDROID__
		instance_extension_names.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_WIN32)
		instance_extension_names.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_METAL_EXT)
		instance_extension_names.push_back(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
		instance_extension_names.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#else
		instance_extension_names.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#endif

		m_instance = std::make_unique<vulkan::Instance>(
			app_name,
			instance_layer_name,
			instance_extension_names);

		m_callback = std::make_unique<vulkan::DebugReportCallback>(
			m_instance.get(),
			VK_DEBUG_REPORT_ERROR_BIT_EXT |
			VK_DEBUG_REPORT_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_INFORMATION_BIT_EXT,
			&DebugCallback);

		auto gpus = m_instance->EnumeratePhysicalDevices();

		vulkan::PhysicalDevice physical_device(gpus[0]);	// TODO 一番良いPhysicalDeviceを選ぶ

		auto const queue_props = physical_device.GetQueueFamilyProperties();

		std::uint32_t graphics_queue_family_index = 0;
		for (std::uint32_t i = 0; i < queue_props.size(); ++i)
		{
			if (queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				graphics_queue_family_index = i;
				break;
			}
		}

		std::vector<const char*> device_layer_names;

		std::vector<const char*> device_extension_names;
		device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		m_device = std::make_unique<vulkan::Device>(
			physical_device.Get(),
			device_layer_names,
			device_extension_names);

		m_command_pool = std::make_unique<vulkan::CommandPool>(
			m_device.get(),
			graphics_queue_family_index);

		m_command_buffers.push_back(std::make_unique<vulkan::CommandBuffer>(
			m_command_pool.get()));

		m_surface = std::make_unique<vulkan::Surface>(
			m_instance.get(), window.GetNativeHandle());

		std::vector<VkBool32> supports_present;
		for (std::uint32_t i = 0; i < queue_props.size(); i++)
		{
			supports_present.push_back(
				physical_device.GetSurfaceSupport(i, m_surface->Get()));
		}

		// Graphics かつ Present な QueueFamily が見つかったら、
		// それをgraphics_queue_family_indexとpresent_queue_family_indexにする
		graphics_queue_family_index = UINT32_MAX;
		std::uint32_t present_queue_family_index = UINT32_MAX;
		for (uint32_t i = 0; i < queue_props.size(); ++i)
		{
			if ((queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
			{
				if (graphics_queue_family_index == UINT32_MAX)
				{
					graphics_queue_family_index = i;
				}

				if (supports_present[i] == VK_TRUE)
				{
					graphics_queue_family_index = i;
					present_queue_family_index = i;
					break;
				}
			}
		}

		// Graphics かつ Present な QueueFamily が見つからなかったら、
		// GraphicsとPresentそれぞれのIndexを設定する
		if (present_queue_family_index == UINT32_MAX)
		{
			for (std::size_t i = 0; i < queue_props.size(); ++i)
			{
				if (supports_present[i] == VK_TRUE)
				{
					present_queue_family_index = i;
					break;
				}
			}
		}

		m_graphics_queue = std::make_unique<vulkan::Queue>(
			m_device->GetDeviceQueue(graphics_queue_family_index, 0));
		m_present_queue = std::make_unique<vulkan::Queue>(
			m_device->GetDeviceQueue(present_queue_family_index, 0));

		m_swapchain = std::make_unique<vulkan::Swapchain>(
			m_device.get(),
			&physical_device,
			m_surface.get(),
			window.GetClientWidth(),
			window.GetClientHeight(),
			graphics_queue_family_index,
			present_queue_family_index);

		for (auto& swapchain_image : m_swapchain->GetImages())
		{
			m_swapchain_image_views.push_back(
				std::make_unique<vulkan::ImageView>(
					m_device.get(), swapchain_image, m_swapchain->GetFormat()));
		}

		m_image_acquired_semaphore = std::make_unique<vulkan::Semaphore>(m_device.get());

		m_render_pass = std::make_unique<vulkan::RenderPass>(
			m_device.get(), m_swapchain->GetFormat(), NUM_SAMPLES);

		for (auto& swapchain_image_view : m_swapchain_image_views)
		{
			m_framebuffers.push_back(
				std::make_unique<vulkan::Framebuffer>(
					m_device.get(),
					m_render_pass->Get(),
					std::vector<VkImageView>{swapchain_image_view->Get()},
					m_swapchain->GetExtent()));
		}

		m_draw_fence = std::make_unique<vulkan::Fence>(m_device.get());
	}

	~VulkanRenderer()
	{
	}

	void Begin(void) override
	{
		m_frame_index = m_swapchain->AcquireNextImage(
			UINT64_MAX,
			m_image_acquired_semaphore->Get(),
			VK_NULL_HANDLE);

		m_command_buffers[0]->Begin();
		m_command_buffers[0]->BeginRenderPass(
			m_render_pass->Get(),
			m_framebuffers[m_frame_index]->Get(),
			m_swapchain->GetExtent());
	}

	void End(void) override
	{
		m_command_buffers[0]->EndRenderPass();

		m_command_buffers[0]->End();

		m_graphics_queue->Submit(
			m_command_buffers[0]->Get(),
			m_image_acquired_semaphore->Get(),
			m_draw_fence->Get());
		
		VkResult res;
		do {
			res = m_device->WaitForFences(1, &m_draw_fence->Get(), VK_TRUE, FENCE_TIMEOUT);
		} while (res == VK_TIMEOUT);

		m_present_queue->Present(m_swapchain->Get(), m_frame_index);
	}

private:
	std::unique_ptr<vulkan::Instance>					m_instance;
	std::unique_ptr<vulkan::DebugReportCallback>		m_callback;
	std::unique_ptr<vulkan::Device>						m_device;
	std::unique_ptr<vulkan::CommandPool>				m_command_pool;
	std::vector<std::unique_ptr<vulkan::CommandBuffer>>	m_command_buffers;
	std::unique_ptr<vulkan::Surface>					m_surface;
	std::unique_ptr<vulkan::Swapchain>					m_swapchain;
	std::vector<std::unique_ptr<vulkan::ImageView>>		m_swapchain_image_views;
	std::vector<std::unique_ptr<vulkan::Framebuffer>>	m_framebuffers;
	std::unique_ptr<vulkan::Semaphore>					m_image_acquired_semaphore;
	std::unique_ptr<vulkan::RenderPass>					m_render_pass;
	std::unique_ptr<vulkan::Fence>						m_draw_fence;
	std::unique_ptr<vulkan::Queue>						m_graphics_queue;
	std::unique_ptr<vulkan::Queue>						m_present_queue;
	std::uint32_t										m_frame_index;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP
