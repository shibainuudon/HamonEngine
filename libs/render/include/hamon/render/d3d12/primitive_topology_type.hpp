/**
 *	@file	primitive_topology_type.hpp
 *
 *	@brief	PrimitiveTopologyType
 */

#ifndef HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP
#define HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_PRIMITIVE_TOPOLOGY_TYPE
PrimitiveTopologyType(render::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case render::PrimitiveTopology::Points:		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	case render::PrimitiveTopology::Lines:		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
	case render::PrimitiveTopology::Triangles:	return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}
	return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP
