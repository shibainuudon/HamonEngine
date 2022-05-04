/**
 *	@file	rs6k.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_RS6000 を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_RS6K_HPP
#define HAMON_CONFIG_ARCHITECTURE_RS6K_HPP

#if defined(__THW_RS6000) || defined(_IBMR2)    || \
    defined(_POWER)       || defined(_ARCH_PWR) || \
    defined(_ARCH_PWR2)
#  define HAMON_ARCHITECTURE "rs6000"
#  define HAMON_ARCHITECTURE_RS6000
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_RS6K_HPP
