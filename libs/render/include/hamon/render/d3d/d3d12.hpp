/**
 *	@file	d3d12.hpp
 *
 *	@brief	
 */

#ifndef HAMON_RENDER_D3D_D3D12_HPP
#define HAMON_RENDER_D3D_D3D12_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3d12.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "d3d12.lib")
#endif

#endif // HAMON_RENDER_D3D_D3D12_HPP
