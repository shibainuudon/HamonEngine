/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode
 */

#ifndef HAMON_RENDER_D3D11_CULL_MODE_HPP
#define HAMON_RENDER_D3D11_CULL_MODE_HPP

#include <hamon/render/cull_mode.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_CULL_MODE CullMode(render::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case render::CullMode::None:  return D3D11_CULL_NONE;
	case render::CullMode::Front: return D3D11_CULL_FRONT;
	case render::CullMode::Back:  return D3D11_CULL_BACK;
	}
	return D3D11_CULL_NONE;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_CULL_MODE_HPP
