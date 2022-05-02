/**
 *	@file	sampler_address_mode.hpp
 *
 *	@brief	SamplerAddressMode
 */

#ifndef HAMON_RENDER_VULKAN_SAMPLER_ADDRESS_MODE_HPP
#define HAMON_RENDER_VULKAN_SAMPLER_ADDRESS_MODE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/sampler_address_mode.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkSamplerAddressMode
SamplerAddressMode(render::SamplerAddressMode mode)
{
    switch (mode)
    {
    case render::SamplerAddressMode::Repeat:                return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case render::SamplerAddressMode::MirroredRepeat:        return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    case render::SamplerAddressMode::ClampToEdge:           return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case render::SamplerAddressMode::ClampToBorder:         return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    case render::SamplerAddressMode::MirrorClampToEdge:     return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
    }
    return VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SAMPLER_ADDRESS_MODE_HPP
