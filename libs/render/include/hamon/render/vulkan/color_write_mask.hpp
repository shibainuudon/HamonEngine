/**
 *	@file	color_write_mask.hpp
 *
 *	@brief	ColorWriteMask
 */

#ifndef HAMON_RENDER_VULKAN_COLOR_WRITE_MASK_HPP
#define HAMON_RENDER_VULKAN_COLOR_WRITE_MASK_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/color_write_mask.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkColorComponentFlags
ColorWriteMask(std::uint32_t mask)
{
	::VkColorComponentFlags result{};

	if (mask & render::ColorWriteMask::Red)
	{
		result |= VK_COLOR_COMPONENT_R_BIT;
	}
	if (mask & render::ColorWriteMask::Green)
	{
		result |= VK_COLOR_COMPONENT_G_BIT;
	}
	if (mask & render::ColorWriteMask::Blue)
	{
		result |= VK_COLOR_COMPONENT_B_BIT;
	}
	if (mask & render::ColorWriteMask::Alpha)
	{
		result |= VK_COLOR_COMPONENT_A_BIT;
	}

	return result;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_COLOR_WRITE_MASK_HPP
