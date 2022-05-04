/**
 *	@file	nodiscard.hpp
 *
 *	@brief	HAMON_NODISCARD の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_NODISCARD_HPP
#define HAMON_CONFIG_SUFFIX_NODISCARD_HPP

//
//	[[nodiscard]] workaround
//
#if !defined(HAMON_NODISCARD)
#	if HAMON_HAS_CPP_ATTRIBUTE(nodiscard)
#		define HAMON_NODISCARD [[nodiscard]]
#	else
#		define HAMON_NODISCARD
#		define HAMON_NO_NODISCARD
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_NODISCARD_HPP
