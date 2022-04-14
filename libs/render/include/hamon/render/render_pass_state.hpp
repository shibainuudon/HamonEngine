/**
 *	@file	render_pass_state.hpp
 *
 *	@brief	RenderPassState
 */

#ifndef HAMON_RENDER_RENDER_PASS_STATE_HPP
#define HAMON_RENDER_RENDER_PASS_STATE_HPP

#include <hamon/render/clear_value.hpp>
#include <hamon/render/viewport.hpp>

namespace hamon
{

inline namespace render
{

struct RenderPassState
{
	ClearValue	clear_value;
	Viewport	viewport;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RENDER_PASS_STATE_HPP
