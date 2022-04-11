/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode
 */

#ifndef HAMON_RENDER_VULKAN_FILL_MODE_HPP
#define HAMON_RENDER_VULKAN_FILL_MODE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/fill_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPolygonMode
FillMode(render::FillMode mode)
{
	switch (mode)
	{
	case render::FillMode::Solid:		return VK_POLYGON_MODE_FILL;
	case render::FillMode::Wireframe:	return VK_POLYGON_MODE_LINE;
	}
	return VK_POLYGON_MODE_FILL;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_FILL_MODE_HPP
