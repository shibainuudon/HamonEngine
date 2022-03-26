/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology
 */

#ifndef HAMON_RENDER_PRIMITIVE_TOPOLOGY_HPP
#define HAMON_RENDER_PRIMITIVE_TOPOLOGY_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class PrimitiveTopology : std::uint32_t
{
	Points,
	Lines,
	Triangles,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_PRIMITIVE_TOPOLOGY_HPP
