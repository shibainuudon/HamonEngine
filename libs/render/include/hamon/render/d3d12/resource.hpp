/**
 *	@file	resource.hpp
 *
 *	@brief	Resource
 */

#ifndef HAMON_RENDER_D3D12_RESOURCE_HPP
#define HAMON_RENDER_D3D12_RESOURCE_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Resource
{
public:
	Resource(d3d12::Device* device, ::UINT64 size, void const* data)
	{
		::D3D12_HEAP_PROPERTIES prop = {};
		prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask     = 1;
		prop.VisibleNodeMask      = 1;

		::D3D12_RESOURCE_DESC desc = {};
		desc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment        = 0;
		desc.Width            = size;
		desc.Height           = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels        = 1;
		desc.Format           = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

		m_resource = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr);

		if (data != nullptr)
		{
			::UINT8* p = static_cast<::UINT8*>(this->Map(0, nullptr));
			std::memcpy(p, data, size);
			this->Unmap(0, nullptr);
		}
	}

	::ID3D12Resource1* Get(void) const
	{
		return	m_resource.Get();
	}

	void* Map(::UINT subresource, const ::D3D12_RANGE* read_range) const
	{
		void* result;
		ThrowIfFailed(m_resource->Map(subresource, read_range, &result));
		return result;
	}
	
	void Unmap(::UINT subresource, const ::D3D12_RANGE* written_range) const
	{
		m_resource->Unmap(subresource, written_range);
	}

private:
	ComPtr<::ID3D12Resource1>	m_resource;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_resource_HPP
