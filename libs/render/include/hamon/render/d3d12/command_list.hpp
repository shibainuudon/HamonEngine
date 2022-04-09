/**
 *	@file	command_list.hpp
 *
 *	@brief	CommandList
 */

#ifndef HAMON_RENDER_D3D12_COMMAND_LIST_HPP
#define HAMON_RENDER_D3D12_COMMAND_LIST_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_allocator.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class CommandList
{
public:
	explicit CommandList(Device* device, CommandAllocator* command_allocator)
	{
		m_command_list = device->CreateGraphicsCommandList(
			D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator->Get());
	}

	void Close(void)
	{
		ThrowIfFailed(m_command_list->Close());
	}

	void Reset(CommandAllocator* command_allocator)
	{
		ThrowIfFailed(m_command_list->Reset(command_allocator->Get(), nullptr));
	}

	void ResourceBarrier(
		::ID3D12Resource*       resource,
		::D3D12_RESOURCE_STATES state_before,
		::D3D12_RESOURCE_STATES state_after)
	{
		::D3D12_RESOURCE_BARRIER barrier;
		barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource   = resource;
		barrier.Transition.StateBefore = state_before;
		barrier.Transition.StateAfter  = state_after;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_command_list->ResourceBarrier(1, &barrier);
	}
	void IASetVertexBuffers(
		::UINT                            start_slot,
		::UINT                            num_views,
		const ::D3D12_VERTEX_BUFFER_VIEW* views)
	{
		m_command_list->IASetVertexBuffers(start_slot, num_views, views);
	}

	void IASetPrimitiveTopology(
		::D3D12_PRIMITIVE_TOPOLOGY primitive_topology)
	{
		m_command_list->IASetPrimitiveTopology(primitive_topology);
	}

	void DrawInstanced(
		::UINT vertex_count_per_instance,
		::UINT instance_count,
		::UINT start_vertex_location,
		::UINT start_instance_location)
	{
		m_command_list->DrawInstanced(
			vertex_count_per_instance,
			instance_count,
			start_vertex_location,
			start_instance_location);
	}

	void RSSetViewports(
		::UINT                  num_viewports,
		const ::D3D12_VIEWPORT* viewports)
	{
		m_command_list->RSSetViewports(num_viewports, viewports);
	}

	void RSSetScissorRects(
		::UINT              num_rects,
		const ::D3D12_RECT* rects)
	{
		m_command_list->RSSetScissorRects(num_rects, rects);
	}

	void OMSetRenderTargets(
		::UINT                               num_render_target_descriptors,
		::D3D12_CPU_DESCRIPTOR_HANDLE const* render_target_descriptors,
		::BOOL                               rts_single_handle_to_descriptor_range,
		::D3D12_CPU_DESCRIPTOR_HANDLE const* depth_stencil_descriptor)
	{
		m_command_list->OMSetRenderTargets(
			num_render_target_descriptors,
			render_target_descriptors,
			rts_single_handle_to_descriptor_range,
			depth_stencil_descriptor);
	}

	void OMSetStencilRef(::UINT stencil_ref)
	{
		m_command_list->OMSetStencilRef(stencil_ref);
	}

	void ClearRenderTargetView(
		::D3D12_CPU_DESCRIPTOR_HANDLE const& render_target_view,
		::FLOAT const*                       color_rgba,
		::UINT                               num_rects,
		::D3D12_RECT const*                  rects)
	{
		m_command_list->ClearRenderTargetView(
			render_target_view,
			color_rgba,
			num_rects,
			rects);
	}

	void SetGraphicsRootSignature(
		::ID3D12RootSignature* root_signature)
	{
		m_command_list->SetGraphicsRootSignature(root_signature);
	}

	void SetPipelineState(
		::ID3D12PipelineState* pipeline_state)
	{
		m_command_list->SetPipelineState(pipeline_state);
	}

	::ID3D12GraphicsCommandList6* Get(void) const { return m_command_list.Get(); }

private:
	ComPtr<::ID3D12GraphicsCommandList6>	m_command_list;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMMAND_LIST_HPP
