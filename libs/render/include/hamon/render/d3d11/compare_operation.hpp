/**
 *	@file	compare_operation.hpp
 *
 *	@brief	CompareOperation
 */

#ifndef HAMON_RENDER_D3D11_COMPARE_OPERATION_HPP
#define HAMON_RENDER_D3D11_COMPARE_OPERATION_HPP

#include <hamon/render/compare_operation.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_COMPARISON_FUNC CompareOperation(render::CompareOperation op)
{
	switch (op)
	{
	case render::CompareOperation::Never:			return D3D11_COMPARISON_NEVER;
	case render::CompareOperation::Less:			return D3D11_COMPARISON_LESS;
	case render::CompareOperation::Equal:			return D3D11_COMPARISON_EQUAL;
	case render::CompareOperation::LessEqual:		return D3D11_COMPARISON_LESS_EQUAL;
	case render::CompareOperation::Greater:			return D3D11_COMPARISON_GREATER;
	case render::CompareOperation::NotEqual:		return D3D11_COMPARISON_NOT_EQUAL;
	case render::CompareOperation::GreaterEqual:	return D3D11_COMPARISON_GREATER_EQUAL;
	case render::CompareOperation::Always:			return D3D11_COMPARISON_ALWAYS;
	}
	return D3D11_COMPARISON_NEVER;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_COMPARE_OPERATION_HPP
