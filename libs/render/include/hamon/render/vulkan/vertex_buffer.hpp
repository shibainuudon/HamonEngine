/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP
#define HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/resource.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/geometry.hpp>

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
		: m_resource(
			device,
			geometry.GetVertexArrayBytes(),
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		, m_count(static_cast<std::uint32_t>(geometry.GetVertexArrayCount()))
	{
		auto const size = geometry.GetVertexArrayBytes();
		auto const src  = geometry.GetVertexArrayData();

		void* dst = m_resource.Map(0, size, 0);
		std::memcpy(dst, src, size);
		m_resource.Unmap();
	}

	void Bind(vulkan::CommandBuffer* command_buffer)
	{
		::VkDeviceSize offset = 0;
		command_buffer->BindVertexBuffers(0, 1, &m_resource.GetBuffer(), &offset);
	}

	void Draw(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->Draw(m_count, 1, 0, 0);
	}

private:
	vulkan::Resource	m_resource;
	std::uint32_t		m_count;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_VERTEX_BUFFER_HPP
