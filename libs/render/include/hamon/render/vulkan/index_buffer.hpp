/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP
#define HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/buffer.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/vulkan/index_type.hpp>
#include <hamon/render/geometry.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class IndexBuffer
{
public:
	explicit IndexBuffer(vulkan::Device* device, render::detail::IndexArrayBase const* index_array)
		: m_count(static_cast<std::uint32_t>(index_array->GetCount()))
		, m_type(vulkan::IndexType(index_array->GetType()))
	{
		auto const size = index_array->GetBytes();
		auto const src  = index_array->GetData();

		m_buffer = std::make_unique<vulkan::Buffer>(
			device,
			size,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT);

		m_device_memory = std::make_unique<vulkan::DeviceMemory>(
			device,
			m_buffer->GetMemoryRequirements(),
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		{
			void* dst = m_device_memory->Map(0, size, 0);
			std::memcpy(dst, src, size);
			m_device_memory->Unmap();
		}

		m_buffer->BindMemory(m_device_memory.get(), 0);
	}

	void Bind(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->BindIndexBuffer(m_buffer->Get(), 0, m_type);
	}

	void Draw(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->DrawIndexed(m_count, 1, 0, 0, 0);
	}

private:
	std::unique_ptr<vulkan::Buffer>			m_buffer;
	std::unique_ptr<vulkan::DeviceMemory>	m_device_memory;
	std::uint32_t							m_count;
	::VkIndexType							m_type;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP
