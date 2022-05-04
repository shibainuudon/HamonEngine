/**
 *	@file	alignof.hpp
 *
 *	@brief	HAMON_ALIGNOF の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_ALIGNOF_HPP
#define HAMON_CONFIG_SUFFIX_ALIGNOF_HPP

//
//	alignof workaround
//
#if !defined(HAMON_ALIGNOF)
#	if defined(HAMON_HAS_CXX11_ALIGNOF)
#		define HAMON_ALIGNOF(type) alignof(type)
#	elif defined(_MSC_VER)
#		define HAMON_ALIGNOF(type) __alignof(type)
#	elif defined(__GNUC__)
#		define HAMON_ALIGNOF(type) __alignof__(type)
#	else
#		define HAMON_ALIGNOF(type)
#		define HAMON_NO_ALIGNOF
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_ALIGNOF_HPP
