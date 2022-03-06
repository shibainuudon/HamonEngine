/**
 *	@file	command_allocator.hpp
 *
 *	@brief	CommandAllocator
 */

#ifndef HAMON_RENDER_D3D12_COMMAND_ALLOCATOR_HPP
#define HAMON_RENDER_D3D12_COMMAND_ALLOCATOR_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/device.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class CommandAllocator
{
public:
	explicit CommandAllocator(Device* device)
	{
		m_command_allocator = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	void Reset()
	{
		m_command_allocator->Reset();
	}

	::ID3D12CommandAllocator* Get(void) const { return m_command_allocator.Get(); }

private:
	ComPtr<::ID3D12CommandAllocator>	m_command_allocator;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMMAND_ALLOCATOR_HPP
