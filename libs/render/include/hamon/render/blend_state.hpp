/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_BLEND_STATE_HPP
#define HAMON_RENDER_BLEND_STATE_HPP

#include <hamon/render/blend_factor.hpp>
#include <hamon/render/blend_operation.hpp>
#include <hamon/render/logic_operation.hpp>
#include <hamon/render/color_write_mask.hpp>
#include <cstdint>

namespace hamon
{

inline namespace render
{

struct BlendState
{
	bool			blend_enable     { false };
	BlendFactor		color_src_factor { BlendFactor::One };
	BlendFactor		color_dest_factor{ BlendFactor::Zero };
	BlendOperation	color_operation  { BlendOperation::Add };
	BlendFactor		alpha_src_factor { BlendFactor::One };
	BlendFactor		alpha_dest_factor{ BlendFactor::Zero };
	BlendOperation	alpha_operation  { BlendOperation::Add };

	bool			logic_op_enable  { false };
	LogicOperation	logic_operation  { LogicOperation::Noop };

	std::uint32_t	color_write_mask { ColorWriteMask::All };

	struct
	{
		float         r;
		float         g;
		float         b;
		float         a;
	}				constant_color{1, 1, 1, 1};
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/detail/hash_combine.hpp>
#include <functional>

namespace std
{

template <>
struct hash<hamon::render::BlendState>
{
	std::size_t operator()(hamon::render::BlendState const& arg) const
	{
		return hamon::render::detail::HashCombine(
			arg.blend_enable,
			arg.color_src_factor,
			arg.color_dest_factor,
			arg.color_operation,
			arg.alpha_src_factor,
			arg.alpha_dest_factor,
			arg.alpha_operation,
			arg.logic_op_enable,
			arg.logic_operation,
			arg.color_write_mask);
	}
};

}	// namespace std

#endif // HAMON_RENDER_BLEND_STATE_HPP
