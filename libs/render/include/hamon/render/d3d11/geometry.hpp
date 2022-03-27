/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry
 */

#ifndef HAMON_RENDER_D3D11_GEOMETRY_HPP
#define HAMON_RENDER_D3D11_GEOMETRY_HPP

#include <hamon/render/geometry.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/vertex_buffer.hpp>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Geometry
{
public:
	Geometry(Device* device, render::Geometry const& geometry)
	{
		m_vertex_buffer = std::make_unique<VertexBuffer>(device, geometry);
	}

	void Draw(DeviceContext* device_context)
	{
		m_vertex_buffer->Draw(device_context);
	}

private:
	std::unique_ptr<VertexBuffer>	m_vertex_buffer;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_GEOMETRY_HPP
