/**
 *	@file	glext.hpp
 *
 *	@brief	glext
 */

#ifndef HAMON_RENDER_OPENGL_GLEXT_HPP
#define HAMON_RENDER_OPENGL_GLEXT_HPP

#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

#if defined(_WIN32)
#define GET_PROC_ADDRESS(name)	wglGetProcAddress((LPCSTR)name)
#elif defined(__linux)
#define GET_PROC_ADDRESS(name)	(*glXGetProcAddressARB)((const GLubyte*)name)
#endif

inline void APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam)
{
	static auto func = (PFNGLDEBUGMESSAGECALLBACKPROC)GET_PROC_ADDRESS("glDebugMessageCallback");
	return func(callback, userParam);
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_GLEXT_HPP
