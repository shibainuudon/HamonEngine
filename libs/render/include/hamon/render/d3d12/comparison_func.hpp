/**
 *	@file	comparison_func.hpp
 *
 *	@brief	ComparisonFunc
 */

#ifndef HAMON_RENDER_D3D12_COMPARISON_FUNC_HPP
#define HAMON_RENDER_D3D12_COMPARISON_FUNC_HPP

#include <hamon/render/comparison_func.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_COMPARISON_FUNC ComparisonFunc(render::ComparisonFunc func)
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

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_COMPARISON_FUNC_HPP
