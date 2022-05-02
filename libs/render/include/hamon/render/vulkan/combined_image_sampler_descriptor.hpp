/**
 *	@file	combined_image_sampler_descriptor.hpp
 *
 *	@brief	CombinedImageSamplerDescriptor
 */

#ifndef HAMON_RENDER_VULKAN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR_HPP
#define HAMON_RENDER_VULKAN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR_HPP

#include <hamon/render/vulkan/spirv_reflection.hpp>
#include <hamon/render/vulkan/resource_map.hpp>
#include <hamon/render/vulkan/sampler.hpp>
#include <hamon/render/vulkan/texture.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/uniforms.hpp>
#include <hamon/render/sampler.hpp>
#include <string>

namespace hamon
{

inline namespace render
{

namespace vulkan
{


class CombinedImageSamplerDescriptor
{
public:
	explicit CombinedImageSamplerDescriptor(SpirvReflection::Uniform const& reflection)
		: m_name(reflection.name)
		, m_set(reflection.set)
		, m_binding(reflection.binding)
	{
	}

	void LoadUniforms(
		vulkan::Device* device,
		vulkan::CommandPool* command_pool,
		vulkan::ResourceMap* resource_map,
		render::Uniforms const& uniforms)
	{
		auto uniform = uniforms[m_name];
		if (uniform == nullptr)
		{
			return;
		}

		using type = std::pair<render::Texture, render::Sampler>;
		auto data = static_cast<type const*>(uniform->GetData());
		auto texture = resource_map->GetTexture(device, command_pool, data->first);
		auto sampler = resource_map->GetSampler(device, data->second);

		m_image_info.sampler = sampler->Get();
		m_image_info.imageView = texture->GetView();
		m_image_info.imageLayout = texture->GetLayout();
	}

	::VkWriteDescriptorSet
	CreateWriteDescriptorSet(std::vector<::VkDescriptorSet> const& descriptor_sets) const
	{
		::VkWriteDescriptorSet write {};
		write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.pNext            = nullptr;
		write.dstSet           = descriptor_sets[m_set];
		write.dstBinding       = m_binding;
		write.dstArrayElement  = 0;
		write.descriptorCount  = 1;
		write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		write.pImageInfo       = &m_image_info;
		write.pBufferInfo      = nullptr;
		write.pTexelBufferView = nullptr;

		return write;
	}

private:
	std::string					m_name;
	std::uint32_t				m_set;
	std::uint32_t				m_binding;
	::VkDescriptorImageInfo		m_image_info;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR_HPP
