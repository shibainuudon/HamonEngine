/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_VULKAN_GEOMETRY_HPP
#define HAMON_RENDER_VULKAN_GEOMETRY_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/vertex_buffer.hpp>
#include <hamon/render/vulkan/index_buffer.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/geometry.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Geometry
{
public:
	explicit Geometry(vulkan::Device* device, render::Geometry const& geometry)
	{
		m_vertex_buffer = std::make_unique<vulkan::VertexBuffer>(device, geometry);
		if (geometry.GetIndexArrayData() != nullptr)
		{
			m_index_buffer = std::make_unique<vulkan::IndexBuffer>(device, geometry);
		}
	}

	~Geometry()
	{
	}

	void Draw(vulkan::CommandBuffer* command_buffer)
	{
		m_vertex_buffer->Bind(command_buffer);
		if (m_index_buffer)
		{
			m_index_buffer->Bind(command_buffer);
			m_index_buffer->Draw(command_buffer);
		}
		else
		{
			m_vertex_buffer->Draw(command_buffer);
		}
	}

private:
	std::unique_ptr<vulkan::VertexBuffer>	m_vertex_buffer;
	std::unique_ptr<vulkan::IndexBuffer>	m_index_buffer;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_GEOMETRY_HPP
