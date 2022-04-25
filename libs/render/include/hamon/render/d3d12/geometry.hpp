/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_D3D12_GEOMETRY_HPP
#define HAMON_RENDER_D3D12_GEOMETRY_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/vertex_buffer.hpp>
#include <hamon/render/d3d12/index_buffer.hpp>
#include <hamon/render/d3d12/primitive_topology.hpp>
#include <hamon/render/d3d12/primitive_topology_type.hpp>
#include <hamon/render/d3d12/input_layout.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/geometry.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Geometry
{
public:
	explicit Geometry(d3d12::Device* device, render::Geometry const& geometry)
		: m_primitive_topology(d3d12::PrimitiveTopology(geometry.GetPrimitiveTopology()))
		, m_primitive_topology_type(d3d12::PrimitiveTopologyType(geometry.GetPrimitiveTopology()))
		, m_vertex_buffer(new VertexBuffer(device, geometry))
		, m_input_layout(geometry.GetLayout())
	{
		if (geometry.GetIndexArray() != nullptr)
		{
			m_index_buffer = std::make_unique<IndexBuffer>(device, geometry.GetIndexArray());
		}
	}

	void Draw(d3d12::CommandList* command_list)
	{
		command_list->IASetPrimitiveTopology(m_primitive_topology);
		m_vertex_buffer->Bind(command_list);

		if (m_index_buffer)
		{
			m_index_buffer->Bind(command_list);
			m_index_buffer->Draw(command_list);
		}
		else
		{
			m_vertex_buffer->Draw(command_list);
		}
	}

	auto const& GetPrimitiveTopology(void) const
	{
		return m_primitive_topology;
	}

	auto const& GetPrimitiveTopologyType(void) const
	{
		return m_primitive_topology_type;
	}

	auto const& GetInputLayout(void) const
	{
		return m_input_layout;
	}

private:
	::D3D12_PRIMITIVE_TOPOLOGY				m_primitive_topology;
	::D3D12_PRIMITIVE_TOPOLOGY_TYPE			m_primitive_topology_type;
	d3d12::InputLayout						m_input_layout;
	std::unique_ptr<d3d12::VertexBuffer>	m_vertex_buffer;
	std::unique_ptr<d3d12::IndexBuffer>		m_index_buffer;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_GEOMETRY_HPP
