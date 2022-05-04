/**
 *	@file	mips.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_MIPS を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_MIPS_HPP
#define HAMON_CONFIG_ARCHITECTURE_MIPS_HPP

#if defined(__mips__) || defined(__mips) || \
    defined(__MIPS__)
#  define HAMON_ARCHITECTURE "mips"
#  define HAMON_ARCHITECTURE_MIPS
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_MIPS_HPP
