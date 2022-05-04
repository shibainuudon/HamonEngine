/**
 *	@file	inline_var.hpp
 *
 *	@brief	HAMON_INLINE_VAR の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_INLINE_VAR_HPP
#define HAMON_CONFIG_SUFFIX_INLINE_VAR_HPP

//
//	inline variables workaround
//
#if !defined(HAMON_INLINE_VAR)
#	if defined(HAMON_HAS_CXX17_INLINE_VARIABLES)
#		define HAMON_INLINE_VAR inline
#	else
#		define HAMON_INLINE_VAR
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_INLINE_VAR_HPP
