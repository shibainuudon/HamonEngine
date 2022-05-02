/**
 *	@file	device.hpp
 *
 *	@brief	Device
 */

#ifndef HAMON_RENDER_D3D12_DEVICE_HPP
#define HAMON_RENDER_D3D12_DEVICE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d/dxgi.hpp>
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
	explicit Device(std::vector<ComPtr<::IDXGIAdapter4>> const& adapters)
	{
		::D3D_FEATURE_LEVEL const feature_levels[] =
		{
			::D3D_FEATURE_LEVEL_12_1,
			::D3D_FEATURE_LEVEL_12_0,
			::D3D_FEATURE_LEVEL_11_1,
			::D3D_FEATURE_LEVEL_11_0,
		};

		::HRESULT hr = S_OK;
		for (auto const& adapter : adapters)
		{
			for (auto feature_level : feature_levels)
			{
				hr = ::D3D12CreateDevice(
					adapter.Get(),
					feature_level,
					IID_PPV_ARGS(&m_device));

				if (SUCCEEDED(hr))
				{
					return;
				}
			}
		}
		ThrowIfFailed(hr);
	}

	ComPtr<::ID3D12CommandQueue>
	CreateCommandQueue(::D3D12_COMMAND_QUEUE_DESC const& desc)
	{
		ComPtr<::ID3D12CommandQueue> command_queue;
		ThrowIfFailed(m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue)));
		return command_queue;
	}

	ComPtr<::ID3D12CommandAllocator>
	CreateCommandAllocator(::D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<::ID3D12CommandAllocator> command_allocator;
		ThrowIfFailed(m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator)));
		return command_allocator;
	}

	ComPtr<::ID3D12GraphicsCommandList6>
	CreateGraphicsCommandList(::D3D12_COMMAND_LIST_TYPE type, ::ID3D12CommandAllocator* command_allocator)
	{
		ComPtr<::ID3D12GraphicsCommandList6> command_list;
		ThrowIfFailed(m_device->CreateCommandList(
			0,	// nodeMask
			type,
			command_allocator,
			nullptr,
			IID_PPV_ARGS(&command_list)));
		return command_list;
	}

	ComPtr<::ID3D12Fence1>
	CreateFence(::UINT64 initial_value, ::D3D12_FENCE_FLAGS flags)
	{
		ComPtr<::ID3D12Fence1> fence;
		ThrowIfFailed(m_device->CreateFence(initial_value, flags, IID_PPV_ARGS(&fence)));
		return fence;
	}

	ComPtr<::ID3D12DescriptorHeap>
	CreateDescriptorHeap(::D3D12_DESCRIPTOR_HEAP_DESC const& desc)
	{
		ComPtr<::ID3D12DescriptorHeap> descriptor_heap;
		ThrowIfFailed(m_device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptor_heap)));
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

	void CreateConstantBufferView(
		::D3D12_CONSTANT_BUFFER_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE			 dest_descriptor)
	{
		m_device->CreateConstantBufferView(desc, dest_descriptor);
	}

	ComPtr<::ID3D12RootSignature> CreateRootSignature(
		::UINT       node_mask,
		const void*  blob_with_root_signature,
		::SIZE_T     blob_length_in_bytes)
	{
		ComPtr<::ID3D12RootSignature> root_signature;
		ThrowIfFailed(m_device->CreateRootSignature(
			node_mask,
			blob_with_root_signature,
			blob_length_in_bytes,
			IID_PPV_ARGS(&root_signature)));
		return root_signature;
	}
	
	ComPtr<::ID3D12PipelineState> CreateGraphicsPipelineState(
		const D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc)
	{
		ComPtr<::ID3D12PipelineState> pipeline_state;
		ThrowIfFailed(m_device->CreateGraphicsPipelineState(
			desc,
			IID_PPV_ARGS(&pipeline_state)));
		return pipeline_state;
	}

	ComPtr<::ID3D12Resource1> CreateCommittedResource(
		const ::D3D12_HEAP_PROPERTIES* heap_properties,
		::D3D12_HEAP_FLAGS            heap_flags,
		const ::D3D12_RESOURCE_DESC* desc,
		::D3D12_RESOURCE_STATES       initial_resource_state,
		const ::D3D12_CLEAR_VALUE* optimized_clear_value)
	{
		ComPtr<::ID3D12Resource1> resource;
		ThrowIfFailed(m_device->CreateCommittedResource(
			heap_properties,
			heap_flags,
			desc,
			initial_resource_state,
			optimized_clear_value,
			IID_PPV_ARGS(&resource)));
		return resource;
	}

	void CreateShaderResourceView(
		::ID3D12Resource* resource,
		::D3D12_SHADER_RESOURCE_VIEW_DESC const& desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE            dest_descriptor)
	{
		m_device->CreateShaderResourceView(resource, &desc, dest_descriptor);
	}

	void CreateSampler(
		::D3D12_SAMPLER_DESC const& desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE dest_descriptor)
	{
		m_device->CreateSampler(&desc, dest_descriptor);
	}

	void GetCopyableFootprints(
		::D3D12_RESOURCE_DESC const*          resource_desc,
		::UINT                                first_subresource,
		::UINT                                num_subresources,
		::UINT64                              base_offset,
		::D3D12_PLACED_SUBRESOURCE_FOOTPRINT* layouts,
		::UINT*                               num_rows,
		::UINT64*                             row_size_in_bytes,
		::UINT64*                             total_bytes)
	{
		m_device->GetCopyableFootprints(
			resource_desc,
			first_subresource,
			num_subresources,
			base_offset,
			layouts,
			num_rows,
			row_size_in_bytes,
			total_bytes);
	}

private:
	ComPtr<::ID3D12Device8>	m_device;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_DEVICE_HPP
