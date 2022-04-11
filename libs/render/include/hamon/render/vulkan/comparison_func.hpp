/**
 *	@file	comparison_func.hpp
 *
 *	@brief	ComparisonFunc
 */

#ifndef HAMON_RENDER_VULKAN_COMPARISON_FUNC_HPP
#define HAMON_RENDER_VULKAN_COMPARISON_FUNC_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/comparison_func.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkCompareOp
ComparisonFunc(render::ComparisonFunc mode)
{
	switch (mode)
	{
	case render::ComparisonFunc::Never:			return VK_COMPARE_OP_NEVER;
	case render::ComparisonFunc::Less:			return VK_COMPARE_OP_LESS;
	case render::ComparisonFunc::Equal:			return VK_COMPARE_OP_EQUAL;
	case render::ComparisonFunc::LessEqual:		return VK_COMPARE_OP_LESS_OR_EQUAL;
	case render::ComparisonFunc::Greater:		return VK_COMPARE_OP_GREATER;
	case render::ComparisonFunc::NotEqual:		return VK_COMPARE_OP_NOT_EQUAL;
	case render::ComparisonFunc::GreaterEqual:	return VK_COMPARE_OP_GREATER_OR_EQUAL;
	case render::ComparisonFunc::Always:		return VK_COMPARE_OP_ALWAYS;
	}
	return VK_COMPARE_OP_NEVER;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_COMPARISON_FUNC_HPP
