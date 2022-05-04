/**
 *	@file	alpha.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_ALPHA を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_ALPHA_HPP
#define HAMON_CONFIG_ARCHITECTURE_ALPHA_HPP

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#  define HAMON_ARCHITECTURE "alpha"
#  define HAMON_ARCHITECTURE_ALPHA
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_ALPHA_HPP
