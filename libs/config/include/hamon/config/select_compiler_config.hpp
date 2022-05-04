/**
 *	@file	select_compiler_config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SELECT_COMPILER_CONFIG_HPP
#define HAMON_CONFIG_SELECT_COMPILER_CONFIG_HPP

#if defined(__clang__) && !defined(__CUDACC__) && !defined(__ibmxl__)
// when using clang and cuda at same time, you want to appear as gcc
//  Clang C++ emulates GCC, so it has to appear early.

#  if defined(__APPLE__)
#    define HAMON_COMPILER_CONFIG	"hamon/config/compiler/apple_clang.hpp"
#  else
#    define HAMON_COMPILER_CONFIG	"hamon/config/compiler/clang.hpp"
#  endif

#elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#   define HAMON_COMPILER_CONFIG	"hamon/config/compiler/gcc.hpp"

#elif defined(_MSC_VER)
//  Microsoft Visual C++
#   define HAMON_COMPILER_CONFIG	"hamon/config/compiler/msvc.hpp"

#else
#	error "Unknown compiler"

#endif

#endif // HAMON_CONFIG_SELECT_COMPILER_CONFIG_HPP
