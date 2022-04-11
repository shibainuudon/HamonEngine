/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation
 */

#ifndef HAMON_RENDER_VULKAN_BLEND_OPERATION_HPP
#define HAMON_RENDER_VULKAN_BLEND_OPERATION_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/blend_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkBlendOp
BlendOperation(render::BlendOperation op)
{
	switch (op)
	{
	case render::BlendOperation::Add:				return VK_BLEND_OP_ADD;
	case render::BlendOperation::Subtract:			return VK_BLEND_OP_SUBTRACT;
	case render::BlendOperation::ReverseSubtract:	return VK_BLEND_OP_REVERSE_SUBTRACT;
	case render::BlendOperation::Min:				return VK_BLEND_OP_MIN;
	case render::BlendOperation::Max:				return VK_BLEND_OP_MAX;
	}
	return VK_BLEND_OP_ADD;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BLEND_OPERATION_HPP
