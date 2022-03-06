/**
 *	@file	fence.hpp
 *
 *	@brief	Fence
 */

#ifndef HAMON_RENDER_D3D12_FENCE_HPP
#define HAMON_RENDER_D3D12_FENCE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_queue.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Fence
{
public:
	explicit Fence(Device* device, ::UINT buffer_count)
	{
		::UINT64 const initial_value = 0;
		m_fence = device->CreateFence(initial_value, D3D12_FENCE_FLAG_NONE);
		m_values.resize(buffer_count, initial_value + 1);
		m_event = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	}

	void WaitForGpu(CommandQueue* command_queue, ::UINT frame_index)
	{
		command_queue->Signal(m_fence.Get(), m_values[frame_index]);

		m_fence->SetEventOnCompletion(m_values[frame_index], m_event);
		WaitForSingleObjectEx(m_event, INFINITE, FALSE);

		m_values[frame_index]++;
	}

	void Close(void)
	{
		::CloseHandle(m_event);
	}

	void MoveToNextFrame(CommandQueue* command_queue, ::UINT frame_index)
	{
		auto const current_value = m_values[frame_index];
		command_queue->Signal(m_fence.Get(), current_value);

		auto next_index = (frame_index + 1) % m_values.size();

		if (m_fence->GetCompletedValue() < m_values[next_index])
		{
			m_fence->SetEventOnCompletion(m_values[next_index], m_event);
			WaitForSingleObjectEx(m_event, INFINITE, FALSE);
		}

		m_values[next_index] = current_value + 1;
	}

private:
	ComPtr<::ID3D12Fence1>	m_fence;
	std::vector<::UINT64>	m_values;
	::HANDLE				m_event;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_FENCE_HPP
