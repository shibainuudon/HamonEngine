/**
 *	@file	dxgi_factory.hpp
 *
 *	@brief	DXGIFactory
 */

#ifndef HAMON_RENDER_D3D_DXGI_FACTORY_HPP
#define HAMON_RENDER_D3D_DXGI_FACTORY_HPP

#include <hamon/render/d3d/dxgi.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

class DXGIFactory
{
public:
	DXGIFactory(void)
	{
		::UINT flags = 0;
#if defined(_DEBUG)
		flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		ThrowIfFailed(::CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_factory)));
	}

	std::vector<ComPtr<::IDXGIAdapter4>>
	EnumAdapters(void)
	{
		std::vector<ComPtr<::IDXGIAdapter4>> result;

		ComPtr<::IDXGIAdapter1> adapter1;
		for (::UINT i = 0; m_factory->EnumAdapters1(i, &adapter1) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			::DXGI_ADAPTER_DESC1 desc1;
			ThrowIfFailed(adapter1->GetDesc1(&desc1));

			if (desc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// ソフトウェアアダプターはスキップ
				continue;
			}

			ComPtr<::IDXGIAdapter4> adapter4;
			ThrowIfFailed(adapter1.As(&adapter4));
			result.push_back(adapter4);
		}

		return result;
	}

	ComPtr<::IDXGISwapChain4>
	CreateSwapChainForHwnd(
		::IUnknown*	device,
		::HWND hwnd,
		::DXGI_SWAP_CHAIN_DESC1 const* desc,
		::DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* fullscreen_desc,
		::IDXGIOutput6* restrict_to_output)
	{
		ComPtr<::IDXGISwapChain1> swap_chain1;
		ThrowIfFailed(m_factory->CreateSwapChainForHwnd(
			device,
			hwnd,
			desc,
			fullscreen_desc,
			restrict_to_output,
			&swap_chain1));
		
		ComPtr<::IDXGISwapChain4> swap_chain4;
		ThrowIfFailed(swap_chain1.As(&swap_chain4));
		return swap_chain4;
	}

	void MakeWindowAssociation(::HWND hwnd, ::UINT flags)
	{
		ThrowIfFailed(m_factory->MakeWindowAssociation(hwnd, flags));
	}

private:
	ComPtr<::IDXGIFactory7>	m_factory;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D_DXGI_FACTORY_HPP
