/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState
 */

#ifndef HAMON_RENDER_D3D12_DEPTH_STENCIL_STATE_HPP
#define HAMON_RENDER_D3D12_DEPTH_STENCIL_STATE_HPP

#include <hamon/render/depth_stencil_state.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class DepthStencilState
{
public:
	explicit DepthStencilState(render::DepthStencilState const& state)
	{
		m_desc.DepthEnable                  = state.depth.enable;
		m_desc.DepthWriteMask               = ToD3D12DepthWriteMask(state.depth.write);
		m_desc.DepthFunc                    = ToD3D12ComparisonFunc(state.depth.func);
		m_desc.StencilEnable                = state.stencil.enable;
		m_desc.StencilReadMask              = state.stencil.read_mask;
		m_desc.StencilWriteMask             = state.stencil.write_mask;
		m_desc.FrontFace.StencilFailOp      = ToD3D12StencilOp(state.stencil.fail_operation);
		m_desc.FrontFace.StencilDepthFailOp = ToD3D12StencilOp(state.stencil.depth_fail_operation);
		m_desc.FrontFace.StencilPassOp      = ToD3D12StencilOp(state.stencil.pass_operation);
		m_desc.FrontFace.StencilFunc        = ToD3D12ComparisonFunc(state.stencil.func);
		
		// FrontとBackのStencil設定を同じにする
		m_desc.BackFace = m_desc.FrontFace;
	}
	
	::D3D12_DEPTH_STENCIL_DESC const& Get(void) const { return m_desc; }

private:
	static ::D3D12_DEPTH_WRITE_MASK ToD3D12DepthWriteMask(bool write)
	{
		return write ?
			D3D12_DEPTH_WRITE_MASK_ALL :
			D3D12_DEPTH_WRITE_MASK_ZERO;
	}

	static ::D3D12_COMPARISON_FUNC ToD3D12ComparisonFunc(render::ComparisonFunc func)
	{
		switch (func)
		{
		case render::ComparisonFunc::Never:			return D3D12_COMPARISON_FUNC_NEVER;
		case render::ComparisonFunc::Less:			return D3D12_COMPARISON_FUNC_LESS;
		case render::ComparisonFunc::Equal:			return D3D12_COMPARISON_FUNC_EQUAL;
		case render::ComparisonFunc::LessEqual:		return D3D12_COMPARISON_FUNC_LESS_EQUAL;
		case render::ComparisonFunc::Greater:		return D3D12_COMPARISON_FUNC_GREATER;
		case render::ComparisonFunc::NotEqual:		return D3D12_COMPARISON_FUNC_NOT_EQUAL;
		case render::ComparisonFunc::GreaterEqual:	return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
		case render::ComparisonFunc::Always:		return D3D12_COMPARISON_FUNC_ALWAYS;
		}
		return D3D12_COMPARISON_FUNC_NEVER;
	}

	static ::D3D12_STENCIL_OP ToD3D12StencilOp(render::StencilOperation op)
	{
		switch (op)
		{
		case render::StencilOperation::Keep:				return D3D12_STENCIL_OP_KEEP;
		case render::StencilOperation::Zero:				return D3D12_STENCIL_OP_ZERO;
		case render::StencilOperation::Replace:				return D3D12_STENCIL_OP_REPLACE;
		case render::StencilOperation::IncrementSaturate:	return D3D12_STENCIL_OP_INCR_SAT;
		case render::StencilOperation::DecrementSaturate:	return D3D12_STENCIL_OP_DECR_SAT;
		case render::StencilOperation::Invert:				return D3D12_STENCIL_OP_INVERT;
		case render::StencilOperation::Increment:			return D3D12_STENCIL_OP_INCR;
		case render::StencilOperation::Decrement:			return D3D12_STENCIL_OP_DECR;
		}
		return D3D12_STENCIL_OP_KEEP;
	}

private:
	::D3D12_DEPTH_STENCIL_DESC	m_desc{};
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_DEPTH_STENCIL_STATE_HPP
