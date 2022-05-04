/**
 *	@file	arm.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_ARM を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_ARM_HPP
#define HAMON_CONFIG_ARCHITECTURE_ARM_HPP

#if defined(__arm__) || defined(__arm64)  || defined(__thumb__) || \
    defined(_M_ARM)  || defined(_M_ARM64) || \
    defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB)
#  define HAMON_ARCHITECTURE "arm"
#  define HAMON_ARCHITECTURE_ARM
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_ARM_HPP
