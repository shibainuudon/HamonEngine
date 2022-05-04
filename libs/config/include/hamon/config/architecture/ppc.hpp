/**
 *	@file	ppc.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_PPC を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_PPC_HPP
#define HAMON_CONFIG_ARCHITECTURE_PPC_HPP

#if defined(__powerpc)    || defined(__powerpc__)     || \
    defined(__POWERPC__)  || defined(__ppc__)         || \
    defined(_M_PPC)       || defined(_ARCH_PPC)       || \
    defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
    defined(_XENON)
#  define HAMON_ARCHITECTURE "ppc"
#  define HAMON_ARCHITECTURE_PPC
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_PPC_HPP
