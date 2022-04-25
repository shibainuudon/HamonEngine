/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer
 */

#ifndef HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP
#define HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d12/resource.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/d3d12.hpp>
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
	VertexBuffer(
		d3d12::Device* device,
		render::Geometry const& geometry)
		: m_resource(device, geometry.GetVertexArrayBytes(), geometry.GetVertexArrayData())
		, m_count(static_cast<::UINT>(geometry.GetVertexArrayCount()))
	{
		auto const size = geometry.GetVertexArrayBytes();
		auto const stride = geometry.GetLayout().GetBytes();

		// VertexBufferView を初期化
		m_view.BufferLocation = m_resource.Get()->GetGPUVirtualAddress();
        m_view.StrideInBytes = static_cast<::UINT>(stride);
        m_view.SizeInBytes = static_cast<::UINT>(size);
	}
	
	void Bind(d3d12::CommandList* command_list)
	{
		command_list->IASetVertexBuffers(0, 1, &m_view);
	}

	void Draw(d3d12::CommandList* command_list)
	{
		command_list->DrawInstanced(m_count, 1, 0, 0);
	}

private:
	d3d12::Resource				m_resource;
	::D3D12_VERTEX_BUFFER_VIEW	m_view;
	::UINT						m_count{0};
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_VERTEX_BUFFER_HPP
