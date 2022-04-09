/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_DEPTH_STENCIL_STATE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class ComparisonFunc : std::uint32_t
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
};

enum class StencilOperation : std::uint32_t
{
	Keep,
	Zero,
	Replace,
	IncrementSaturate,
	DecrementSaturate,
	Invert,
	Increment,
	Decrement,
};

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
