/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP
#define HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class VertexBuffer
{
public:
	VertexBuffer(Device* device, render::Geometry const& geometry)
	{
		auto const data = geometry.GetVertexArrayData();
		auto const size = geometry.GetVertexArrayBytes();
		auto const stride = geometry.GetLayout().GetBytes();

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

		// 頂点データをVertexBufferにコピー
		::UINT8* p;
		ThrowIfFailed(m_resource->Map(0, nullptr, reinterpret_cast<void**>(&p)));
		std::memcpy(p, data, size);
        m_resource->Unmap(0, nullptr);

		// VertexBufferView を初期化
		m_view.BufferLocation = m_resource->GetGPUVirtualAddress();
        m_view.StrideInBytes = static_cast<::UINT>(stride);
        m_view.SizeInBytes = static_cast<::UINT>(size);
	}

	void Draw(CommandList* command_list)
	{
		command_list->IASetVertexBuffers(0, 1, &m_view);
		command_list->DrawInstanced(3, 1, 0, 0);
	}

private:
	ComPtr<::ID3D12Resource1>	m_resource;
	::D3D12_VERTEX_BUFFER_VIEW	m_view;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP
