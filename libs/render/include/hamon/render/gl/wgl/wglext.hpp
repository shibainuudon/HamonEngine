/**
 *	@file	wglext.hpp
 *
 *	@brief	wglext
 */

#ifndef HAMON_RENDER_GL_WGLEXT_HPP
#define HAMON_RENDER_GL_WGLEXT_HPP

#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline HGLRC WINAPI wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList)
{
	static auto func = (PFNWGLCREATECONTEXTATTRIBSARBPROC)::wglGetProcAddress("wglCreateContextAttribsARB");
	return func(hDC, hShareContext, attribList);
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_WGLEXT_HPP
