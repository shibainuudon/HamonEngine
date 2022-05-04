/**
 *	@file	fallthrough.hpp
 *
 *	@brief	HAMON_FALLTHROUGH の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_FALLTHROUGH_HPP
#define HAMON_CONFIG_SUFFIX_FALLTHROUGH_HPP

//
//	fallthrough workaround
//
#if !defined(HAMON_FALLTHROUGH)
#	if defined(HAMON_HAS_CXX17_FALLTHROUGH)
#		define HAMON_FALLTHROUGH() [[fallthrough]]
#	elif HAMON_HAS_ATTRIBUTE(fallthrough)
#		define HAMON_FALLTHROUGH() __attribute__((__fallthrough__))
#	else
#		define HAMON_FALLTHROUGH()
#		define HAMON_NO_FALLTHROUGH
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_FALLTHROUGH_HPP
