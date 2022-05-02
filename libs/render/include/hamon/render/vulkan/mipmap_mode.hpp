/**
 *	@file	mipmap_mode.hpp
 *
 *	@brief	MipmapMode
 */

#ifndef HAMON_RENDER_VULKAN_MIPMAP_MODE_HPP
#define HAMON_RENDER_VULKAN_MIPMAP_MODE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/mipmap_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkSamplerMipmapMode
MipmapMode(render::MipmapMode mode)
{
	switch (mode)
	{
	case hamon::render::MipmapMode::Nearest:	return VK_SAMPLER_MIPMAP_MODE_NEAREST;
	case hamon::render::MipmapMode::Linear:		return VK_SAMPLER_MIPMAP_MODE_LINEAR;
	}
	return VK_SAMPLER_MIPMAP_MODE_NEAREST;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_MIPMAP_MODE_HPP
