/**
 *	@file	hash_combine.hpp
 *
 *	@brief	HashCombine
 */

#ifndef HAMON_RENDER_DETAIL_HASH_COMBINE_HPP
#define HAMON_RENDER_DETAIL_HASH_COMBINE_HPP


namespace hamon
{

inline namespace render
{

namespace detail
{

template <typename T>
struct dependent_false : std::false_type {};

template <typename T>
inline std::size_t HashCombineImpl2(std::size_t seed, T const& v)
{
	if constexpr (sizeof(std::size_t) == 4)
	{
		return seed ^ (std::hash<T>{}(v) + 0x9e3779b9U           + (seed <<  6) + (seed >> 2));
	}
	else if constexpr (sizeof(std::size_t) == 8)
	{
		return seed ^ (std::hash<T>{}(v) + 0x9e3779b97f4a7c15LLU + (seed << 12) + (seed >> 4));
	}
	else
	{
		static_assert(dependent_false<T>::value);
	}
}

inline std::size_t HashCombineImpl(std::size_t seed)
{
	return seed;
}

template <typename T, typename... Args>
inline std::size_t HashCombineImpl(std::size_t seed, T const& v, Args const&... rest)
{
	return HashCombineImpl(HashCombineImpl2(seed, v), rest...);
}

template <typename... Args>
inline std::size_t HashCombine(Args const&... args)
{
	return HashCombineImpl(0, args...);
}

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_HASH_COMBINE_HPP
