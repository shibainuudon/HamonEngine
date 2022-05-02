/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor
 */

#ifndef HAMON_RENDER_VULKAN_BORDER_COLOR_HPP
#define HAMON_RENDER_VULKAN_BORDER_COLOR_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/border_color.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkBorderColor
BorderColor(render::BorderColor border_color)
{
	switch (border_color)
	{
	case render::BorderColor::TransparentBlack:	return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
	case render::BorderColor::OpaqueBlack:		return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
	case render::BorderColor::OpaqueWhite:		return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	}
	return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_BORDER_COLOR_HPP
