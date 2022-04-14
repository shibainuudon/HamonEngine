/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor
 */

#ifndef HAMON_RENDER_VULKAN_BLEND_FACTOR_HPP
#define HAMON_RENDER_VULKAN_BLEND_FACTOR_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/blend_factor.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkBlendFactor
BlendFactor(render::BlendFactor factor)
{
	switch (factor)
	{
	case render::BlendFactor::Zero:					return VK_BLEND_FACTOR_ZERO;
	case render::BlendFactor::One:					return VK_BLEND_FACTOR_ONE;
	case render::BlendFactor::SrcColor:				return VK_BLEND_FACTOR_SRC_COLOR;
	case render::BlendFactor::OneMinusSrcColor:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
	case render::BlendFactor::DstColor:				return VK_BLEND_FACTOR_DST_COLOR;
	case render::BlendFactor::OneMinusDstColor:		return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
	case render::BlendFactor::SrcAlpha:				return VK_BLEND_FACTOR_SRC_ALPHA;
	case render::BlendFactor::OneMinusSrcAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	case render::BlendFactor::DstAlpha:				return VK_BLEND_FACTOR_DST_ALPHA;
	case render::BlendFactor::OneMinusDstAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
	case render::BlendFactor::ConstantColor:		return VK_BLEND_FACTOR_CONSTANT_COLOR;
	case render::BlendFactor::OneMinusConstantColor:return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
	case render::BlendFactor::ConstantAlpha:		return VK_BLEND_FACTOR_CONSTANT_ALPHA;
	case render::BlendFactor::OneMinusConstantAlpha:return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
	case render::BlendFactor::SrcAlphaSaturate:		return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
	case render::BlendFactor::Src1Color:			return VK_BLEND_FACTOR_SRC1_COLOR;
	case render::BlendFactor::OneMinusSrc1Color:	return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
	case render::BlendFactor::Src1Alpha:			return VK_BLEND_FACTOR_SRC1_ALPHA;
	case render::BlendFactor::OneMinusSrc1Alpha:	return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
	}
	return VK_BLEND_FACTOR_ZERO;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BLEND_FACTOR_HPP
