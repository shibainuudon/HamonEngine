/**
 *	@file	root_signature.hpp
 *
 *	@brief	RootSignature
 */

#ifndef HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP
#define HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d12/device.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class RootSignature
{
public:
	explicit RootSignature(Device* device)
	{
		::D3D12_ROOT_SIGNATURE_DESC desc;
		desc.NumParameters     = 0;
		desc.pParameters       = nullptr;
		desc.NumStaticSamplers = 0;
		desc.pStaticSamplers   = nullptr;
		desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ComPtr<::ID3DBlob> signature;
		ComPtr<::ID3DBlob> error;
		ThrowIfFailed(::D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		m_root_signature = device->CreateRootSignature(
			0,
			signature->GetBufferPointer(),
			signature->GetBufferSize());
	}

	::ID3D12RootSignature* Get(void) const { return m_root_signature.Get(); }

private:
	ComPtr<::ID3D12RootSignature>	m_root_signature;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_ROOT_SIGNATURE_HPP
