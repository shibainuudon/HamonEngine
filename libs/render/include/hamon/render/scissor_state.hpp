/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState
 */

#ifndef HAMON_RENDER_SCISSOR_STATE_HPP
#define HAMON_RENDER_SCISSOR_STATE_HPP

namespace hamon
{

inline namespace render
{

struct ScissorState
{
	bool          enable{false};
	std::uint32_t left  {0};
	std::uint32_t top   {0};
	std::uint32_t width {0};
	std::uint32_t height{0};
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SCISSOR_STATE_HPP
