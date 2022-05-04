/**
 *	@file	warning.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SUFFIX_WARNING_HPP
#define HAMON_CONFIG_SUFFIX_WARNING_HPP

//
//	HAMON_WARNING_PUSH
//
#if !defined(HAMON_WARNING_PUSH)
#	if defined(HAMON_MSVC)
#	  define HAMON_WARNING_PUSH()			HAMON_PRAGMA(warning(push))
#	elif defined(HAMON_CLANG)
#	  define HAMON_WARNING_PUSH()			HAMON_PRAGMA(clang diagnostic push)
#	elif defined(HAMON_GCC)
#	  define HAMON_WARNING_PUSH()			HAMON_PRAGMA(GCC diagnostic push)
#	else
#	  define HAMON_WARNING_PUSH()
#	endif
#endif

//
//	HAMON_WARNING_POP
//
#if !defined(HAMON_WARNING_POP)
#	if defined(HAMON_MSVC)
#	  define HAMON_WARNING_POP()			HAMON_PRAGMA(warning(pop))
#	elif defined(HAMON_CLANG)
#	  define HAMON_WARNING_POP()			HAMON_PRAGMA(clang diagnostic pop)
#	elif defined(HAMON_GCC)
#	  define HAMON_WARNING_POP()			HAMON_PRAGMA(GCC diagnostic pop)
#	else
#	  define HAMON_WARNING_POP()
#	endif
#endif

//
//	警告抑制マクロ
//
#if !defined(HAMON_WARNING_DISABLE_MSVC)
#	if defined(HAMON_MSVC)
#	  define HAMON_WARNING_DISABLE_MSVC(x)	HAMON_PRAGMA(warning(disable: x))
#	else
#	  define HAMON_WARNING_DISABLE_MSVC(x)
#	endif
#endif

#if !defined(HAMON_WARNING_DISABLE_CLANG)
#	if defined(HAMON_CLANG)
#	  define HAMON_WARNING_DISABLE_CLANG(x)	HAMON_PRAGMA(clang diagnostic ignored x)
#	else
#	  define HAMON_WARNING_DISABLE_CLANG(x)
#	endif
#endif

#if !defined(HAMON_WARNING_DISABLE_GCC)
#	if defined(HAMON_GCC)
#	  define HAMON_WARNING_DISABLE_GCC(x)	HAMON_PRAGMA(GCC diagnostic ignored x)
#	else
#	  define HAMON_WARNING_DISABLE_GCC(x)
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_WARNING_HPP
