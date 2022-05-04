/**
 *	@file	likely.hpp
 *
 *	@brief	HAMON_LIKELY の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_LIKELY_HPP
#define HAMON_CONFIG_SUFFIX_LIKELY_HPP

//
//	分岐予測ヒント
//
#if !defined(HAMON_LIKELY)
#  if HAMON_HAS_BUILTIN(__builtin_expect)
#    define HAMON_LIKELY(x) __builtin_expect(x, 1)
#  else
#    define HAMON_LIKELY(x) x
#  endif
#endif

#if !defined(HAMON_UNLIKELY)
#  if HAMON_HAS_BUILTIN(__builtin_expect)
#    define HAMON_UNLIKELY(x) __builtin_expect(x, 0)
#  else
#    define HAMON_UNLIKELY(x) x
#  endif
#endif

#endif // HAMON_CONFIG_SUFFIX_LIKELY_HPP
