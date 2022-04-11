/**
 *	@file	com_ptr.hpp
 *
 *	@brief	
 */

#ifndef HAMON_RENDER_D3D_COM_PTR_HPP
#define HAMON_RENDER_D3D_COM_PTR_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <wrl/client.h>

namespace hamon
{

inline namespace render
{

using Microsoft::WRL::ComPtr;

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D_COM_PTR_HPP
