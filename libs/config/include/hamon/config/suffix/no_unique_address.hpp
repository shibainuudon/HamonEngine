/**
 *	@file	no_unique_address.hpp
 *
 *	@brief	HAMON_NO_UNIQUE_ADDRESS の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP
#define HAMON_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP

//
//	[[no_unique_address]] workaround
//
#if !defined(HAMON_NO_UNIQUE_ADDRESS)
#	if defined(HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS)
#		define HAMON_NO_UNIQUE_ADDRESS [[no_unique_address]]
#	else
#		define HAMON_NO_UNIQUE_ADDRESS
#		define HAMON_NO_NO_UNIQUE_ADDRESS
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP
