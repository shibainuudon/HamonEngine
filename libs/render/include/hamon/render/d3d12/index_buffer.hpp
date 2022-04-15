/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer
 */

#ifndef HAMON_RENDER_D3D12_INDEX_BUFFER_HPP
#define HAMON_RENDER_D3D12_INDEX_BUFFER_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d12/resource.hpp>
#include <hamon/render/geometry.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class IndexBuffer
{
public:
	IndexBuffer(Device* device, render::Geometry const& geometry)
		: m_resource(device, geometry.GetIndexArrayBytes(), geometry.GetIndexArrayData())
		, m_count(static_cast<::UINT>(geometry.GetIndexArrayCount()))
	{
		auto const size = geometry.GetVertexArrayBytes();

		// IndexBufferView を初期化
		m_view.BufferLocation = m_resource.Get()->GetGPUVirtualAddress();
		m_view.SizeInBytes = static_cast<::UINT>(size);
		m_view.Format = DXGI_FORMAT_R16_UINT;
	}
	
	void Bind(CommandList* command_list)
	{
		command_list->IASetIndexBuffer(&m_view);
	}

	void Draw(CommandList * command_list)
	{
		command_list->DrawIndexedInstanced(m_count, 1, 0, 0, 0);
	}

private:
	d3d12::Resource				m_resource;
	::D3D12_INDEX_BUFFER_VIEW	m_view;
	::UINT						m_count{0};
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_INDEX_BUFFER_HPP
