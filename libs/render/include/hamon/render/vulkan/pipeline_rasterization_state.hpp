/**
 *	@file	pipeline_rasterization_state.hpp
 *
 *	@brief	PipelineRasterizationState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_RASTERIZATION_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_RASTERIZATION_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/fill_mode.hpp>
#include <hamon/render/vulkan/cull_mode.hpp>
#include <hamon/render/vulkan/front_face.hpp>
#include <hamon/render/rasterizer_state.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineRasterizationStateCreateInfo
PipelineRasterizationState(render::RasterizerState const& state)
{
	::VkPipelineRasterizationStateCreateInfo info{};
	info.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	info.pNext                   = nullptr;
	info.flags                   = 0;
	info.polygonMode             = vulkan::FillMode(state.fill_mode);
	info.cullMode                = vulkan::CullMode(state.cull_mode);
	info.frontFace               = vulkan::FrontFace(state.front_face);
	info.depthClampEnable        = VK_FALSE;
	info.rasterizerDiscardEnable = VK_FALSE;
	info.depthBiasEnable         = VK_FALSE;
	info.depthBiasConstantFactor = 0;
	info.depthBiasClamp          = 0;
	info.depthBiasSlopeFactor    = 0;
	info.lineWidth               = 1.0f;
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_RASTERIZATION_STATE_HPP
