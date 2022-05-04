/**
 *	@file	config.hpp
 *
 *	@brief	Config library
 */

#ifndef HAMON_CONFIG_HPP
#define HAMON_CONFIG_HPP

#include <hamon/config/prefix.hpp>

#if !defined(HAMON_USER_CONFIG) && !defined(HAMON_NO_USER_CONFIG)
#	define HAMON_USER_CONFIG <hamon/config/user.hpp>
#endif
#if defined(HAMON_USER_CONFIG)
#	include HAMON_USER_CONFIG
#endif

#if !defined(HAMON_COMPILER_CONFIG) && !defined(HAMON_NO_COMPILER_CONFIG) && !defined(HAMON_NO_CONFIG)
#	include <hamon/config/select_compiler_config.hpp>
#endif
#if defined(HAMON_COMPILER_CONFIG)
#	include HAMON_COMPILER_CONFIG
#endif

#if !defined(HAMON_STDLIB_CONFIG) && !defined(HAMON_NO_STDLIB_CONFIG) && !defined(HAMON_NO_CONFIG) && defined(__cplusplus)
#	include <hamon/config/select_stdlib_config.hpp>
#endif
#if defined(HAMON_STDLIB_CONFIG)
#	include HAMON_STDLIB_CONFIG
#endif

#if !defined(HAMON_PLATFORM_CONFIG) && !defined(HAMON_NO_PLATFORM_CONFIG) && !defined(HAMON_NO_CONFIG)
#	include <hamon/config/select_platform_config.hpp>
#endif
#if defined(HAMON_PLATFORM_CONFIG)
#	include HAMON_PLATFORM_CONFIG
#endif

#include <hamon/config/architecture.hpp>
#include <hamon/config/suffix.hpp>

#endif // HAMON_CONFIG_HPP
