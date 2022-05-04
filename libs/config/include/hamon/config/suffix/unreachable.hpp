/**
 *	@file	unreachable.hpp
 *
 *	@brief	HAMON_UNREACHABLE の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_UNREACHABLE_HPP
#define HAMON_CONFIG_SUFFIX_UNREACHABLE_HPP

//
//	unreachable workaround
//
#if !defined(HAMON_UNREACHABLE)
#  ifdef __GNUC__
#    define HAMON_UNREACHABLE() __builtin_unreachable()
#  else
#    define HAMON_UNREACHABLE()
#  endif
#endif

#endif // HAMON_CONFIG_SUFFIX_UNREACHABLE_HPP
