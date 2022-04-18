/**
 *	@file	index_type.hpp
 *
 *	@brief	IndexType
 */

#ifndef HAMON_RENDER_D3D12_INDEX_TYPE_HPP
#define HAMON_RENDER_D3D12_INDEX_TYPE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/index_type.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::DXGI_FORMAT
IndexType(render::IndexType type)
{
	switch (type)
	{
	case render::IndexType::UInt16:	return DXGI_FORMAT_R16_UINT;
	case render::IndexType::UInt32:	return DXGI_FORMAT_R32_UINT;
	}
	return DXGI_FORMAT_R16_UINT;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_INDEX_TYPE_HPP
