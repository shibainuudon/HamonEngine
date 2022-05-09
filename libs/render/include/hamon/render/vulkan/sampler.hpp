/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler
 */

#ifndef HAMON_RENDER_VULKAN_SAMPLER_HPP
#define HAMON_RENDER_VULKAN_SAMPLER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/filter_mode.hpp>
#include <hamon/render/vulkan/mipmap_mode.hpp>
#include <hamon/render/vulkan/sampler_address_mode.hpp>
#include <hamon/render/vulkan/compare_operation.hpp>
#include <hamon/render/vulkan/border_color.hpp>
#include <hamon/render/sampler.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Sampler
{
public:
	explicit Sampler(vulkan::Device* device, render::Sampler const& sampler)
		: m_device(device)
	{
		::VkSamplerCreateInfo info{};
		info.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		info.pNext                   = nullptr;
		info.flags                   = 0;
		info.magFilter               = vulkan::FilterMode(sampler.mag_filter);
		info.minFilter               = vulkan::FilterMode(sampler.min_filter);
		info.mipmapMode              = vulkan::MipmapMode(sampler.mip_filter);
		info.addressModeU            = vulkan::SamplerAddressMode(sampler.address_mode_u);
		info.addressModeV            = vulkan::SamplerAddressMode(sampler.address_mode_v);
		info.addressModeW            = vulkan::SamplerAddressMode(sampler.address_mode_w);
		info.mipLodBias              = sampler.mip_lod_bias;
		info.anisotropyEnable        = sampler.anisotropy_enable;
		info.maxAnisotropy           = sampler.max_anisotropy;
		info.compareEnable           = sampler.compare_enable;
		info.compareOp               = vulkan::CompareOperation(sampler.compare_operation);
		info.minLod                  = sampler.min_lod;
		info.maxLod                  = sampler.max_lod;
		info.borderColor             = vulkan::BorderColor(sampler.border_color);
		info.unnormalizedCoordinates = VK_FALSE;

		m_sampler = m_device->CreateSampler(info);
	}

	~Sampler()
	{
		m_device->DestroySampler(m_sampler);
	}

	::VkSampler Get(void) const
	{
		return m_sampler;
	}

private:
	::VkSampler		m_sampler;
	vulkan::Device*	m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SAMPLER_HPP
