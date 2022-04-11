/**
 *	@file	pipeline_multisample_state.hpp
 *
 *	@brief	PipelineMultisampleState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_MULTISAMPLE_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_MULTISAMPLE_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineMultisampleStateCreateInfo
PipelineMultisampleState(::VkSampleCountFlagBits samples)
{
	::VkPipelineMultisampleStateCreateInfo info{};
	info.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	info.pNext                 = nullptr;
	info.flags                 = 0;
	info.pSampleMask           = nullptr;
	info.rasterizationSamples  = samples;
	info.sampleShadingEnable   = VK_FALSE;
	info.alphaToCoverageEnable = VK_FALSE;
	info.alphaToOneEnable      = VK_FALSE;
	info.minSampleShading      = 0.0;
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_MULTISAMPLE_STATE_HPP
