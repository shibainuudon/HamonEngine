/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode
 */

#ifndef HAMON_RENDER_D3D12_CULL_MODE_HPP
#define HAMON_RENDER_D3D12_CULL_MODE_HPP

#include <hamon/render/cull_mode.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_CULL_MODE CullMode(render::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case render::CullMode::None:	return D3D12_CULL_MODE_NONE;
	case render::CullMode::Front:	return D3D12_CULL_MODE_FRONT;
	case render::CullMode::Back:	return D3D12_CULL_MODE_BACK;
	}
	return D3D12_CULL_MODE_NONE;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_CULL_MODE_HPP
