/**
 *	@file	context.hpp
 *
 *	@brief	Context
 */

#ifndef HAMON_RENDER_OPENGL_CONTEXT_HPP
#define HAMON_RENDER_OPENGL_CONTEXT_HPP

#if defined(_WIN32)
#include <hamon/render/opengl/wgl/context.hpp>
#elif defined(__linux)
#include <hamon/render/opengl/x11/context.hpp>
#endif

#endif // HAMON_RENDER_OPENGL_CONTEXT_HPP
