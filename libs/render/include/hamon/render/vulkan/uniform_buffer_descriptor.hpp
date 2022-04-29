/**
 *	@file	uniform_buffer_descriptor.hpp
 *
 *	@brief	UniformBufferDescriptor
 */

#ifndef HAMON_RENDER_VULKAN_UNIFORM_BUFFER_DESCRIPTOR_HPP
#define HAMON_RENDER_VULKAN_UNIFORM_BUFFER_DESCRIPTOR_HPP

#include <hamon/render/vulkan/spirv_reflection.hpp>
#include <hamon/render/vulkan/uniform_buffer.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class UniformBufferDescriptor
{
public:
	explicit UniformBufferDescriptor(SpirvReflection::Uniform const& reflection)
		: m_set(reflection.set)
		, m_binding(reflection.binding)
		, m_bytes(reflection.bytes)
	{
		for (auto const& member : reflection.members)
		{
			Variable variable;
			variable.name   = member.name;
			variable.bytes  = member.bytes;
			variable.offset = member.offset;
			m_variables.push_back(variable);
		}
	}

	void LoadUniforms(
		vulkan::UniformBuffer* uniform_buffer,
		render::Uniforms const& uniforms)
	{
		auto const mem = uniform_buffer->Allocate(m_bytes);

		for (auto const& variable : m_variables)
		{
			auto uniform = uniforms[variable.name];
			if (uniform != nullptr)
			{
				std::memcpy(
					&mem.mapped_buffer[variable.offset],
					uniform->GetData(),
					variable.bytes);
			}
		}

		m_buffer_info.buffer = uniform_buffer->GetBuffer();
		m_buffer_info.offset = mem.offset;
		m_buffer_info.range  = m_bytes;
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
		write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		write.pImageInfo       = nullptr;
		write.pBufferInfo      = &m_buffer_info;
		write.pTexelBufferView = nullptr;

		return write;
	}

private:
	struct Variable
	{
		std::string		name;
		std::uint32_t	offset;
		std::size_t		bytes;
	};

	std::uint32_t							m_set;
	std::uint32_t							m_binding;
	std::size_t								m_bytes;
	std::vector<Variable>					m_variables;
	::VkDescriptorBufferInfo				m_buffer_info;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_UNIFORM_BUFFER_DESCRIPTOR_HPP
