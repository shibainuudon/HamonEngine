/**
 *	@file	pipeline_viewport_state.hpp
 *
 *	@brief	PipelineViewportState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_VIEWPORT_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_VIEWPORT_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineViewportStateCreateInfo
PipelineViewportState(void)
{
	::VkPipelineViewportStateCreateInfo info {};
	info.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	info.pNext         = nullptr;
	info.flags         = 0;
	info.viewportCount = 1;
	info.scissorCount  = 1;
	info.pScissors     = nullptr;
	info.pViewports    = nullptr;
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_VIEWPORT_STATE_HPP
