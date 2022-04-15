/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_D3D11_GEOMETRY_HPP
#define HAMON_RENDER_D3D11_GEOMETRY_HPP

#include <hamon/render/geometry.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/vertex_buffer.hpp>
#include <hamon/render/d3d11/index_buffer.hpp>
#include <hamon/render/d3d11/primitive_topology.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Geometry
{
public:
	Geometry(Device* device, render::Geometry const& geometry)
		: m_primitive_topology(d3d11::PrimitiveTopology(geometry.GetPrimitiveTopology()))
	{
		m_vertex_buffer = std::make_unique<VertexBuffer>(device, geometry);

		if (geometry.GetIndexArrayData() != nullptr)
		{
			m_index_buffer = std::make_unique<IndexBuffer>(device, geometry);
		}
	}

	void Draw(DeviceContext* device_context)
	{
		device_context->IASetPrimitiveTopology(m_primitive_topology);

		m_vertex_buffer->Bind(device_context);
		
		if (m_index_buffer)
		{
			m_index_buffer->Bind(device_context);
			m_index_buffer->Draw(device_context);
		}
		else
		{
			m_vertex_buffer->Draw(device_context);
		}
	}

private:
	std::unique_ptr<VertexBuffer>	m_vertex_buffer;
	std::unique_ptr<IndexBuffer>	m_index_buffer;
	::D3D11_PRIMITIVE_TOPOLOGY		m_primitive_topology;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_GEOMETRY_HPP
