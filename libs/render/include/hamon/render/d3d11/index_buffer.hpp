/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_D3D11_INDEX_BUFFER_HPP
#define HAMON_RENDER_D3D11_INDEX_BUFFER_HPP

#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/buffer.hpp>
#include <hamon/render/d3d11/index_type.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class IndexBuffer
{
public:
	IndexBuffer(Device* device, render::detail::IndexArrayBase const* index_array)
		: m_buffer(
			device,
			static_cast<::UINT>(index_array->GetBytes()),
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_INDEX_BUFFER,
			index_array->GetData())
		, m_count(static_cast<::UINT>(index_array->GetCount()))
		, m_format(d3d11::IndexType(index_array->GetType()))
	{
	}

	void Bind(DeviceContext* device_context)
	{
		device_context->IASetIndexBuffer(m_buffer.Get(), m_format, 0);
	}

	void Draw(DeviceContext* device_context)
	{
		device_context->DrawIndexed(m_count, 0, 0);
	}

private:
	d3d11::Buffer		m_buffer;
	::UINT				m_count = 0;
	::DXGI_FORMAT		m_format;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_INDEX_BUFFER_HPP
