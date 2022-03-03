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

inline void APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam)
{
	static auto func = (PFNGLDEBUGMESSAGECALLBACKPROC)::wglGetProcAddress("glDebugMessageCallback");
	return func(callback, userParam);
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_GLEXT_HPP
