/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology
 */

#ifndef HAMON_RENDER_GL_PRIMITIVE_TOPOLOGY_HPP
#define HAMON_RENDER_GL_PRIMITIVE_TOPOLOGY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum PrimitiveTopology(render::PrimitiveTopology topology)
{
	switch (topology)
	{
	case render::PrimitiveTopology::PointList:		return GL_POINTS;
	case render::PrimitiveTopology::LineList:		return GL_LINES;
	case render::PrimitiveTopology::TriangleList:	return GL_TRIANGLES;
	}
	return GL_POINTS;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_PRIMITIVE_TOPOLOGY_HPP
