/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_GEOMETRY_HPP
#define HAMON_RENDER_GEOMETRY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/vertex_layout.hpp>
#include <vector>
#include <utility>

namespace hamon
{

inline namespace render
{

class Geometry
{
public:
	Geometry(PrimitiveTopology topology,
		VertexLayout layout,
		std::vector<float> vertices)
		: m_topology(topology)
		, m_layout(std::move(layout))
		, m_vertices(std::move(vertices))
	{
	}

	PrimitiveTopology	GetPrimitiveTopology(void) const
	{
		return m_topology;
	}

	VertexLayout const& GetLayout(void) const
	{
		return m_layout;
	}

	std::size_t GetVertexArrayCount(void) const
	{
		return GetVertexArrayBytes() / m_layout.GetBytes();
	}

	std::size_t GetVertexArrayBytes(void) const
	{
		return sizeof(float) * m_vertices.size();
	}

	void const* GetVertexArrayData(void) const
	{
		return m_vertices.data();
	}

private:
	PrimitiveTopology	m_topology;
	VertexLayout		m_layout;
	std::vector<float>	m_vertices;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GEOMETRY_HPP
