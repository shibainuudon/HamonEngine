/**
 *	@file	d3d11.hpp
 *
 *	@brief	
 */

#ifndef HAMON_RENDER_D3D_D3D11_HPP
#define HAMON_RENDER_D3D_D3D11_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3d11_4.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "d3d11.lib")
#endif

#endif // HAMON_RENDER_D3D_D3D11_HPP
