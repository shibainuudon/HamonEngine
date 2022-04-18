/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_GEOMETRY_HPP
#define HAMON_RENDER_GEOMETRY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/vertex_layout.hpp>
#include <hamon/render/index_type.hpp>
#include <hamon/render/detail/identifiable.hpp>
#include <hamon/render/detail/index_array.hpp>
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
		, m_index_array()
	{
	}

	template <typename IndexArrayRange>
	Geometry(
		PrimitiveTopology topology,
		VertexLayout layout,
		std::vector<float> vertices,
		IndexArrayRange const& index_array)
		: Geometry(
			topology,
			layout,
			std::move(vertices),
			std::begin(index_array),
			std::end(index_array))
	{
	}

	template <
		typename IndexArrayIterator,
		typename IndexType = std::iter_value_t<IndexArrayIterator>
	>
	Geometry(
		PrimitiveTopology topology,
		VertexLayout layout,
		std::vector<float> vertices,
		IndexArrayIterator index_first,
		IndexArrayIterator index_last)
		: m_topology(topology)
		, m_layout(std::move(layout))
		, m_vertices(std::move(vertices))
		, m_index_array(new detail::IndexArray<IndexType>(index_first, index_last))
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

	detail::IndexArrayBase* GetIndexArray(void) const
	{
		return m_index_array.get();
	}

private:
	PrimitiveTopology			m_topology;
	VertexLayout				m_layout;
	std::vector<float>			m_vertices;
	std::unique_ptr<detail::IndexArrayBase>	m_index_array;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GEOMETRY_HPP
