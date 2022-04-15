/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_GEOMETRY_HPP
#define HAMON_RENDER_GEOMETRY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/vertex_layout.hpp>
#include <hamon/render/detail/identifiable.hpp>
#include <vector>
#include <utility>
#include <cstdint>

namespace hamon
{

inline namespace render
{

class Geometry : public detail::Identifiable
{
public:
	Geometry(
		PrimitiveTopology topology,
		VertexLayout layout,
		std::vector<float> vertices)
		: m_topology(topology)
		, m_layout(std::move(layout))
		, m_vertices(std::move(vertices))
		, m_indices()
	{
	}

	Geometry(
		PrimitiveTopology topology,
		VertexLayout layout,
		std::vector<float> vertices,
		std::vector<std::uint16_t> indices)
		: m_topology(topology)
		, m_layout(std::move(layout))
		, m_vertices(std::move(vertices))
		, m_indices(std::move(indices))
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
		return m_vertices.empty() ? 0 : sizeof(float) * m_vertices.size();
	}

	void const* GetVertexArrayData(void) const
	{
		return m_vertices.empty() ? nullptr : m_vertices.data();
	}

	std::size_t GetIndexArrayCount(void) const
	{
		return m_indices.empty() ? 0 : m_indices.size();
	}

	std::size_t GetIndexArrayBytes(void) const
	{
		return m_indices.empty() ? 0 : sizeof(std::uint16_t) * m_indices.size();
	}

	void const* GetIndexArrayData(void) const
	{
		return m_indices.empty() ? nullptr : m_indices.data();
	}

private:
	PrimitiveTopology			m_topology;
	VertexLayout				m_layout;
	std::vector<float>			m_vertices;
	std::vector<std::uint16_t>	m_indices;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GEOMETRY_HPP
