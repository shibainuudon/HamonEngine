/**
 *	@file	descriptor_heap.hpp
 *
 *	@brief	DescriptorHeap
 */

#ifndef HAMON_RENDER_D3D12_descriptor_heap_HPP
#define HAMON_RENDER_D3D12_descriptor_heap_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class DescriptorHeap
{
public:
	explicit DescriptorHeap(
		d3d12::Device* device,
		::D3D12_DESCRIPTOR_HEAP_TYPE type,
		::UINT num,
		::D3D12_DESCRIPTOR_HEAP_FLAGS flags)
	{
		::D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.Type           = type;
		desc.NumDescriptors = num;
		desc.Flags          = flags;
		desc.NodeMask       = 0;

		m_descriptor_heap       = device->CreateDescriptorHeap(desc);
		m_handle_increment_size = device->GetDescriptorHandleIncrementSize(type);
		Reset();
	}

	auto AssignGpuDescriptorHandle(void)
	{
		auto handle = m_gpu_handle;
		m_gpu_handle.ptr += m_handle_increment_size;
		return handle;
	}

	auto AssignCpuDescriptorHandle(void)
	{
		auto handle = m_cpu_handle;
		m_cpu_handle.ptr += m_handle_increment_size;
		return handle;
	}

	void Reset(void)
	{
		m_gpu_handle = m_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
		m_cpu_handle = m_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
	}

	auto Get(void) const
	{
		return m_descriptor_heap.Get();
	}

private:
	ComPtr<::ID3D12DescriptorHeap>	m_descriptor_heap;
	::UINT							m_handle_increment_size;
	::D3D12_GPU_DESCRIPTOR_HANDLE	m_gpu_handle;
	::D3D12_CPU_DESCRIPTOR_HANDLE	m_cpu_handle;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_descriptor_heap_HPP
