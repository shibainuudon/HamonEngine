/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation
 */

#ifndef HAMON_RENDER_D3D12_stencil_operation_HPP
#define HAMON_RENDER_D3D12_stencil_operation_HPP

#include <hamon/render/stencil_operation.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_STENCIL_OP StencilOperation(render::StencilOperation op)
{
	switch (op)
	{
	case render::StencilOperation::Keep:				return D3D12_STENCIL_OP_KEEP;
	case render::StencilOperation::Zero:				return D3D12_STENCIL_OP_ZERO;
	case render::StencilOperation::Replace:				return D3D12_STENCIL_OP_REPLACE;
	case render::StencilOperation::IncrementAndClamp:	return D3D12_STENCIL_OP_INCR_SAT;
	case render::StencilOperation::DecrementAndClamp:	return D3D12_STENCIL_OP_DECR_SAT;
	case render::StencilOperation::Invert:				return D3D12_STENCIL_OP_INVERT;
	case render::StencilOperation::IncrementAndWrap:	return D3D12_STENCIL_OP_INCR;
	case render::StencilOperation::DecrementAndWrap:	return D3D12_STENCIL_OP_DECR;
	}
	return D3D12_STENCIL_OP_KEEP;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_stencil_operation_HPP
