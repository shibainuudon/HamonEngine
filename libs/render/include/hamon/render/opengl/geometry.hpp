/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_OPENGL_GEOMETRY_HPP
#define HAMON_RENDER_OPENGL_GEOMETRY_HPP

#include <hamon/render/geometry.hpp>
#include <hamon/render/opengl/vertex_buffer.hpp>
#include <hamon/render/opengl/index_buffer.hpp>
#include <hamon/render/opengl/vertex_array.hpp>
#include <hamon/render/opengl/primitive_topology.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Geometry
{
public:
	explicit Geometry(render::Geometry const& geometry)
		: m_topology(gl::PrimitiveTopology(geometry.GetPrimitiveTopology()))
	{
		m_vertex_buffer = std::make_unique<VertexBuffer>(geometry);

		if (geometry.GetIndexArrayData() != nullptr)
		{
			m_index_buffer = std::make_unique<IndexBuffer>(geometry);
		}

		m_vertex_array = std::make_unique<VertexArray>(
			geometry.GetLayout(),
			m_vertex_buffer.get(),
			m_index_buffer.get());
	}

	void Draw()
	{
		m_vertex_array->Bind();

		if (m_index_buffer)
		{
			m_index_buffer->Draw(m_topology);
		}
		else
		{
			m_vertex_buffer->Draw(m_topology);
		}

		m_vertex_array->Unbind();
	}

private:
	std::unique_ptr<gl::VertexBuffer>	m_vertex_buffer;
	std::unique_ptr<gl::IndexBuffer>	m_index_buffer;
	std::unique_ptr<gl::VertexArray>	m_vertex_array;
	::GLenum							m_topology;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_GEOMETRY_HPP
