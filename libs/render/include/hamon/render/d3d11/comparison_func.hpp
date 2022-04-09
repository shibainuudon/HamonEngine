/**
 *	@file	comparison_func.hpp
 *
 *	@brief	ComparisonFunc
 */

#ifndef HAMON_RENDER_D3D11_COMPARISON_FUNC_HPP
#define HAMON_RENDER_D3D11_COMPARISON_FUNC_HPP

#include <hamon/render/comparison_func.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_COMPARISON_FUNC ComparisonFunc(render::ComparisonFunc func)
{
	switch (func)
	{
	case render::ComparisonFunc::Never:			return D3D11_COMPARISON_NEVER;
	case render::ComparisonFunc::Less:			return D3D11_COMPARISON_LESS;
	case render::ComparisonFunc::Equal:			return D3D11_COMPARISON_EQUAL;
	case render::ComparisonFunc::LessEqual:		return D3D11_COMPARISON_LESS_EQUAL;
	case render::ComparisonFunc::Greater:		return D3D11_COMPARISON_GREATER;
	case render::ComparisonFunc::NotEqual:		return D3D11_COMPARISON_NOT_EQUAL;
	case render::ComparisonFunc::GreaterEqual:	return D3D11_COMPARISON_GREATER_EQUAL;
	case render::ComparisonFunc::Always:		return D3D11_COMPARISON_ALWAYS;
	}
	return D3D11_COMPARISON_NEVER;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_COMPARISON_FUNC_HPP
