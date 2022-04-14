/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology
 */

#ifndef HAMON_RENDER_VULKAN_PRIMITIVE_TOPOLOGY_HPP
#define HAMON_RENDER_VULKAN_PRIMITIVE_TOPOLOGY_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/primitive_topology.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkPrimitiveTopology
PrimitiveTopology(render::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case render::PrimitiveTopology::PointList:		return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	case render::PrimitiveTopology::LineList:		return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	case render::PrimitiveTopology::TriangleList:	return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	}
	return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PRIMITIVE_TOPOLOGY_HPP
