/**
 *	@file	select_platform_config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SELECT_PLATFORM_CONFIG_HPP
#define HAMON_CONFIG_SELECT_PLATFORM_CONFIG_HPP

#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
// linux
#  define HAMON_PLATFORM_CONFIG "hamon/config/platform/linux.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define HAMON_PLATFORM_CONFIG	"hamon/config/platform/win32.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define HAMON_PLATFORM_CONFIG "hamon/config/platform/macos.hpp"

#else
#  error "Unknown platform"

#endif

#endif // HAMON_CONFIG_SELECT_PLATFORM_CONFIG_HPP
