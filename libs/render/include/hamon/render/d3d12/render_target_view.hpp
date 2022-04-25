/**
 *	@file	render_target_view.hpp
 *
 *	@brief	RenderTargetView
 */

#ifndef HAMON_RENDER_D3D12_RENDER_TARGET_VIEW_HPP
#define HAMON_RENDER_D3D12_RENDER_TARGET_VIEW_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class RenderTargetView
{
public:
	explicit RenderTargetView(d3d12::Device* device, render::DXGISwapChain* swap_chain)
	{
		auto const buffer_count = swap_chain->GetBufferCount();

		::D3D12_DESCRIPTOR_HEAP_DESC desc {};
		desc.NumDescriptors = buffer_count;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_descriptor_heap = device->CreateDescriptorHeap(desc);
		m_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		for (::UINT i = 0; i < buffer_count; ++i)
		{
			ComPtr<::ID3D12Resource1> resource;
			swap_chain->GetBuffer(i, IID_PPV_ARGS(&resource));
			device->CreateRenderTargetView(resource.Get(), nullptr, GetHandle(i));
		}
	}

	::D3D12_CPU_DESCRIPTOR_HANDLE
	GetHandle(::UINT index) const
	{
		::D3D12_CPU_DESCRIPTOR_HANDLE handle(m_descriptor_heap->GetCPUDescriptorHandleForHeapStart());
		handle.ptr += m_descriptor_size * index;
		return handle;
	}

private:
	ComPtr<::ID3D12DescriptorHeap>	m_descriptor_heap;
	::UINT							m_descriptor_size;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_RENDER_TARGET_VIEW_HPP
