/**
 *	@file	gl.hpp
 *
 *	@brief	OpenGL関係のヘッダをインクルードする
 */

#ifndef HAMON_RENDER_OPENGL_GL_HPP
#define HAMON_RENDER_OPENGL_GL_HPP

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include <GL/glext.h>

#if defined(_WIN32)
#define WGL_WGLEXT_PROTOTYPES
#include <GL/wglext.h>
#endif
#if defined(__linux)
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glx.h>
#include <GL/glxext.h>
#endif

#endif // HAMON_RENDER_OPENGL_GL_HPP
