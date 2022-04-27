/**
 *	@file	pipeline_dynamic_state.hpp
 *
 *	@brief	PipelineDynamicState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineDynamicStateCreateInfo
PipelineDynamicState(std::vector<::VkDynamicState> const& dynamic_state_enables)
{
	::VkPipelineDynamicStateCreateInfo info {};
	info.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	info.pNext             = nullptr;
	info.flags             = 0;
	info.dynamicStateCount = static_cast<std::uint32_t>(dynamic_state_enables.size());
	info.pDynamicStates    = dynamic_state_enables.data();
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_DYNAMIC_STATE_HPP
