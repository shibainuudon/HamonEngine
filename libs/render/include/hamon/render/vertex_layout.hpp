/**
 *	@file	vertex_layout.hpp
 *
 *	@brief	VertexLayout
 */

#ifndef HAMON_RENDER_VERTEX_LAYOUT_HPP
#define HAMON_RENDER_VERTEX_LAYOUT_HPP

#include <hamon/render/semantic.hpp>
#include <hamon/render/type.hpp>
#include <cstddef>
#include <vector>
#include <initializer_list>

namespace hamon
{

inline namespace render
{

struct VertexAttribute
{
	Semantic	semantic;
	Type		type;
	std::size_t	element_num;
	std::size_t offset;
};

class VertexLayout
{
public:
	VertexLayout(std::size_t bytes, std::vector<VertexAttribute> attributes)
		: m_bytes(bytes)
		, m_attributes(attributes)
	{
	}

	std::size_t	GetBytes(void) const { return m_bytes; }

	std::vector<VertexAttribute> const& GetAttributes(void) const
	{
		return m_attributes;
	}

private:
	std::size_t						m_bytes;
	std::vector<VertexAttribute>	m_attributes;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VERTEX_LAYOUT_HPP
