/**
 *	@file	pragma.hpp
 *
 *	@brief	HAMON_PRAGMA の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_PRAGMA_HPP
#define HAMON_CONFIG_SUFFIX_PRAGMA_HPP

//
//	Pragma演算子
//
#if !defined(HAMON_PRAGMA)
#	if defined(HAMON_HAS_CXX11_PRAGMA_OPERATOR)
#	  define HAMON_PRAGMA(x)		_Pragma(#x)
#	else
#	  define HAMON_PRAGMA(x)		__pragma(x)
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_PRAGMA_HPP
