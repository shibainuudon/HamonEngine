/**
 *	@file	vulkan_renderer.hpp
 *
 *	@brief	VulkanRenderer
 */

#ifndef HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP
#define HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP

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
#include <hamon/render/vulkan/pipeline_layout.hpp>
#include <hamon/render/vulkan/buffer.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/geometry.hpp>
#include <hamon/render/vulkan/program.hpp>
#include <hamon/render/vulkan/graphics_pipeline.hpp>
#include <hamon/render/vulkan/descriptor_pool.hpp>
#include <hamon/render/vulkan/descriptor_set_layout.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/render_pass_state.hpp>
#include <unordered_map>

namespace hamon
{

inline namespace render
{

#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT
#define FENCE_TIMEOUT 100000000

class VulkanRenderer : public Renderer
{
private:
	static const char* GetReportBitString(::VkDebugReportFlagsEXT flags)
	{
		if ((flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
		{
			return "INFO";
		}
		if ((flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
		{
			return "WARNING";
		}
		if ((flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
		{
			return "PERFORMANCE_WARNING";
		}
		if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
		{
			return "ERROR";
		}
		if ((flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
		{
			return "DEBUG";
		}
		return "";
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL
	DebugCallback(
		::VkDebugReportFlagsEXT      flags,
		::VkDebugReportObjectTypeEXT /*objectType*/,
		std::uint64_t              /*object*/,
		std::size_t                /*location*/,
		std::int32_t               /*messageCode*/,
		const char*                /*pLayerPrefix*/,
		const char*                pMessage,
		void*                      /*pUserData*/)
	{
		std::printf("[%s]: %s\n", GetReportBitString(flags), pMessage);
		return VK_FALSE;
	}
	
public:
	explicit VulkanRenderer(Window const& window)
	{
		const char* app_name = "HamonEngine";
		
		std::vector<const char*> instance_layer_name =
		{
#if defined(_DEBUG)
			"VK_LAYER_KHRONOS_validation",
#endif
		};

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

		m_physical_device = std::make_unique<vulkan::PhysicalDevice>(gpus[0]);	// TODO 一番良いPhysicalDeviceを選ぶ

		auto const queue_props = m_physical_device->GetQueueFamilyProperties();

		std::uint32_t graphics_queue_family_index = 0;
		for (std::uint32_t i = 0; i < queue_props.size(); ++i)
		{
			if (queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				graphics_queue_family_index = i;
				break;
			}
		}

		std::vector<const char*> device_layer_names =
		{
#if defined(_DEBUG)
			"VK_LAYER_KHRONOS_validation",
#endif
		};

		std::vector<const char*> device_extension_names;
		device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		m_device = std::make_unique<vulkan::Device>(
			m_physical_device.get(),
			device_layer_names,
			device_extension_names);

		m_command_pool = std::make_unique<vulkan::CommandPool>(
			m_device.get(),
			graphics_queue_family_index);

		m_command_buffers.push_back(std::make_unique<vulkan::CommandBuffer>(
			m_command_pool.get()));

		m_descriptor_pool = std::make_unique<vulkan::DescriptorPool>(
			m_device.get());

		m_surface = std::make_unique<vulkan::Surface>(
			m_instance.get(), window.GetNativeHandle());

		std::vector<::VkBool32> supports_present;
		for (std::uint32_t i = 0; i < queue_props.size(); i++)
		{
			supports_present.push_back(
				m_physical_device->GetSurfaceSupport(i, m_surface->Get()));
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
					present_queue_family_index = static_cast<std::uint32_t>(i);
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

		m_uniform_buffer = std::make_unique<vulkan::UniformBuffer>(
			m_device.get(),
			1024 * 1024);	// TODO
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

		m_uniform_buffer->Reset();
		m_descriptor_pool->Reset();
		m_command_buffers[0]->Begin();
	}

	void End(void) override
	{
		m_command_buffers[0]->End();

		m_graphics_queue->Submit(
			m_command_buffers[0]->Get(),
			m_image_acquired_semaphore->Get(),
			m_draw_fence->Get());
		
		::VkResult res;
		do {
			res = m_draw_fence->Wait(VK_TRUE, FENCE_TIMEOUT);
		} while (res == VK_TIMEOUT);

		m_draw_fence->Reset();

		m_present_queue->Present(m_swapchain->Get(), m_frame_index);
	}

	void BeginRenderPass(RenderPassState const& render_pass_state) override
	{
		m_command_buffers[0]->BeginRenderPass(
			m_render_pass->Get(),
			m_framebuffers[m_frame_index]->Get(),
			m_swapchain->GetExtent(),
			render_pass_state.clear_value);

		{
			::VkViewport vp;
			vp.x        = render_pass_state.viewport.left;
			vp.y        = render_pass_state.viewport.top + render_pass_state.viewport.height;
			vp.width    = render_pass_state.viewport.width;
			vp.height   = -render_pass_state.viewport.height;
			vp.minDepth = render_pass_state.viewport.min_depth;
			vp.maxDepth = render_pass_state.viewport.max_depth;
			m_command_buffers[0]->SetViewport(0, 1, &vp);
		}
		{
			::VkRect2D scissor;
			scissor.offset = {0, 0};
			scissor.extent.width  = static_cast<std::uint32_t>(render_pass_state.viewport.width);
			scissor.extent.height = static_cast<std::uint32_t>(render_pass_state.viewport.height);
			m_command_buffers[0]->SetScissor(0, 1, &scissor);
		}
	}

	void EndRenderPass(void) override
	{
		m_command_buffers[0]->EndRenderPass();
	}

private:
	template <typename T, typename Map, typename Id, typename... Args>
	typename Map::mapped_type
	GetOrCreate(Map& map, Id const& id, Args&&... args)
	{
		auto it = map.find(id);
		if (it != map.end())
		{
			return it->second;
		}
		else
		{
			auto p = std::make_shared<T>(std::forward<Args>(args)...);
			map[id] = p;
			return p;
		}
	}

public:
	void Render(
		Geometry const& geometry,
		Program const& program,
		Uniforms const& uniforms,
		RenderState const& render_state) override
	{
		auto vulkan_geometry = GetOrCreate<vulkan::Geometry>(
			m_geometry_map, geometry.GetID(), m_device.get(), geometry);
		auto vulkan_program = GetOrCreate<vulkan::Program>(
			m_program_map, program.GetID(), m_device.get(), program);
		auto pipeline_layout = GetOrCreate<vulkan::PipelineLayout>(
			m_pipeline_layout_map, program.GetID(), m_device.get(), vulkan_program->GetDescriptorSetLayouts());

		vulkan_program->LoadUniforms(m_uniform_buffer.get(), uniforms);

		auto descriptor_sets = m_descriptor_pool->AllocateDescriptorSets(
			vulkan_program->GetDescriptorSetLayouts());

		auto writes = vulkan_program->CreateWriteDescriptorSets(descriptor_sets);
		m_device->UpdateDescriptorSets(writes, {});

		auto id = render::detail::HashCombine(
			geometry.GetID(),
			program.GetID(),
			render_state);
		auto vulkan_graphics_pipeline = GetOrCreate<vulkan::GraphicsPipeline>(
			m_graphics_pipeline_map,
			id,
			m_device.get(),
			pipeline_layout.get(),
			m_render_pass.get(),
			*vulkan_program,
			geometry,
			render_state);

		vulkan_graphics_pipeline->Bind(m_command_buffers[0].get());

		m_command_buffers[0]->BindDescriptorSets(
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline_layout->Get(),
			0,
			descriptor_sets,
			{});

		vulkan_geometry->Draw(m_command_buffers[0].get());
	}

private:
	std::unique_ptr<vulkan::Instance>					m_instance;
	std::unique_ptr<vulkan::DebugReportCallback>		m_callback;
	std::unique_ptr<vulkan::PhysicalDevice>				m_physical_device;
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
	std::unique_ptr<vulkan::DescriptorPool>				m_descriptor_pool;
	std::unique_ptr<vulkan::UniformBuffer>				m_uniform_buffer;

	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::Program>>	m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::Geometry>>	m_geometry_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::PipelineLayout>>	m_pipeline_layout_map;
	std::unordered_map<std::size_t, std::shared_ptr<vulkan::GraphicsPipeline>>	m_graphics_pipeline_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_VULKAN_RENDERER_HPP
