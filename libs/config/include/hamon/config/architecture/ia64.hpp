/**
 *	@file	ia64.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_IA64 を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_IA64_HPP
#define HAMON_CONFIG_ARCHITECTURE_IA64_HPP

#if defined(__ia64__) || defined(_IA64)  || \
    defined(__IA64__) || defined(__ia64) || \
    defined(_M_IA64)  || defined(__itanium__)
#  define HAMON_ARCHITECTURE "ia64"
#  define HAMON_ARCHITECTURE_IA64
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_IA64_HPP
