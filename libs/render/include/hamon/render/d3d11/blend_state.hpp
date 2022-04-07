/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState
 */

#ifndef HAMON_RENDER_D3D11_BLEND_STATE_HPP
#define HAMON_RENDER_D3D11_BLEND_STATE_HPP

#include <hamon/render/blend_state.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class BlendState
{
public:
	explicit BlendState(render::BlendState const& blend_state)
	{
		m_desc.AlphaToCoverageEnable  = FALSE;
		m_desc.IndependentBlendEnable = FALSE;
		for (auto& rt : m_desc.RenderTarget)
		{
			rt.BlendEnable           = blend_state.blend_enable;
			rt.SrcBlend              = ToD3D11Blend(blend_state.color_src_factor);
			rt.DestBlend             = ToD3D11Blend(blend_state.color_dest_factor);
			rt.BlendOp               = ToD3D11BlendOp(blend_state.color_operation);
			rt.SrcBlendAlpha         = ToD3D11Blend(blend_state.alpha_src_factor);
			rt.DestBlendAlpha        = ToD3D11Blend(blend_state.alpha_dest_factor);
			rt.BlendOpAlpha          = ToD3D11BlendOp(blend_state.alpha_operation);

			rt.LogicOpEnable         = blend_state.logic_op_enable;
			rt.LogicOp               = ToD3D11LogiOp(blend_state.logic_operation);
			
			rt.RenderTargetWriteMask = ToD3D11WriteMask(blend_state.color_write_mask);
		}
	}
	
	::D3D11_BLEND_DESC1 const& Get(void) const { return m_desc; }

private:
	static ::D3D11_BLEND ToD3D11Blend(render::BlendFactor factor)
	{
		switch (factor)
		{
		case render::BlendFactor::Zero:				return D3D11_BLEND_ZERO;
		case render::BlendFactor::One:				return D3D11_BLEND_ONE;
		case render::BlendFactor::SrcColor:			return D3D11_BLEND_SRC_COLOR;
		case render::BlendFactor::InvSrcColor:		return D3D11_BLEND_INV_SRC_COLOR;
		case render::BlendFactor::SrcAlpha:			return D3D11_BLEND_SRC_ALPHA;
		case render::BlendFactor::InvSrcAlpha:		return D3D11_BLEND_INV_SRC_ALPHA;
		case render::BlendFactor::DestAlpha:		return D3D11_BLEND_DEST_ALPHA;
		case render::BlendFactor::InvDestAlpha:		return D3D11_BLEND_INV_DEST_ALPHA;
		case render::BlendFactor::DestColor:		return D3D11_BLEND_DEST_COLOR;
		case render::BlendFactor::InvDestColor:		return D3D11_BLEND_INV_DEST_COLOR;
		case render::BlendFactor::SrcAlphaSat:		return D3D11_BLEND_SRC_ALPHA_SAT;
		case render::BlendFactor::BlendFactor:		return D3D11_BLEND_BLEND_FACTOR;
		case render::BlendFactor::InvBlendFactor:	return D3D11_BLEND_INV_BLEND_FACTOR;
		case render::BlendFactor::Src1Color:		return D3D11_BLEND_SRC1_COLOR;
		case render::BlendFactor::InvSrc1Color:		return D3D11_BLEND_INV_SRC1_COLOR;
		case render::BlendFactor::Src1Alpha:		return D3D11_BLEND_SRC1_ALPHA;
		case render::BlendFactor::InvSrc1Alpha:		return D3D11_BLEND_INV_SRC1_ALPHA;
		}
		return D3D11_BLEND_ZERO;
	}

	static ::D3D11_BLEND_OP ToD3D11BlendOp(render::BlendOperation op)
	{
		switch (op)
		{
		case render::BlendOperation::Add:				return D3D11_BLEND_OP_ADD;
		case render::BlendOperation::Subtract:			return D3D11_BLEND_OP_SUBTRACT;
		case render::BlendOperation::ReverseSubtract:	return D3D11_BLEND_OP_REV_SUBTRACT;
		case render::BlendOperation::Min:				return D3D11_BLEND_OP_MIN;
		case render::BlendOperation::Max:				return D3D11_BLEND_OP_MAX;
		}
		return D3D11_BLEND_OP_ADD;
	}

	static ::D3D11_LOGIC_OP ToD3D11LogiOp(render::LogicOperation op)
	{
		switch (op)
		{
		case render::LogicOperation::Clear:			return D3D11_LOGIC_OP_CLEAR;
		case render::LogicOperation::Set:			return D3D11_LOGIC_OP_SET;
		case render::LogicOperation::Copy:			return D3D11_LOGIC_OP_COPY;
		case render::LogicOperation::CopyInverted:	return D3D11_LOGIC_OP_COPY_INVERTED;
		case render::LogicOperation::Noop:			return D3D11_LOGIC_OP_NOOP;
		case render::LogicOperation::Invert:		return D3D11_LOGIC_OP_INVERT;
		case render::LogicOperation::And:			return D3D11_LOGIC_OP_AND;
		case render::LogicOperation::Nand:			return D3D11_LOGIC_OP_NAND;
		case render::LogicOperation::Or:			return D3D11_LOGIC_OP_OR;
		case render::LogicOperation::Nor:			return D3D11_LOGIC_OP_NOR;
		case render::LogicOperation::Xor:			return D3D11_LOGIC_OP_XOR;
		case render::LogicOperation::Equiv:			return D3D11_LOGIC_OP_EQUIV;
		case render::LogicOperation::AndReverse:	return D3D11_LOGIC_OP_AND_REVERSE;
		case render::LogicOperation::AndInverted:	return D3D11_LOGIC_OP_AND_INVERTED;
		case render::LogicOperation::OrReverse:		return D3D11_LOGIC_OP_OR_REVERSE;
		case render::LogicOperation::OrInverted:	return D3D11_LOGIC_OP_OR_INVERTED;
		}
		return D3D11_LOGIC_OP_NOOP;
	}

	static ::UINT8 ToD3D11WriteMask(std::uint32_t mask)
	{
		::UINT8 result = 0;
		if (mask & render::ColorWriteMask::Red)
		{
			result |= D3D11_COLOR_WRITE_ENABLE_RED;
		}
		if (mask & render::ColorWriteMask::Green)
		{
			result |= D3D11_COLOR_WRITE_ENABLE_GREEN;
		}
		if (mask & render::ColorWriteMask::Blue)
		{
			result |= D3D11_COLOR_WRITE_ENABLE_BLUE;
		}
		if (mask & render::ColorWriteMask::Alpha)
		{
			result |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
		}
		return result;
	}

private:
	::D3D11_BLEND_DESC1	m_desc{};
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_BLEND_STATE_HPP
