/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_OPENGL_GEOMETRY_HPP
#define HAMON_RENDER_OPENGL_GEOMETRY_HPP

#include <hamon/render/geometry.hpp>
#include <hamon/render/opengl/buffer.hpp>
#include <hamon/render/opengl/vertex_array.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum ToGlPrimitiveTopology(render::PrimitiveTopology topology)
{
	switch (topology)
	{
	case hamon::render::PrimitiveTopology::Points:		return GL_POINTS;
	case hamon::render::PrimitiveTopology::Lines:		return GL_LINES;
	case hamon::render::PrimitiveTopology::Triangles:	return GL_TRIANGLES;
	default:											return GL_POINTS;
	}
}

class Geometry
{
public:
	Geometry(render::Geometry const& geometry)
		: m_vertex_buffer(geometry.GetVertexArrayBytes(), geometry.GetVertexArrayData(), GL_STATIC_DRAW)
		, m_vertex_array(geometry.GetLayout(), m_vertex_buffer.GetId(), 0)
		, m_topology(ToGlPrimitiveTopology(geometry.GetPrimitiveTopology()))
		, m_vertex_count(static_cast<::GLsizei>(geometry.GetVertexArrayCount()))
	{
	}

	void Draw()
	{
		m_vertex_array.Bind();
		::glDrawArrays(m_topology, 0, m_vertex_count);
		m_vertex_array.Unbind();
	}

private:
	gl::Buffer		m_vertex_buffer;
	// gl::Buffer	m_index_buffer;
	gl::VertexArray	m_vertex_array;
	::GLenum		m_topology;
	::GLsizei		m_vertex_count;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_GEOMETRY_HPP
