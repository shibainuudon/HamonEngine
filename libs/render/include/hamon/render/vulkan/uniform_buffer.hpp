/**
 *	@file	uniform_buffer.hpp
 *
 *	@brief	UniformBuffer
 */

#ifndef HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP
#define HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/spirv_reflection.hpp>
#include <hamon/render/vulkan/buffer.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class UniformBuffer
{
public:
	explicit UniformBuffer(vulkan::Device* device, SpirvReflection::Uniform const& reflection)
		: m_set(reflection.set)
		, m_binding(reflection.binding)
		, m_bytes(reflection.bytes)
	{
		m_buffer = std::make_unique<vulkan::Buffer>(
			device,
			m_bytes,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

		m_device_memory = std::make_unique<vulkan::DeviceMemory>(
			device,
			m_buffer->GetMemoryRequirements(),
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		m_buffer->BindMemory(m_device_memory.get(), 0);

		m_mapped_buffer = static_cast<std::uint8_t*>(m_device_memory->Map(0, m_bytes, 0));

		for (auto const& member : reflection.members)
		{
			Variable variable;
			variable.name   = member.name;
			variable.bytes  = member.bytes;
			variable.offset = member.offset;
			m_variables.push_back(variable);
		}

		m_buffer_info.buffer = m_buffer->Get();
		m_buffer_info.offset = 0;
		m_buffer_info.range  = m_bytes;
	}

	void LoadUniforms(
		render::Uniforms const& uniforms)
	{
		for (auto const& variable : m_variables)
		{
			auto uniform = uniforms[variable.name];
			if (uniform != nullptr)
			{
				std::memcpy(
					&m_mapped_buffer[variable.offset],
					uniform->GetData(),
					variable.bytes);
			}
		}
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
	std::unique_ptr<vulkan::Buffer>			m_buffer;
	std::unique_ptr<vulkan::DeviceMemory>	m_device_memory;
	std::uint8_t*							m_mapped_buffer;
	::VkDescriptorBufferInfo				m_buffer_info;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP
