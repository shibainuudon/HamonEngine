/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP
#define HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP

#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/buffer.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class VertexBuffer
{
public:
	VertexBuffer(Device* device, render::Geometry const& geometry)
		: m_buffer(
			device,
			static_cast<::UINT>(geometry.GetVertexArrayBytes()),
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_VERTEX_BUFFER,
			geometry.GetVertexArrayData())
		, m_stride(static_cast<::UINT>(geometry.GetLayout().GetBytes()))
		, m_count(static_cast<::UINT>(geometry.GetVertexArrayCount()))
	{
	}

	void Bind(DeviceContext* device_context)
	{
		::ID3D11Buffer* buffers[]
		{
			m_buffer.Get()
		};
		device_context->IASetVertexBuffers(0, 1, buffers, &m_stride, &m_offset);
	}

	void Draw(DeviceContext* device_context)
	{
		device_context->Draw(m_count, 0);
	}

private:
	d3d11::Buffer		m_buffer;
	::UINT				m_stride = 0;
	::UINT				m_offset = 0;
	::UINT				m_count = 0;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_VERTEX_BUFFER_HPP
