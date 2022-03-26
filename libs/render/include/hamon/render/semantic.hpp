/**
 *	@file	semantic.hpp
 *
 *	@brief	Semantic
 */

#ifndef HAMON_RENDER_SEMANTIC_HPP
#define HAMON_RENDER_SEMANTIC_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class Semantic : std::uint32_t
{
	Position,
	Normal,
	Color,
	TexCoord,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SEMANTIC_HPP
