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
		m_command_list->Close();
	}

	void Reset(CommandAllocator* command_allocator)
	{
		m_command_list->Reset(command_allocator->Get(), nullptr);
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

	::ID3D12GraphicsCommandList6* Get(void) const { return m_command_list.Get(); }

private:
	ComPtr<::ID3D12GraphicsCommandList6>	m_command_list;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMMAND_LIST_HPP
