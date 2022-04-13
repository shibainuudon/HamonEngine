/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage
 */

#ifndef HAMON_RENDER_VULKAN_SHADER_STAGE_HPP
#define HAMON_RENDER_VULKAN_SHADER_STAGE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/shader_stage.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkShaderStageFlagBits ShaderStage(render::ShaderStage stage)
{
	switch (stage)
	{
	case render::ShaderStage::Compute:					return VK_SHADER_STAGE_COMPUTE_BIT;
	case render::ShaderStage::Vertex:					return VK_SHADER_STAGE_VERTEX_BIT;
	case render::ShaderStage::Geometry:					return VK_SHADER_STAGE_GEOMETRY_BIT;
	case render::ShaderStage::TessellationControl:		return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	case render::ShaderStage::TessellationEvaluation:	return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	case render::ShaderStage::Fragment:					return VK_SHADER_STAGE_FRAGMENT_BIT;
	}
	return VK_SHADER_STAGE_VERTEX_BIT;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SHADER_STAGE_HPP
