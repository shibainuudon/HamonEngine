/**
 *	@file	compare_operation.hpp
 *
 *	@brief	CompareOperation
 */

#ifndef HAMON_RENDER_VULKAN_compare_operation_HPP
#define HAMON_RENDER_VULKAN_compare_operation_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/compare_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkCompareOp
CompareOperation(render::CompareOperation op)
{
	switch (op)
	{
	case render::CompareOperation::Never:			return VK_COMPARE_OP_NEVER;
	case render::CompareOperation::Less:			return VK_COMPARE_OP_LESS;
	case render::CompareOperation::Equal:			return VK_COMPARE_OP_EQUAL;
	case render::CompareOperation::LessEqual:		return VK_COMPARE_OP_LESS_OR_EQUAL;
	case render::CompareOperation::Greater:			return VK_COMPARE_OP_GREATER;
	case render::CompareOperation::NotEqual:		return VK_COMPARE_OP_NOT_EQUAL;
	case render::CompareOperation::GreaterEqual:	return VK_COMPARE_OP_GREATER_OR_EQUAL;
	case render::CompareOperation::Always:			return VK_COMPARE_OP_ALWAYS;
	}
	return VK_COMPARE_OP_NEVER;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_compare_operation_HPP
