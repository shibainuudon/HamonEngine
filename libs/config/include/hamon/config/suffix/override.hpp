/**
 *	@file	override.hpp
 *
 *	@brief	HAMON_OVERRIDE の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_OVERRIDE_HPP
#define HAMON_CONFIG_SUFFIX_OVERRIDE_HPP

//
//	override workaround
//
#if !defined(HAMON_OVERRIDE)
#	if defined(HAMON_HAS_CXX11_OVERRIDE)
#		define HAMON_OVERRIDE override
#	else
#		define HAMON_OVERRIDE
#		define HAMON_NO_OVERRIDE
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_OVERRIDE_HPP
