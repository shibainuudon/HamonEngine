/**
 *	@file	color_write_mask.hpp
 *
 *	@brief	ColorWriteMask
 */

#ifndef HAMON_RENDER_D3D12_COLOR_WRITE_MASK_HPP
#define HAMON_RENDER_D3D12_COLOR_WRITE_MASK_HPP

#include <hamon/render/color_write_mask.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

static ::UINT8 ColorWriteMask(std::uint32_t mask)
{
	::UINT8 result = 0;
	if (mask & render::ColorWriteMask::Red)
	{
		result |= D3D12_COLOR_WRITE_ENABLE_RED;
	}
	if (mask & render::ColorWriteMask::Green)
	{
		result |= D3D12_COLOR_WRITE_ENABLE_GREEN;
	}
	if (mask & render::ColorWriteMask::Blue)
	{
		result |= D3D12_COLOR_WRITE_ENABLE_BLUE;
	}
	if (mask & render::ColorWriteMask::Alpha)
	{
		result |= D3D12_COLOR_WRITE_ENABLE_ALPHA;
	}
	return result;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COLOR_WRITE_MASK_HPP
