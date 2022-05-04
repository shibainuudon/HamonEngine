/**
 *	@file	prefix.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_PREFIX_HPP
#define HAMON_CONFIG_PREFIX_HPP

//
// HAMON_HAS_FEATURE
//
#if defined(__has_feature)
#	define HAMON_HAS_FEATURE(x)		(__has_feature(x))
#else
#	define HAMON_HAS_FEATURE(x)		(0)
#endif

//
// HAMON_HAS_EXTENSION
//
#if defined(__has_extension)
#	define HAMON_HAS_EXTENSION(x)	(__has_extension(x))
#else
#	define HAMON_HAS_EXTENSION(x)	HAMON_HAS_FEATURE(x)
#endif

//
// HAMON_HAS_ATTRIBUTE
//
#if defined(__has_attribute)
#	define HAMON_HAS_ATTRIBUTE(x)	(__has_attribute(x))
#else
#	define HAMON_HAS_ATTRIBUTE(x)	(0)
#endif

//
// HAMON_HAS_CPP_ATTRIBUTE
//
#if defined(__has_cpp_attribute)
#	define HAMON_HAS_CPP_ATTRIBUTE(x)	(__has_cpp_attribute(x))
#else
#	define HAMON_HAS_CPP_ATTRIBUTE(x)	(0)
#endif

//
// HAMON_HAS_BUILTIN
//
#if defined(__has_builtin)
#	define HAMON_HAS_BUILTIN(x)		(__has_builtin(x))
#else
#	define HAMON_HAS_BUILTIN(x)		(0)
#endif

//
// HAMON_HAS_WARNING
//
#if defined(__has_warning)
#	define HAMON_HAS_WARNING(x)		(__has_warning(x))
#else
#	define HAMON_HAS_WARNING(x)		(0)
#endif

//
// HAMON_HAS_INCLUDE
//
#if defined(__has_include)
#	define HAMON_HAS_INCLUDE(x)		(__has_include(x))
#else
#	define HAMON_HAS_INCLUDE(x)		(0)
#endif

//
// HAMON_HAS_KEYWORD
//
#if defined(__is_identifier)
#	define HAMON_HAS_KEYWORD(x)		(!__is_identifier(x))
#else
#	define HAMON_HAS_KEYWORD(x)		(0)
#endif

#endif // HAMON_CONFIG_PREFIX_HPP
