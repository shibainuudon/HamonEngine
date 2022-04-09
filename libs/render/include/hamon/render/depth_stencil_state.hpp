/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/comparison_func.hpp>
#include <hamon/render/stencil_operation.hpp>
#include <cstdint>

namespace hamon
{

inline namespace render
{

struct DepthStencilState
{
	struct
	{
		bool            enable{true};
		bool            write {true};
		ComparisonFunc  func  {ComparisonFunc::Less};
	} depth;

	struct
	{
		bool				enable              {false};
		std::uint8_t		read_mask           {0xff};
		std::uint8_t		write_mask          {0xff};
		StencilOperation	fail_operation      {StencilOperation::Keep};
		StencilOperation	depth_fail_operation{StencilOperation::Keep};
		StencilOperation	pass_operation      {StencilOperation::Keep};
		ComparisonFunc		func                {ComparisonFunc::Always};
		std::uint8_t		reference           {0x00};
	} stencil;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DEPTH_STENCIL_STATE_HPP
