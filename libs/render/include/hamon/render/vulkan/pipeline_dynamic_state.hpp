/**
 *	@file	pipeline_dynamic_state.hpp
 *
 *	@brief	PipelineDynamicState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/array_proxy.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineDynamicStateCreateInfo
PipelineDynamicState(vulkan::ArrayProxy<::VkDynamicState> dynamic_state_enables)
{
	::VkPipelineDynamicStateCreateInfo info {};
	info.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	info.pNext             = nullptr;
	info.flags             = 0;
	info.dynamicStateCount = dynamic_state_enables.GetSize();
	info.pDynamicStates    = dynamic_state_enables.GetData();
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP
