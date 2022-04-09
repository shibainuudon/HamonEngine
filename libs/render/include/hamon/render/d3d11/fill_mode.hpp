/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode
 */

#ifndef HAMON_RENDER_D3D11_FILL_MODE_HPP
#define HAMON_RENDER_D3D11_FILL_MODE_HPP

#include <hamon/render/fill_mode.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_FILL_MODE FillMode(render::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case render::FillMode::Solid:     return D3D11_FILL_SOLID;
	case render::FillMode::Wireframe: return D3D11_FILL_WIREFRAME;
	}
	return D3D11_FILL_SOLID;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_FILL_MODE_HPP
