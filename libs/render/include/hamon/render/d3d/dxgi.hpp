/**
 *	@file	dxgi.hpp
 *
 *	@brief	
 */

#ifndef HAMON_RENDER_D3D_DXGI_HPP
#define HAMON_RENDER_D3D_DXGI_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <dxgi1_6.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "dxgi.lib")
#endif

#endif // HAMON_RENDER_D3D_DXGI_HPP
