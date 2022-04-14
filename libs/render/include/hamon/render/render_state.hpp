/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState
 */

#ifndef HAMON_RENDER_RENDER_STATE_HPP
#define HAMON_RENDER_RENDER_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/depth_stencil_state.hpp>
#include <hamon/render/rasterizer_state.hpp>

namespace hamon
{

inline namespace render
{

struct RenderState
{
	BlendState			blend_state;
	DepthStencilState	depth_stencil_state;
	RasterizerState		rasterizer_state;
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/detail/hash_combine.hpp>
#include <functional>

namespace std
{

template <>
struct hash<hamon::render::RenderState>
{
	std::size_t operator()(hamon::render::RenderState const& arg) const
	{
		return hamon::render::detail::HashCombine(
			arg.blend_state,
			arg.depth_stencil_state,
			arg.rasterizer_state);
	}
};

}	// namespace std

#endif // HAMON_RENDER_RENDER_STATE_HPP
