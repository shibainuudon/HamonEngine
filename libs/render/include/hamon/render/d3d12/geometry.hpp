/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_D3D12_GEOMETRY_HPP
#define HAMON_RENDER_D3D12_GEOMETRY_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/vertex_buffer.hpp>
#include <hamon/render/d3d12/primitive_topology.hpp>
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
	explicit Geometry(Device* device, render::Geometry const& geometry)
		: m_primitive_topology(d3d12::PrimitiveTopology(geometry.GetPrimitiveTopology()))
		, m_vertex_buffer(new VertexBuffer(device, geometry))
	{
	}

	void Draw(CommandList* command_list)
	{
		command_list->IASetPrimitiveTopology(m_primitive_topology);
		m_vertex_buffer->Draw(command_list);
	}

private:
	::D3D12_PRIMITIVE_TOPOLOGY		m_primitive_topology;
	std::unique_ptr<VertexBuffer>	m_vertex_buffer;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_GEOMETRY_HPP
