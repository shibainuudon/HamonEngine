/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP
#define HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP

#include <hamon/render/geometry.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class VertexBuffer
{
private:
	static ::D3D11_PRIMITIVE_TOPOLOGY
	ToD3D11Topology(render::PrimitiveTopology topology)
	{
		switch (topology)
		{
		case render::PrimitiveTopology::Points:    return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		case render::PrimitiveTopology::Lines:     return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		case render::PrimitiveTopology::Triangles: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		default:                                   return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		}
	}

public:
	VertexBuffer(Device* device, render::Geometry const& geometry)
		: m_topology(ToD3D11Topology(geometry.GetPrimitiveTopology()))
		, m_stride(geometry.GetLayout().GetBytes())
		, m_count(3)//geometry.GetVertexArrayCount())
	{
        ::D3D11_BUFFER_DESC desc{};
        desc.ByteWidth = geometry.GetVertexArrayBytes();
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		::D3D11_SUBRESOURCE_DATA subresource_data{};
		subresource_data.pSysMem = geometry.GetVertexArrayData();

		m_buffer = device->CreateBuffer(&desc, &subresource_data);
	}

	void Draw(DeviceContext* device_context)
	{
		device_context->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset);
		device_context->IASetPrimitiveTopology(m_topology);
		device_context->Draw(m_count, 0);
	}

private:
	ComPtr<::ID3D11Buffer>	m_buffer;
	::D3D11_PRIMITIVE_TOPOLOGY	m_topology;
	::UINT m_stride = 0;
	::UINT m_offset = 0;
	::UINT m_count = 0;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP
