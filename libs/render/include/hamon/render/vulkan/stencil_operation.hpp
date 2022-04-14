/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation
 */

#ifndef HAMON_RENDER_VULKAN_STENCIL_OPERATION_HPP
#define HAMON_RENDER_VULKAN_STENCIL_OPERATION_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/stencil_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkStencilOp
StencilOperation(render::StencilOperation op)
{
	switch (op)
	{
	case render::StencilOperation::Keep:				return VK_STENCIL_OP_KEEP;
	case render::StencilOperation::Zero:				return VK_STENCIL_OP_ZERO;
	case render::StencilOperation::Replace:				return VK_STENCIL_OP_REPLACE;
	case render::StencilOperation::IncrementAndClamp:	return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
	case render::StencilOperation::DecrementAndClamp:	return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
	case render::StencilOperation::Invert:				return VK_STENCIL_OP_INVERT;
	case render::StencilOperation::IncrementAndWrap:	return VK_STENCIL_OP_INCREMENT_AND_WRAP;
	case render::StencilOperation::DecrementAndWrap:	return VK_STENCIL_OP_DECREMENT_AND_WRAP;
	}
	return VK_STENCIL_OP_KEEP;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_STENCIL_OPERATION_HPP
