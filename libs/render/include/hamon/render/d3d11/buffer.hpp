/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer
 */

#ifndef HAMON_RENDER_D3D11_BUFFER_HPP
#define HAMON_RENDER_D3D11_BUFFER_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d11/device.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Buffer
{
private:

public:
	Buffer(
		Device* device,
		::UINT size,
		::D3D11_USAGE usage,
		::UINT bind_flags,
		void const* data)
	{
        ::D3D11_BUFFER_DESC desc{};
        desc.ByteWidth = size;
        desc.Usage     = usage;
        desc.BindFlags = bind_flags;

		if (data == nullptr)
		{
			m_buffer = device->CreateBuffer(&desc, nullptr);
		}
		else
		{
			::D3D11_SUBRESOURCE_DATA subresource_data{};
			subresource_data.pSysMem = data;

			m_buffer = device->CreateBuffer(&desc, &subresource_data);
		}
	}

	::ID3D11Buffer* Get(void) const { return m_buffer.Get(); }

private:
	ComPtr<::ID3D11Buffer>	m_buffer;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_BUFFER_HPP
