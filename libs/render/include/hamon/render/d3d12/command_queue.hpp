/**
 *	@file	command_queue.hpp
 *
 *	@brief	CommandQueue
 */

#ifndef HAMON_RENDER_D3D12_COMMAND_QUEUE_HPP
#define HAMON_RENDER_D3D12_COMMAND_QUEUE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_list.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class CommandQueue
{
public:
	explicit CommandQueue(Device* device)
	{
		::D3D12_COMMAND_QUEUE_DESC desc {};
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;

		m_command_queue = device->CreateCommandQueue(desc);
	}

	void Signal(::ID3D12Fence* fence, ::UINT64 value)
	{
		m_command_queue->Signal(fence, value);
	}

	void ExecuteCommandList(CommandList* command_list)
	{
		::ID3D12CommandList* command_lists[] = { command_list->Get() };
		m_command_queue->ExecuteCommandLists(ARRAYSIZE(command_lists), command_lists);
	}

	::ID3D12CommandQueue* Get(void) const { return m_command_queue.Get(); }

private:
	ComPtr<::ID3D12CommandQueue>	m_command_queue;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMMAND_QUEUE_HPP
