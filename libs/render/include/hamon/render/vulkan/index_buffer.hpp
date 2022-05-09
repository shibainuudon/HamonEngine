/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP
#define HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/resource.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/vulkan/index_type.hpp>
#include <hamon/render/geometry.hpp>
#include <cstdint>

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
		: m_resource(
			device,
			index_array->GetBytes(),
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		, m_count(static_cast<std::uint32_t>(index_array->GetCount()))
		, m_type(vulkan::IndexType(index_array->GetType()))
	{
		auto const size = index_array->GetBytes();
		auto const src  = index_array->GetData();

		void* dst = m_resource.Map(0, size, 0);
		std::memcpy(dst, src, size);
		m_resource.Unmap();
	}

	void Bind(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->BindIndexBuffer(m_resource.GetBuffer(), 0, m_type);
	}

	void Draw(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->DrawIndexed(m_count, 1, 0, 0, 0);
	}

private:
	vulkan::Resource	m_resource;
	std::uint32_t		m_count;
	::VkIndexType		m_type;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_INDEX_BUFFER_HPP
