/**
 *	@file	carries_dependency.hpp
 *
 *	@brief	HAMON_CARRIES_DEPENDENCY の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP
#define HAMON_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP

//
//	[[carries_dependency]] workaround
//
#if !defined(HAMON_CARRIES_DEPENDENCY)
#	if defined(HAMON_HAS_CXX11_CARRIES_DEPENDENCY)
#		define HAMON_CARRIES_DEPENDENCY [[carries_dependency]]
#	else
#		define HAMON_CARRIES_DEPENDENCY
#		define HAMON_NO_CARRIES_DEPENDENCY
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP
