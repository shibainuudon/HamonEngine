/**
 *	@file	window.hpp
 *
 *	@brief	Window library
 */

#ifndef HAMON_WINDOW_WINDOW_HPP
#define HAMON_WINDOW_WINDOW_HPP

#if defined(_WIN32)
#include <hamon/window/win32/win32_window.hpp>
//#elif defined(HAMON_PLATFORM_LINUX)
#else
#include <hamon/window/x11/x11_window.hpp>
#endif

#endif // HAMON_WINDOW_WINDOW_HPP
