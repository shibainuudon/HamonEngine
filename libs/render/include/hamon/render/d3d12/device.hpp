/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_D3D12_DEVICE_HPP
#define HAMON_RENDER_D3D12_DEVICE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Device
{
public:
	explicit Device(std::vector<ComPtr<IDXGIAdapter4>> const& adapters)
	{
		::D3D_FEATURE_LEVEL const feature_levels[] =
		{
			::D3D_FEATURE_LEVEL_12_1,
			::D3D_FEATURE_LEVEL_12_0,
			::D3D_FEATURE_LEVEL_11_1,
			::D3D_FEATURE_LEVEL_11_0,
		};

		for (auto const& adapter : adapters)
		{
			for (auto feature_level : feature_levels)
			{
				auto const hr = ::D3D12CreateDevice(
					adapter.Get(),
					feature_level,
					IID_PPV_ARGS(&m_device));

				if (SUCCEEDED(hr))
				{
					return;
				}
			}
		}
	}

	ComPtr<::ID3D12CommandQueue>
	CreateCommandQueue(::D3D12_COMMAND_QUEUE_DESC const& desc)
	{
		ComPtr<::ID3D12CommandQueue> command_queue;
		m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue));
		return command_queue;
	}

	ComPtr<::ID3D12CommandAllocator>
	CreateCommandAllocator(::D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<::ID3D12CommandAllocator> command_allocator;
		m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator));
		return command_allocator;
	}

	ComPtr<::ID3D12GraphicsCommandList6>
	CreateGraphicsCommandList(::D3D12_COMMAND_LIST_TYPE type, ::ID3D12CommandAllocator* command_allocator)
	{
		ComPtr<::ID3D12GraphicsCommandList6> command_list;
		m_device->CreateCommandList(
			0,	// nodeMask
			type,
			command_allocator,
			nullptr,
			IID_PPV_ARGS(&command_list));
		return command_list;
	}

	ComPtr<::ID3D12Fence1>
	CreateFence(::UINT64 initial_value, ::D3D12_FENCE_FLAGS flags)
	{
		ComPtr<::ID3D12Fence1> fence;
		m_device->CreateFence(initial_value, flags, IID_PPV_ARGS(&fence));
		return fence;
	}

	ComPtr<::ID3D12DescriptorHeap>
	CreateDescriptorHeap(::D3D12_DESCRIPTOR_HEAP_DESC const& desc)
	{
		ComPtr<::ID3D12DescriptorHeap> descriptor_heap;
		m_device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptor_heap));
		return descriptor_heap;
	}

	::UINT
	GetDescriptorHandleIncrementSize(::D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type)
	{
		return m_device->GetDescriptorHandleIncrementSize(descriptor_heap_type);
	}

	void CreateRenderTargetView(
		::ID3D12Resource* resource,
		::D3D12_RENDER_TARGET_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE dest_descriptor)
	{
		m_device->CreateRenderTargetView(resource, desc, dest_descriptor);
	}

private:
	ComPtr<::ID3D12Device8>	m_device;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_DEVICE_HPP
