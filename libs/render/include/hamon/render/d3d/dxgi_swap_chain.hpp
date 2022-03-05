/**
 *	@file	dxgi_swap_chain.hpp
 *
 *	@brief	DXGIFactory
 */

#ifndef HAMON_RENDER_D3D_DXGI_SWAP_CHAIN_HPP
#define HAMON_RENDER_D3D_DXGI_SWAP_CHAIN_HPP

#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi.hpp>
#include <hamon/render/d3d/com_ptr.hpp>

namespace hamon
{

inline namespace render
{

class DXGISwapChain
{
public:
	DXGISwapChain(
		DXGIFactory* factory,
		::IUnknown* device,
		::UINT buffer_count,
		::UINT width,
		::UINT height,
		::HWND hwnd)
	{
		::DXGI_SWAP_CHAIN_DESC1 desc {};
		desc.BufferCount      = buffer_count;
		desc.Width            = width;
		desc.Height           = height;
		desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.SampleDesc.Count = 1;

		auto swap_chain = factory->CreateSwapChainForHwnd(
			device,
			hwnd,
			&desc,
			nullptr,
			nullptr);

		swap_chain.As(&m_swap_chain);
	}

	void Present(::UINT sync_interval, ::UINT flags)
	{
		m_swap_chain->Present(sync_interval, flags);
	}

	void GetBuffer(::UINT buffer, REFIID riid, void** surface) const
	{
		m_swap_chain->GetBuffer(buffer, riid, surface);
	}

private:
	ComPtr<IDXGISwapChain4>	m_swap_chain;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D_DXGI_SWAP_CHAIN_HPP
