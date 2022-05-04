/**
 *	@file	is_implicitly_copy_constructible.hpp
 *
 *	@brief	is_implicitly_copy_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief		型Tが暗黙にコピー構築可能か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_implicitly_copy_constructible は、型Tが暗黙にコピー構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_implicitly_copy_constructible
	: public hamon::is_implicitly_constructible<
		T,
		typename std::add_lvalue_reference<
			typename std::add_const<T>::type
		>::type
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_implicitly_copy_constructible_v = is_implicitly_copy_constructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_HPP
