/**
 *	@file	extern_template.hpp
 *
 *	@brief	HAMON_EXTERN_TEMPLATE の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP
#define HAMON_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP

#if !defined(HAMON_EXTERN_TEMPLATE)
#	if defined(HAMON_HAS_CXX11_EXTERN_TEMPLATE)
#		define HAMON_EXTERN_TEMPLATE(...) extern template __VA_ARGS__
#	else
#		define HAMON_EXTERN_TEMPLATE(...)
#		define HAMON_NO_EXTERN_TEMPLATE
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP
