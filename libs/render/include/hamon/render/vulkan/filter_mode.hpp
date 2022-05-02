/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode
 */

#ifndef HAMON_RENDER_VULKAN_filter_mode_HPP
#define HAMON_RENDER_VULKAN_filter_mode_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/filter_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkFilter
FilterMode(render::FilterMode mode)
{
	switch (mode)
	{
	case render::FilterMode::Nearest:	return VK_FILTER_NEAREST;
	case render::FilterMode::Linear:	return VK_FILTER_LINEAR;
	}
	return VK_FILTER_NEAREST;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_filter_mode_HPP
