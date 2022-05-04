/**
 *	@file	noreturn.hpp
 *
 *	@brief	HAMON_NORETURN の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_NORETURN_HPP
#define HAMON_CONFIG_SUFFIX_NORETURN_HPP

//
//	[[noreturn]] workaround
//
#if !defined(HAMON_NORETURN)
#	if defined(HAMON_HAS_CXX11_NORETURN)
#		define HAMON_NORETURN [[noreturn]]
#	elif defined(_MSC_VER)
#		define HAMON_NORETURN __declspec(noreturn)
#	elif defined(__GNUC__)
#		define HAMON_NORETURN __attribute__ ((__noreturn__))
#	else
#		define HAMON_NORETURN
#		define HAMON_NO_NORETURN
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_NORETURN_HPP
