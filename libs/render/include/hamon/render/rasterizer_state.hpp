/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_RASTERIZER_STATE_HPP
#define HAMON_RENDER_RASTERIZER_STATE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class FillMode : std::uint32_t
{
	Solid,
	Wireframe,
};

enum class CullMode : std::uint32_t
{
	None,
	Front,
	Back,
};

enum class FrontFace : std::uint32_t
{
	Clockwise,
	CounterClockwise,

	// alias
	CW = Clockwise,
	CCW = CounterClockwise,
};

struct RasterizerState
{
	FillMode	fill_mode  { FillMode::Solid };
	CullMode	cull_mode  { CullMode::Back  };
	FrontFace	front_face { FrontFace::Clockwise };
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RASTERIZER_STATE_HPP
