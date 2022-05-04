/**
 *	@file	sys390.hpp
 *
 *	@brief	HAMON_ARCHITECTURE_SYS390 を定義
 */

#ifndef HAMON_CONFIG_ARCHITECTURE_SYS390_HPP
#define HAMON_CONFIG_ARCHITECTURE_SYS390_HPP

#if defined(__s390__) || defined(__s390x__)
#  define HAMON_ARCHITECTURE "sys390"
#  define HAMON_ARCHITECTURE_SYS390
#endif

#endif // HAMON_CONFIG_ARCHITECTURE_SYS390_HPP
