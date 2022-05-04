/**
 *	@file	parisc.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_PARISC を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_PARISC_HPP
#define HAMON_CONFIG_ARCHITECTURE_PARISC_HPP

#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#  define HAMON_ARCHITECTURE "parisc"
#  define HAMON_ARCHITECTURE_PARISC
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_PARISC_HPP
