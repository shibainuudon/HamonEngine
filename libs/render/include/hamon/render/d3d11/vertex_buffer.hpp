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
#include <hamon/render/d3d11/primitive_topology.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class VertexBuffer
{
private:

public:
	VertexBuffer(Device* device, render::Geometry const& geometry)
		: m_topology(d3d11::PrimitiveTopology(geometry.GetPrimitiveTopology()))
		, m_stride(static_cast<::UINT>(geometry.GetLayout().GetBytes()))
		, m_count(static_cast<::UINT>(geometry.GetVertexArrayCount()))
	{
        ::D3D11_BUFFER_DESC desc{};
        desc.ByteWidth = static_cast<::UINT>(geometry.GetVertexArrayBytes());
        desc.Usage     = D3D11_USAGE_DEFAULT;
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
