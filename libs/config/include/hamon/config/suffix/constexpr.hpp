/**
 *	@file	constexpr.hpp
 *
 *	@brief	HAMON_CONSTEXPR の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_CONSTEXPR_HPP
#define HAMON_CONFIG_SUFFIX_CONSTEXPR_HPP

//
// constexpr workarounds
//
#if !defined(HAMON_CONSTEXPR)
#  define HAMON_CONSTEXPR				HAMON_CXX11_CONSTEXPR
#endif
#if !defined(HAMON_CONSTEXPR_OR_CONST)
#  define HAMON_CONSTEXPR_OR_CONST		HAMON_CXX11_CONSTEXPR_OR_CONST
#endif

#if !defined(HAMON_CXX11_CONSTEXPR)
#  if defined(HAMON_HAS_CXX11_CONSTEXPR)
#    define HAMON_CXX11_CONSTEXPR constexpr
#  else
#    define HAMON_CXX11_CONSTEXPR
#  endif
#endif

#if !defined(HAMON_CXX11_CONSTEXPR_OR_CONST)
# if defined(HAMON_HAS_CXX11_CONSTEXPR)
#   define HAMON_CXX11_CONSTEXPR_OR_CONST constexpr
# else
#   define HAMON_CXX11_CONSTEXPR_OR_CONST const
# endif
#endif

#if !defined(HAMON_CXX14_CONSTEXPR)
#  if defined(HAMON_HAS_CXX14_CONSTEXPR)
#    define HAMON_CXX14_CONSTEXPR constexpr
#  else
#    define HAMON_CXX14_CONSTEXPR
#  endif
#endif

#if !defined(HAMON_CXX14_CONSTEXPR_OR_CONST)
#  if defined(HAMON_HAS_CXX14_CONSTEXPR)
#    define HAMON_CXX14_CONSTEXPR_OR_CONST constexpr
#  else
#    define HAMON_CXX14_CONSTEXPR_OR_CONST const
#  endif
#endif

#if !defined(HAMON_CXX17_CONSTEXPR)
#  if defined(HAMON_HAS_CXX17_CONSTEXPR)
#    define HAMON_CXX17_CONSTEXPR constexpr
#  else
#    define HAMON_CXX17_CONSTEXPR
#  endif
#endif

#if !defined(HAMON_CXX17_CONSTEXPR_OR_CONST)
#  if defined(HAMON_HAS_CXX17_CONSTEXPR)
#    define HAMON_CXX17_CONSTEXPR_OR_CONST constexpr
#  else
#    define HAMON_CXX17_CONSTEXPR_OR_CONST const
#  endif
#endif

#if !defined(HAMON_CXX20_CONSTEXPR)
#  if defined(HAMON_HAS_CXX20_CONSTEXPR)
#    define HAMON_CXX20_CONSTEXPR constexpr
#  else
#    define HAMON_CXX20_CONSTEXPR
#  endif
#endif

#if !defined(HAMON_CXX20_CONSTEXPR_OR_CONST)
#  if defined(HAMON_HAS_CXX20_CONSTEXPR)
#    define HAMON_CXX20_CONSTEXPR_OR_CONST constexpr
#  else
#    define HAMON_CXX20_CONSTEXPR_OR_CONST const
#  endif
#endif

#if !defined(HAMON_STATIC_CONSTEXPR)
#  define HAMON_STATIC_CONSTEXPR			HAMON_CXX11_STATIC_CONSTEXPR
#endif

#if !defined(HAMON_CXX11_STATIC_CONSTEXPR)
#  define HAMON_CXX11_STATIC_CONSTEXPR		static HAMON_CXX11_CONSTEXPR_OR_CONST
#endif

#if !defined(HAMON_CXX14_STATIC_CONSTEXPR)
#  define HAMON_CXX14_STATIC_CONSTEXPR		static HAMON_CXX14_CONSTEXPR_OR_CONST
#endif

#if !defined(HAMON_CXX17_STATIC_CONSTEXPR)
#  define HAMON_CXX17_STATIC_CONSTEXPR		static HAMON_CXX17_CONSTEXPR_OR_CONST
#endif

#if !defined(HAMON_CXX20_STATIC_CONSTEXPR)
#  define HAMON_CXX20_STATIC_CONSTEXPR		static HAMON_CXX20_CONSTEXPR_OR_CONST
#endif

#endif // HAMON_CONFIG_SUFFIX_CONSTEXPR_HPP
