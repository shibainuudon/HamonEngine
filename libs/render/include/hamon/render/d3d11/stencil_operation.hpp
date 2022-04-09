/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation
 */

#ifndef HAMON_RENDER_D3D11_STENCIL_OPERATION_HPP
#define HAMON_RENDER_D3D11_STENCIL_OPERATION_HPP

#include <hamon/render/stencil_operation.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_STENCIL_OP StencilOperation(render::StencilOperation op)
{
	switch (op)
	{
	case render::StencilOperation::Keep:				return D3D11_STENCIL_OP_KEEP;
	case render::StencilOperation::Zero:				return D3D11_STENCIL_OP_ZERO;
	case render::StencilOperation::Replace:				return D3D11_STENCIL_OP_REPLACE;
	case render::StencilOperation::IncrementSaturate:	return D3D11_STENCIL_OP_INCR_SAT;
	case render::StencilOperation::DecrementSaturate:	return D3D11_STENCIL_OP_DECR_SAT;
	case render::StencilOperation::Invert:				return D3D11_STENCIL_OP_INVERT;
	case render::StencilOperation::Increment:			return D3D11_STENCIL_OP_INCR;
	case render::StencilOperation::Decrement:			return D3D11_STENCIL_OP_DECR;
	}
	return D3D11_STENCIL_OP_KEEP;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_STENCIL_OPERATION_HPP
