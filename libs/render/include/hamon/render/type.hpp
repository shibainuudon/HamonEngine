/**
 *	@file	type.hpp
 *
 *	@brief	Type
 */

#ifndef HAMON_RENDER_TYPE_HPP
#define HAMON_RENDER_TYPE_HPP

#include <cstdint>
#include <type_traits>

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

template <typename T>
struct TypeToEnum
{
private:
	template <typename U, bool Signed, std::size_t Size>
	struct Helper;

	template <typename U> struct Helper<U, true,  1> { static const Type value = Type::Int8; };
	template <typename U> struct Helper<U, true,  2> { static const Type value = Type::Int16; };
	template <typename U> struct Helper<U, true,  4> { static const Type value = Type::Int32; };
	template <typename U> struct Helper<U, false, 1> { static const Type value = Type::UInt8; };
	template <typename U> struct Helper<U, false, 2> { static const Type value = Type::UInt16; };
	template <typename U> struct Helper<U, false, 4> { static const Type value = Type::UInt32; };

public:
	static const Type value = Helper<T, std::is_signed_v<T>, sizeof(T)>::value;
};

template <>
struct TypeToEnum<float>
{
	static const Type value = Type::Float; 
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_TYPE_HPP
