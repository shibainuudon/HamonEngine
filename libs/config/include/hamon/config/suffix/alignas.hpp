/**
 *	@file	alignas.hpp
 *
 *	@brief	HAMON_ALIGNAS の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_ALIGNAS_HPP
#define HAMON_CONFIG_SUFFIX_ALIGNAS_HPP

//
//	alignas workaround
//
#if !defined(HAMON_ALIGNAS)
#  if defined(HAMON_HAS_CXX11_ALIGNAS)
#    define HAMON_ALIGNAS(x)      alignas(x)
#    define HAMON_ALIGNAS_TYPE(x) alignas(x)
#  elif defined(_MSC_VER)
#    define HAMON_ALIGNAS(x)      __declspec(align(x))
#    define HAMON_ALIGNAS_TYPE(x) __declspec(align(__alignof(x)))
#  elif defined(__GNUC__)
#    define HAMON_ALIGNAS(x)      __attribute__((__aligned__(x)))
#    define HAMON_ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof__(x))))
#  else
#    define HAMON_ALIGNAS(x)
#    define HAMON_ALIGNAS_TYPE(x)
#    define HAMON_NO_ALIGNAS
#  endif
#endif

#endif // HAMON_CONFIG_SUFFIX_ALIGNAS_HPP
