/**
 *	@file	pipeline_layout.hpp
 *
 *	@brief	PipelineLayout
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_LAYOUT_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_LAYOUT_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/throw_if_failed.hpp>
#include <hamon/render/vulkan/device.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class PipelineLayout
{
public:
	explicit PipelineLayout(vulkan::Device* device)
		: m_device(device)
	{
		::VkPipelineLayoutCreateInfo info = {};
		info.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		info.pNext                  = nullptr;
		info.pushConstantRangeCount = 0;
		info.pPushConstantRanges    = nullptr;
		info.setLayoutCount         = 0;
		info.pSetLayouts            = nullptr;

		m_pipeline_layout = m_device->CreatePipelineLayout(info);
	}

	~PipelineLayout()
	{
		m_device->DestroyPipelineLayout(m_pipeline_layout);
	}

	::VkPipelineLayout Get(void) const { return m_pipeline_layout; }

private:
	::VkPipelineLayout m_pipeline_layout;
	vulkan::Device* m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_pipeline_layout_HPP
