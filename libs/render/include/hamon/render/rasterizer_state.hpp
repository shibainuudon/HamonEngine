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

#include <hamon/render/detail/hash_combine.hpp>
#include <functional>

namespace std
{

template <>
struct hash<hamon::render::RasterizerState>
{
	std::size_t operator()(hamon::render::RasterizerState const& arg) const
	{
		return hamon::render::detail::HashCombine(
			arg.fill_mode,
			arg.cull_mode,
			arg.front_face);
	}
};

}	// namespace std

#endif // HAMON_RENDER_RASTERIZER_STATE_HPP
