/**
 *	@file	constant_buffer.hpp
 *
 *	@brief	ConstantBuffer
 */

#ifndef HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP
#define HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/resource.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class ConstantBuffer
{
private:
	static ::UINT64 RoundUp(::UINT64 x, ::UINT64 align)
	{
		return (x + (align - 1)) & ~(align - 1);
	}

public:
	explicit ConstantBuffer(
		d3d12::Device* device,
		::UINT64 size)
		: m_size(RoundUp(size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT))
		, m_resource(device, m_size, nullptr)
	{
		m_mapped_resource = static_cast<std::uint8_t*>(m_resource.Map(0, nullptr));
	}

	struct Subresource
	{
		D3D12_GPU_VIRTUAL_ADDRESS	gpu_virtual_address;
		std::uint8_t*				mapped_resource;
	};

	Subresource Allocate(::UINT64 size)
	{
		auto const offset = m_offset;
		m_offset += size;
		return
		{
			m_resource.Get()->GetGPUVirtualAddress() + offset,
			m_mapped_resource + offset
		};
	}

	void Reset(void)
	{
		m_offset = 0;
	}

private:
	::UINT64				m_size{};
	::UINT64				m_offset{};
	d3d12::Resource			m_resource;
	std::uint8_t*			m_mapped_resource;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP
