/**
 *	@file	type.hpp
 *
 *	@brief	Type
 */

#ifndef HAMON_RENDER_TYPE_HPP
#define HAMON_RENDER_TYPE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class Type : std::uint32_t
{
	Int8,
	Int16,
	Int32,
	UInt8,
	UInt16,
	UInt32,
	Float,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_TYPE_HPP
