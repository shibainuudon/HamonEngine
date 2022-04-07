/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_BLEND_STATE_HPP
#define HAMON_RENDER_BLEND_STATE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class BlendFactor : std::uint32_t
{
	Zero,
	One,
	SrcColor,
	InvSrcColor,
	SrcAlpha,
	InvSrcAlpha,
	DestAlpha,
	InvDestAlpha,
	DestColor,
	InvDestColor,
	SrcAlphaSat,
	BlendFactor,
	InvBlendFactor,
	Src1Color,
	InvSrc1Color,
	Src1Alpha,
	InvSrc1Alpha,
};

enum class BlendOperation : std::uint32_t
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max,
};

enum class LogicOperation : std::uint32_t
{
	Clear,
	Set,
	Copy,
	CopyInverted,
	Noop,
	Invert,
	And,
	Nand,
	Or,
	Nor,
	Xor,
	Equiv,
	AndReverse,
	AndInverted,
	OrReverse,
	OrInverted,
};

enum ColorWriteMask : std::uint32_t
{
	Red   = (1 << 0),
	Green = (1 << 1),
	Blue  = (1 << 2),
	Alpha = (1 << 3),
	All   = (Red | Green | Blue | Alpha),
};

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
