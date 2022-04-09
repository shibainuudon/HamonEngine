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
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_BLEND_STATE_HPP
