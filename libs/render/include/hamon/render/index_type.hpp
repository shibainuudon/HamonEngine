/**
 *	@file	index_type.hpp
 *
 *	@brief	IndexType
 */

#ifndef HAMON_RENDER_INDEX_TYPE_HPP
#define HAMON_RENDER_INDEX_TYPE_HPP

#include <cstdint>
#include <type_traits>

namespace hamon
{

inline namespace render
{

enum class IndexType : std::uint32_t
{
	UInt16,
	UInt32,
};

template <typename T>
struct GetIndexType
{
private:
	template <typename U, bool Signed, std::size_t Size>
	struct Helper;

	template <typename U> struct Helper<U, false, 2> { static const IndexType value = IndexType::UInt16; };
	template <typename U> struct Helper<U, false, 4> { static const IndexType value = IndexType::UInt32; };

public:
	static const IndexType value = Helper<T, std::is_signed_v<T>, sizeof(T)>::value;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_INDEX_TYPE_HPP
