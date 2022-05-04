/**
 *	@file	deprecated.hpp
 *
 *	@brief	HAMON_DEPRECATED の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_DEPRECATED_HPP
#define HAMON_CONFIG_SUFFIX_DEPRECATED_HPP

//
//	[[deprecated]] workaround
//
#if !defined(HAMON_DEPRECATED)
#	if defined(HAMON_HAS_CXX14_DEPRECATED)
#		define HAMON_DEPRECATED(message) [[deprecated(message)]]
#	elif defined(_MSC_VER)
#		define HAMON_DEPRECATED(message) __declspec(deprecated(message))
#	elif defined(__GNUC__)
#		define HAMON_DEPRECATED(message) __attribute__((deprecated(message)))
#	else
#		define HAMON_DEPRECATED(message)
#		define HAMON_NO_DEPRECATED
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_DEPRECATED_HPP
