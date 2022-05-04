/**
 *	@file	blackfin.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_BLACKFIN を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_BLACKFIN_HPP
#define HAMON_CONFIG_ARCHITECTURE_BLACKFIN_HPP

#if defined(__bfin__) || defined(__BFIN__) || \
    defined(bfin)     || defined(BFIN)
#  define HAMON_ARCHITECTURE "blackfin"
#  define HAMON_ARCHITECTURE_BLACKFIN
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_BLACKFIN_HPP
