/**
 *	@file	comparison_func.hpp
 *
 *	@brief	ComparisonFunc
 */

#ifndef HAMON_RENDER_COMPARISON_FUNC_HPP
#define HAMON_RENDER_COMPARISON_FUNC_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class ComparisonFunc : std::uint32_t
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_COMPARISON_FUNC_HPP
