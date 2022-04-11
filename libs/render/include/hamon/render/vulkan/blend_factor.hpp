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
	case render::BlendFactor::Zero:				return VK_BLEND_FACTOR_ZERO;
	case render::BlendFactor::One:				return VK_BLEND_FACTOR_ONE;
	case render::BlendFactor::SrcColor:			return VK_BLEND_FACTOR_SRC_COLOR;
	case render::BlendFactor::InvSrcColor:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
	case render::BlendFactor::SrcAlpha:			return VK_BLEND_FACTOR_SRC_ALPHA;
	case render::BlendFactor::InvSrcAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	case render::BlendFactor::DestAlpha:		return VK_BLEND_FACTOR_DST_ALPHA;
	case render::BlendFactor::InvDestAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
	case render::BlendFactor::DestColor:		return VK_BLEND_FACTOR_DST_COLOR;
	case render::BlendFactor::InvDestColor:		return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
	case render::BlendFactor::SrcAlphaSat:		return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
	case render::BlendFactor::BlendFactor:		return VK_BLEND_FACTOR_CONSTANT_COLOR;
	case render::BlendFactor::InvBlendFactor:	return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
	case render::BlendFactor::Src1Color:		return VK_BLEND_FACTOR_SRC1_COLOR;
	case render::BlendFactor::InvSrc1Color:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
	case render::BlendFactor::Src1Alpha:		return VK_BLEND_FACTOR_SRC1_ALPHA;
	case render::BlendFactor::InvSrc1Alpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
	}
	return VK_BLEND_FACTOR_ZERO;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BLEND_FACTOR_HPP
