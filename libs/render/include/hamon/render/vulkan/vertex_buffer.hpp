/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP
#define HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/buffer.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/geometry.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class VertexBuffer
{
public:
	explicit VertexBuffer(vulkan::Device* device, render::Geometry const& geometry)
		: m_count(static_cast<std::uint32_t>(geometry.GetVertexArrayCount()))
	{
		auto const size = geometry.GetVertexArrayBytes();
		auto const src  = geometry.GetVertexArrayData();

		m_buffer = std::make_unique<vulkan::Buffer>(
			device,
			size,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

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
		m_buffer->BindAsVertexBuffers(command_buffer);
	}

	void Draw(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->Draw(m_count, 1, 0, 0);
	}

private:
	std::unique_ptr<vulkan::Buffer>			m_buffer;
	std::unique_ptr<vulkan::DeviceMemory>	m_device_memory;
	std::uint32_t							m_count;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP
