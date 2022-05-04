/**
 *	@file	x86.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_X86 を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_X86_HPP
#define HAMON_CONFIG_ARCHITECTURE_X86_HPP

#if defined(i386)      || defined(__i386__) || \
    defined(__i486__)  || defined(__i586__) || \
    defined(__i686__)  || defined(__i386)   || \
    defined(_M_IX86)   || defined(_X86_)    || \
    defined(__INTEL__) || defined(__I86__)  || \
    defined(__THW_INTEL__)
#  define HAMON_ARCHITECTURE "x86_32"
#  define HAMON_ARCHITECTURE_X86_32
#endif

#if defined(__x86_64)  || defined(__x86_64__) || \
    defined(__amd64__) || defined(__amd64)    || \
    defined(_M_X64)
#  define HAMON_ARCHITECTURE "x86_64"
#  define HAMON_ARCHITECTURE_X86_64
#endif

#if defined(HAMON_ARCHITECTURE_X86_32) || defined(HAMON_ARCHITECTURE_X86_64)
#  define HAMON_ARCHITECTURE_X86
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_X86_HPP
