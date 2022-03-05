/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_D3D11_DEVICE_HPP
#define HAMON_RENDER_D3D11_DEVICE_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Device
{
public:
	explicit Device(std::vector<ComPtr<IDXGIAdapter4>> const& adapters)
	{
		::UINT flags = 0;
#if defined(_DEBUG)
		flags |= ::D3D11_CREATE_DEVICE_DEBUG;
#endif

		::D3D_FEATURE_LEVEL const feature_levels[] =
		{
			::D3D_FEATURE_LEVEL_11_1,
			::D3D_FEATURE_LEVEL_11_0,
			::D3D_FEATURE_LEVEL_10_1,
			::D3D_FEATURE_LEVEL_10_0,
		};

		for (auto const& adapter : adapters)
		{
			ComPtr<::ID3D11Device> device;
			auto const hr = ::D3D11CreateDevice(
				adapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				flags,
				feature_levels,
				ARRAYSIZE(feature_levels),
				D3D11_SDK_VERSION,
				&device,
				nullptr,
				nullptr);

			if (SUCCEEDED(hr))
			{
				device.As(&m_device);
				break;
			}
		}
	}

	ComPtr<ID3D11DeviceContext4>
	GetImmediateContext(void)
	{
		ComPtr<::ID3D11DeviceContext> device_context;
		m_device->GetImmediateContext(&device_context);

		ComPtr<ID3D11DeviceContext4> device_context4;
		device_context.As(&device_context4);

		return device_context4;
	}

	ComPtr<::ID3D11RenderTargetView1>
	CreateRenderTargetView(::ID3D11Resource* resource, ::D3D11_RENDER_TARGET_VIEW_DESC1 const* desc)
	{
		ComPtr<::ID3D11RenderTargetView1> rtv1;
		m_device->CreateRenderTargetView1(resource, desc, &rtv1);
		return rtv1;
	}

	::ID3D11Device5* Get(void) const { return m_device.Get(); }

private:
	ComPtr<::ID3D11Device5>	m_device;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_DEVICE_HPP
