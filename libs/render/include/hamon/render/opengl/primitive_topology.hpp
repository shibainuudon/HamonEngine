/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology
 */

#ifndef HAMON_RENDER_OPENGL_PRIMITIVE_TOPOLOGY_HPP
#define HAMON_RENDER_OPENGL_PRIMITIVE_TOPOLOGY_HPP

#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/opengl/gl.hpp>

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
	case render::PrimitiveTopology::Points:		return GL_POINTS;
	case render::PrimitiveTopology::Lines:		return GL_LINES;
	case render::PrimitiveTopology::Triangles:	return GL_TRIANGLES;
	default:									return GL_POINTS;
	}
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_PRIMITIVE_TOPOLOGY_HPP
