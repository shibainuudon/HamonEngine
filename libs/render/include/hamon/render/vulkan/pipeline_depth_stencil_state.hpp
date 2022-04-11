/**
 *	@file	pipeline_depth_stencil_state.hpp
 *
 *	@brief	PipelineDepthStencilState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/comparison_func.hpp>
#include <hamon/render/vulkan/stencil_operation.hpp>
#include <hamon/render/depth_stencil_state.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineDepthStencilStateCreateInfo
PipelineDepthStencilState(render::DepthStencilState const& state)
{
	::VkPipelineDepthStencilStateCreateInfo info{};
	info.sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	info.pNext                 = nullptr;
	info.flags                 = 0;
	info.depthTestEnable       = state.depth.enable;
	info.depthWriteEnable      = state.depth.write;
	info.depthCompareOp        = vulkan::ComparisonFunc(state.depth.func);
	info.depthBoundsTestEnable = VK_FALSE;
	info.minDepthBounds        = 0;
	info.maxDepthBounds        = 0;
	info.stencilTestEnable     = state.stencil.enable;
	info.back.failOp           = vulkan::StencilOperation(state.stencil.fail_operation);
	info.back.passOp           = vulkan::StencilOperation(state.stencil.pass_operation);
	info.back.compareOp        = vulkan::ComparisonFunc(state.stencil.func);
	info.back.compareMask      = state.stencil.read_mask;
	info.back.reference        = state.stencil.reference;
	info.back.depthFailOp      = vulkan::StencilOperation(state.stencil.depth_fail_operation);
	info.back.writeMask        = state.stencil.write_mask;
	info.front                 = info.back;
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_DEPTH_STENCIL_STATE_HPP
