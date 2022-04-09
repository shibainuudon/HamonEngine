/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation
 */

#ifndef HAMON_RENDER_STENCIL_OPERATION_HPP
#define HAMON_RENDER_STENCIL_OPERATION_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class StencilOperation : std::uint32_t
{
	Keep,
	Zero,
	Replace,
	IncrementSaturate,
	DecrementSaturate,
	Invert,
	Increment,
	Decrement,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_STENCIL_OPERATION_HPP
