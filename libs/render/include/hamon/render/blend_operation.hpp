/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation
 */

#ifndef HAMON_RENDER_BLEND_OPERATION_HPP
#define HAMON_RENDER_BLEND_OPERATION_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class BlendOperation : std::uint32_t
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_BLEND_OPERATION_HPP
