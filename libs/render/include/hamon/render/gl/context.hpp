/**
 *	@file	context.hpp
 *
 *	@brief	Context
 */

#ifndef HAMON_RENDER_GL_CONTEXT_HPP
#define HAMON_RENDER_GL_CONTEXT_HPP

#if defined(_WIN32)
#include <hamon/render/gl/wgl/context.hpp>
#elif defined(__linux)
#include <hamon/render/gl/x11/context.hpp>
#endif

#endif // HAMON_RENDER_GL_CONTEXT_HPP
