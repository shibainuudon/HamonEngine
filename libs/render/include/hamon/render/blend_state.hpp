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
	bool independent_blend_enable {false};
	struct
	{
		bool			blend_enable     { false };
		BlendFactor		color_src_factor { BlendFactor::One };
		BlendFactor		color_dest_factor{ BlendFactor::Zero };
		BlendOperation	color_operation  { BlendOperation::Add };
		BlendFactor		alpha_src_factor { BlendFactor::One };
		BlendFactor		alpha_dest_factor{ BlendFactor::Zero };
		BlendOperation	alpha_operation  { BlendOperation::Add };
		std::uint32_t	color_write_mask { ColorWriteMask::All };
	} render_target[8];

	bool			logic_op_enable  { false };
	LogicOperation	logic_operation  { LogicOperation::Noop };

	struct
	{
		float         r;
		float         g;
		float         b;
		float         a;
	} constant_color{1, 1, 1, 1};
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
		std::size_t h = hamon::render::detail::HashCombine(arg.independent_blend_enable);
		for (auto const& r : arg.render_target)
		{
			h = hamon::render::detail::HashCombine(h,
				r.blend_enable,
				r.color_src_factor,
				r.color_dest_factor,
				r.color_operation,
				r.alpha_src_factor,
				r.alpha_dest_factor,
				r.alpha_operation,
				r.color_write_mask);
		}
		return hamon::render::detail::HashCombine(h,
			arg.logic_op_enable,
			arg.logic_operation,
			arg.constant_color.r,
			arg.constant_color.g,
			arg.constant_color.b,
			arg.constant_color.a);
	}
};

}	// namespace std

#endif // HAMON_RENDER_BLEND_STATE_HPP
