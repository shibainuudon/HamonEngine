/**
 *	@file	suffix.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_SUFFIX_HPP
#define HAMON_CONFIG_SUFFIX_HPP

#include <hamon/config/suffix/alignas.hpp>
#include <hamon/config/suffix/alignof.hpp>
#include <hamon/config/suffix/carries_dependency.hpp>
#include <hamon/config/suffix/constexpr.hpp>
#include <hamon/config/suffix/current_function.hpp>
#include <hamon/config/suffix/deprecated.hpp>
#include <hamon/config/suffix/endian.hpp>
#include <hamon/config/suffix/extern_template.hpp>
#include <hamon/config/suffix/fallthrough.hpp>
#include <hamon/config/suffix/final.hpp>
#include <hamon/config/suffix/inline_var.hpp>
#include <hamon/config/suffix/likely.hpp>
#include <hamon/config/suffix/no_unique_address.hpp>
#include <hamon/config/suffix/nodiscard.hpp>
#include <hamon/config/suffix/noexcept.hpp>
#include <hamon/config/suffix/noreturn.hpp>
#include <hamon/config/suffix/override.hpp>
#include <hamon/config/suffix/pragma.hpp>
#include <hamon/config/suffix/unreachable.hpp>
#include <hamon/config/suffix/warning.hpp>

//#define HAMON_HEADER_ONLY

#if defined(HAMON_HEADER_ONLY)
#  define HAMON_INLINE	inline
#else
#  define HAMON_INLINE
#endif

#endif // HAMON_CONFIG_SUFFIX_HPP
