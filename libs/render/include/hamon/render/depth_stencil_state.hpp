/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/compare_operation.hpp>
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
		bool             enable{true};
		bool             write {true};
		CompareOperation compare_operation {CompareOperation::Less};
	} depth;

	struct
	{
		bool				enable              {false};
		std::uint8_t		read_mask           {0xff};
		std::uint8_t		write_mask          {0xff};
		StencilOperation	fail_operation      {StencilOperation::Keep};
		StencilOperation	depth_fail_operation{StencilOperation::Keep};
		StencilOperation	pass_operation      {StencilOperation::Keep};
		CompareOperation	compare_operation   {CompareOperation::Always};
		std::uint8_t		reference           {0x00};
	} stencil;
};

}	// inline namespace render

}	// namespace hamon


#include <hamon/render/detail/hash_combine.hpp>
#include <functional>

namespace std
{

template <>
struct hash<hamon::render::DepthStencilState>
{
	std::size_t operator()(hamon::render::DepthStencilState const& arg) const
	{
		return hamon::render::detail::HashCombine(
			arg.depth.enable,
			arg.depth.write,
			arg.depth.compare_operation,
			arg.stencil.enable,
			arg.stencil.read_mask,
			arg.stencil.write_mask,
			arg.stencil.fail_operation,
			arg.stencil.depth_fail_operation,
			arg.stencil.pass_operation,
			arg.stencil.compare_operation,
			arg.stencil.reference);
	}
};

}	// namespace std

#endif // HAMON_RENDER_DEPTH_STENCIL_STATE_HPP
