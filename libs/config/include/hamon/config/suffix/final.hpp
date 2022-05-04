/**
 *	@file	final.hpp
 *
 *	@brief	HAMON_FINAL の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_FINAL_HPP
#define HAMON_CONFIG_SUFFIX_FINAL_HPP

//
//	final workaround
//
#if !defined(HAMON_FINAL)
#	if defined(HAMON_HAS_CXX11_FINAL)
#		define HAMON_FINAL final
#	else
#		define HAMON_FINAL
#		define HAMON_NO_FINAL
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_FINAL_HPP
