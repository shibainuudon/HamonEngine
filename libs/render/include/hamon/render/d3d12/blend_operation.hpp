/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation
 */

#ifndef HAMON_RENDER_D3D12_BLEND_OPERATION_HPP
#define HAMON_RENDER_D3D12_BLEND_OPERATION_HPP

#include <hamon/render/blend_operation.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_BLEND_OP BlendOperation(render::BlendOperation op)
{
	switch (op)
	{
	case render::BlendOperation::Add:				return D3D12_BLEND_OP_ADD;
	case render::BlendOperation::Subtract:			return D3D12_BLEND_OP_SUBTRACT;
	case render::BlendOperation::ReverseSubtract:	return D3D12_BLEND_OP_REV_SUBTRACT;
	case render::BlendOperation::Min:				return D3D12_BLEND_OP_MIN;
	case render::BlendOperation::Max:				return D3D12_BLEND_OP_MAX;
	}
	return D3D12_BLEND_OP_ADD;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_BLEND_OPERATION_HPP
