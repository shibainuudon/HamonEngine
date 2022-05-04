/**
 *	@file	endian.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SUFFIX_ENDIAN_HPP
#define HAMON_CONFIG_SUFFIX_ENDIAN_HPP

#if (defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)) || \
    (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) || \
     defined(__ARMEB__) || \
     defined(__THUMBEB__) || \
     defined(__AARCH64EB__) || \
     defined(_MIPSEB) || \
     defined(__MIPSEB) || \
     defined(__MIPSEB__)
#  define HAMON_BIG_ENDIAN
#endif

#if (defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
    (defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)) || \
     defined(__ARMEL__) || \
     defined(__THUMBEL__) || \
     defined(__AARCH64EL__) || \
     defined(_MIPSEL) || \
     defined(__MIPSEL) || \
     defined(__MIPSEL__)
#  define HAMON_LITTLE_ENDIAN
#endif

#if !defined(HAMON_BIG_ENDIAN) && !defined(HAMON_LITTLE_ENDIAN)
#  include <hamon/config/architecture.hpp>
#  if defined(HAMON_ARCHITECTURE_M68K)   || \
      defined(HAMON_ARCHITECTURE_PARISC) || \
      defined(HAMON_ARCHITECTURE_SPARC)  || \
      defined(HAMON_ARCHITECTURE_SYS370) || \
      defined(HAMON_ARCHITECTURE_SYS390) || \
      defined(HAMON_ARCHITECTURE_Z)
#    define HAMON_BIG_ENDIAN
#  endif
#  if defined(HAMON_ARCHITECTURE_AMD64) || \
      defined(HAMON_ARCHITECTURE_IA64)  || \
      defined(HAMON_ARCHITECTURE_X86)   || \
      defined(HAMON_ARCHITECTURE_BLACKFIN)
#    define HAMON_LITTLE_ENDIAN
#  endif
#endif

#endif // HAMON_CONFIG_SUFFIX_ENDIAN_HPP
