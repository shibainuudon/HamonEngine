/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_RASTERIZER_STATE_HPP
#define HAMON_RENDER_RASTERIZER_STATE_HPP

#include <hamon/render/fill_mode.hpp>
#include <hamon/render/cull_mode.hpp>
#include <hamon/render/front_face.hpp>

namespace hamon
{

inline namespace render
{

struct RasterizerState
{
	FillMode	fill_mode  { FillMode::Solid };
	CullMode	cull_mode  { CullMode::Back  };
	FrontFace	front_face { FrontFace::Clockwise };
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RASTERIZER_STATE_HPP
