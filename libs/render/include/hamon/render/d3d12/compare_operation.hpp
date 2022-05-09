/**
 *	@file	compare_operation.hpp
 *
 *	@brief	CompareOperation
 */

#ifndef HAMON_RENDER_D3D12_COMPARE_OPERATION_HPP
#define HAMON_RENDER_D3D12_COMPARE_OPERATION_HPP

#include <hamon/render/compare_operation.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_COMPARISON_FUNC CompareOperation(render::CompareOperation op)
{
	switch (op)
	{
	case render::CompareOperation::Never:			return D3D12_COMPARISON_FUNC_NEVER;
	case render::CompareOperation::Less:			return D3D12_COMPARISON_FUNC_LESS;
	case render::CompareOperation::Equal:			return D3D12_COMPARISON_FUNC_EQUAL;
	case render::CompareOperation::LessEqual:		return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case render::CompareOperation::Greater:			return D3D12_COMPARISON_FUNC_GREATER;
	case render::CompareOperation::NotEqual:		return D3D12_COMPARISON_FUNC_NOT_EQUAL;
	case render::CompareOperation::GreaterEqual:	return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	case render::CompareOperation::Always:			return D3D12_COMPARISON_FUNC_ALWAYS;
	}
	return D3D12_COMPARISON_FUNC_NEVER;
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMPARE_OPERATION_HPP
