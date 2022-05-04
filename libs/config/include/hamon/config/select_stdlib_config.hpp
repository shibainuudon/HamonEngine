/**
 *	@file	select_stdlib_config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SELECT_STDLIB_CONFIG_HPP
#define HAMON_CONFIG_SELECT_STDLIB_CONFIG_HPP

#ifdef __cplusplus
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(_LIBCPP_VERSION)
// libc++
#  define HAMON_STDLIB_CONFIG	"hamon/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define HAMON_STDLIB_CONFIG	"hamon/config/stdlib/libstdcpp3.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library
#  define HAMON_STDLIB_CONFIG	"hamon/config/stdlib/dinkumware.hpp"

#else
#  error "Unknown standard library"

#endif

#endif // HAMON_CONFIG_SELECT_STDLIB_CONFIG_HPP
