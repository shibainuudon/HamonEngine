/**
 *	@file	pipeline_shader_stage.hpp
 *
 *	@brief	PipelineShaderStage
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_SHADER_STAGE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_SHADER_STAGE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/shader.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPipelineShaderStageCreateInfo
PipelineShaderStage(vulkan::Shader const& shader)
{
	::VkPipelineShaderStageCreateInfo info{};
	info.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.pNext               = nullptr;
	info.flags               = 0;
	info.stage               = shader.GetStage();
	info.module              = shader.GetModule();
	info.pName               = "main";	// TODO
	info.pSpecializationInfo = nullptr;
	return info;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_SHADER_STAGE_HPP
