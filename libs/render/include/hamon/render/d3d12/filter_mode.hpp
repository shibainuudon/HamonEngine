/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode
 */

#ifndef HAMON_RENDER_D3D12_FILTER_MODE_HPP
#define HAMON_RENDER_D3D12_FILTER_MODE_HPP

#include <hamon/render/filter_mode.hpp>
#include <hamon/render/mipmap_mode.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_FILTER_TYPE FilterType(render::FilterMode mode)
{
	switch (mode)
	{
	case render::FilterMode::Nearest:   return D3D12_FILTER_TYPE_POINT;
	case render::FilterMode::Linear:    return D3D12_FILTER_TYPE_LINEAR;
	}
    return D3D12_FILTER_TYPE_POINT;
}

inline ::D3D12_FILTER_TYPE FilterType(render::MipmapMode mode)
{
	switch (mode)
	{
	case render::MipmapMode::Nearest:   return D3D12_FILTER_TYPE_POINT;
	case render::MipmapMode::Linear:    return D3D12_FILTER_TYPE_LINEAR;
	}
    return D3D12_FILTER_TYPE_POINT;
}

inline ::D3D12_FILTER_REDUCTION_TYPE FilterReductionType(bool comparison)
{
    if (comparison)
    {
        return D3D12_FILTER_REDUCTION_TYPE_COMPARISON;
    }
    else
    {
        return D3D12_FILTER_REDUCTION_TYPE_STANDARD;
    }
    // TODO
    // D3D12_FILTER_REDUCTION_TYPE_MINIMUM
    // D3D12_FILTER_REDUCTION_TYPE_MAXIMUM
}

inline ::D3D12_FILTER FilterMode(
    render::FilterMode min_filter,
    render::FilterMode mag_filter,
    render::MipmapMode mip_filter,
    bool               compare_enable)
{
    return D3D12_ENCODE_BASIC_FILTER(
        FilterType(min_filter),
        FilterType(mag_filter),
        FilterType(mip_filter),
        FilterReductionType(compare_enable));
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_FILTER_MODE_HPP
