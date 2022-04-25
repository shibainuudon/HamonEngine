/**
 *	@file	root_signature.hpp
 *
 *	@brief	RootSignature
 */

#ifndef HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP
#define HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <vector>
#include <iostream>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class RootSignature
{
public:
	explicit RootSignature(
		d3d12::Device* device,
		std::vector<::D3D12_ROOT_PARAMETER1> const& root_parameters)
	{
		::D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc;
		desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
		desc.Desc_1_1.NumParameters     = static_cast<::UINT>(root_parameters.size());
		desc.Desc_1_1.pParameters       = root_parameters.data();
		desc.Desc_1_1.NumStaticSamplers = 0;
		desc.Desc_1_1.pStaticSamplers   = nullptr;
		desc.Desc_1_1.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ComPtr<::ID3DBlob> signature;
		ComPtr<::ID3DBlob> error;
		auto const hr = ::D3D12SerializeVersionedRootSignature(
			&desc, &signature, &error);

		if (error)
		{
			std::cout << static_cast<const char*>(error->GetBufferPointer()) << std::endl;
		}

		ThrowIfFailed(hr);

		m_root_signature = device->CreateRootSignature(
			0,
			signature->GetBufferPointer(),
			signature->GetBufferSize());
	}

	::ID3D12RootSignature* Get(void) const
	{
		return m_root_signature.Get();
	}

private:
	ComPtr<::ID3D12RootSignature>	m_root_signature;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP
