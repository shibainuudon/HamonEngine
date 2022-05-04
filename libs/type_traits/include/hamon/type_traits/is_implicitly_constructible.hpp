/**
 *	@file	is_implicitly_constructible.hpp
 *
 *	@brief	is_implicitly_constructible
 */

#ifndef HAMON_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが暗黙に構築可能か調べる。
 *			T( Args... ) の形式のコンストラクタ呼び出しが暗黙に可能であるか。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_implicitly_constructibleは、T( Args... )の形式のコンストラクタ呼出しが暗黙に可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T, typename... Args>
struct is_implicitly_constructible;

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename... Args>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_implicitly_constructible_v = is_implicitly_constructible<T, Args...>::value;

#endif

namespace detail
{

template <bool, typename T, typename... Args>
struct is_implicitly_constructible_impl
{
private:
	template <typename T1>
	static void test_helper(T1);

	template <typename T1, typename... Args1>
	static auto test(int)
		-> decltype(test_helper<T1>({std::declval<Args1>()...}), std::true_type());

	template <typename T1, typename... Args1>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T, Args...>(0));
};

template <typename T, typename... Args>
struct is_implicitly_constructible_impl<true, T, Args...>
	: public std::true_type
{};

template <bool, typename T, typename... Args>
struct is_implicitly_constructible
	: public is_implicitly_constructible_impl<
		std::is_trivially_constructible<T, Args...>::value,
		T, Args...
	>::type
{};

template <typename T, typename... Args>
struct is_implicitly_constructible<false, T, Args...>
	: public std::false_type
{};

}	// namespace detail

template <typename T, typename... Args>
struct is_implicitly_constructible
	: public detail::is_implicitly_constructible<
		std::is_constructible<T, Args...>::value,
		T, Args...
	>
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
