/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology
 */

#ifndef HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_HPP
#define HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_PRIMITIVE_TOPOLOGY
PrimitiveTopology(render::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case render::PrimitiveTopology::PointList:		return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
	case render::PrimitiveTopology::LineList:		return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	case render::PrimitiveTopology::TriangleList:	return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PRIMITIVE_TOPOLOGY_HPP
