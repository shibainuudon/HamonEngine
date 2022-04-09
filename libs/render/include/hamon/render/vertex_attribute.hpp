/**
 *	@file	vertex_attribute.hpp
 *
 *	@brief	VertexAttribute
 */

#ifndef HAMON_RENDER_VERTEX_ATTRIBUTE_HPP
#define HAMON_RENDER_VERTEX_ATTRIBUTE_HPP

#include <hamon/render/semantic.hpp>
#include <hamon/render/type.hpp>
#include <cstddef>

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

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VERTEX_ATTRIBUTE_HPP
