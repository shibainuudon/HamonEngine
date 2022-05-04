/**
 *	@file	m68k.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_M68K を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_M68K_HPP
#define HAMON_CONFIG_ARCHITECTURE_M68K_HPP

#if defined(__m68k__) || defined(M68000)
#  define HAMON_ARCHITECTURE "m68k"
#  define HAMON_ARCHITECTURE_M68K
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_M68K_HPP
