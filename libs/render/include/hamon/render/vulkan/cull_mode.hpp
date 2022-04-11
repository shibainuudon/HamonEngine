/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode
 */

#ifndef HAMON_RENDER_VULKAN_CULL_MODE_HPP
#define HAMON_RENDER_VULKAN_CULL_MODE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/cull_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkCullModeFlags
CullMode(render::CullMode mode)
{
	switch (mode)
	{
	case render::CullMode::None:	return VK_CULL_MODE_NONE;
	case render::CullMode::Front:	return VK_CULL_MODE_FRONT_BIT;
	case render::CullMode::Back:	return VK_CULL_MODE_BACK_BIT;
	}
	return VK_CULL_MODE_NONE;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_CULL_MODE_HPP
