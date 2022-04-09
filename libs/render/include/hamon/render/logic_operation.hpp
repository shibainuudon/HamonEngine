/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation
 */

#ifndef HAMON_RENDER_LOGIC_OPERATION_HPP
#define HAMON_RENDER_LOGIC_OPERATION_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class LogicOperation : std::uint32_t
{
	Clear,
	Set,
	Copy,
	CopyInverted,
	Noop,
	Invert,
	And,
	Nand,
	Or,
	Nor,
	Xor,
	Equiv,
	AndReverse,
	AndInverted,
	OrReverse,
	OrInverted,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_LOGIC_OPERATION_HPP
