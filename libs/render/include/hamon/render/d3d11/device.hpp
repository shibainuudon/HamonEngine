/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_D3D11_DEVICE_HPP
#define HAMON_RENDER_D3D11_DEVICE_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
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

		::HRESULT hr = S_OK;
		for (auto const& adapter : adapters)
		{
			ComPtr<::ID3D11Device> device;
			hr = ::D3D11CreateDevice(
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
				ThrowIfFailed(device.As(&m_device));
				break;
			}
		}

		ThrowIfFailed(hr);
	}

	ComPtr<ID3D11DeviceContext4>
	GetImmediateContext(void)
	{
		ComPtr<::ID3D11DeviceContext> device_context;
		m_device->GetImmediateContext(&device_context);

		ComPtr<ID3D11DeviceContext4> device_context4;
		ThrowIfFailed(device_context.As(&device_context4));

		return device_context4;
	}

	ComPtr<::ID3D11RenderTargetView1> CreateRenderTargetView(
		::ID3D11Resource* resource,
		::D3D11_RENDER_TARGET_VIEW_DESC1 const* desc)
	{
		ComPtr<::ID3D11RenderTargetView1> rtv1;
		ThrowIfFailed(m_device->CreateRenderTargetView1(resource, desc, &rtv1));
		return rtv1;
	}

	ComPtr<::ID3D11Buffer> CreateBuffer(
		const D3D11_BUFFER_DESC* desc,
		const D3D11_SUBRESOURCE_DATA* initial_data)
	{
		ComPtr<::ID3D11Buffer> buffer;
		ThrowIfFailed(m_device->CreateBuffer(desc, initial_data, &buffer));
		return buffer;
	}

	ComPtr<::ID3D11RasterizerState> CreateRasterizerState(
		const ::D3D11_RASTERIZER_DESC* rasterizer_desc)
	{
		ComPtr<::ID3D11RasterizerState> state;
		ThrowIfFailed(m_device->CreateRasterizerState(rasterizer_desc, &state));
		return state;
	}

	ComPtr<::ID3D11InputLayout> CreateInputLayout(
		const ::D3D11_INPUT_ELEMENT_DESC* input_element_descs,
		::UINT num_elements,
		::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11InputLayout> layout;
		ThrowIfFailed(m_device->CreateInputLayout(
			input_element_descs,
			num_elements,
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			&layout));
		return layout;
	}

	ComPtr<::ID3D11VertexShader> CreateVertexShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11VertexShader> shader;
		ThrowIfFailed(m_device->CreateVertexShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	ComPtr<::ID3D11GeometryShader> CreateGeometryShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11GeometryShader> shader;
		ThrowIfFailed(m_device->CreateGeometryShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	ComPtr<::ID3D11PixelShader> CreatePixelShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11PixelShader> shader;
		ThrowIfFailed(m_device->CreatePixelShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	ComPtr<::ID3D11HullShader> CreateHullShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11HullShader> shader;
		ThrowIfFailed(m_device->CreateHullShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	ComPtr<::ID3D11DomainShader> CreateDomainShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11DomainShader> shader;
		ThrowIfFailed(m_device->CreateDomainShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	ComPtr<::ID3D11ComputeShader> CreateComputeShader(::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11ComputeShader> shader;
		ThrowIfFailed(m_device->CreateComputeShader(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			nullptr,
			&shader));
		return shader;
	}

	::ID3D11Device5* Get(void) const { return m_device.Get(); }

private:
	ComPtr<::ID3D11Device5>	m_device;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_DEVICE_HPP
