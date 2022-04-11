/**
 *	@file	pipeline_input_assembly_state.hpp
 *
 *	@brief	PipelineInputAssemblyState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/primitive_topology.hpp>
#include <hamon/render/primitive_topology.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineInputAssemblyStateCreateInfo
PipelineInputAssemblyState(render::PrimitiveTopology primitive_topology)
{
	::VkPipelineInputAssemblyStateCreateInfo info{};
	info.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.pNext                  = nullptr;
	info.flags                  = 0;
	info.primitiveRestartEnable = VK_FALSE;
	info.topology               = vulkan::PrimitiveTopology(primitive_topology);
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_HPP
