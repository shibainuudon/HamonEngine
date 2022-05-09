/**
 *	@file	compare_operation.hpp
 *
 *	@brief	CompareOperation
 */

#ifndef HAMON_RENDER_COMPARE_OPERATION_HPP
#define HAMON_RENDER_COMPARE_OPERATION_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class CompareOperation : std::uint32_t
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

#endif // HAMON_RENDER_COMPARE_OPERATION_HPP
