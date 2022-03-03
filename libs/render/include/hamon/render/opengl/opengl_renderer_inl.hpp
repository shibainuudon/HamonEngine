/**
 *	@file	opengl_renderer_inl.hpp
 *
 *	@brief	OpenGLRenderer
 */

#ifndef HAMON_RENDER_OPENGL_OPENGL_RENDERER_INL_HPP
#define HAMON_RENDER_OPENGL_OPENGL_RENDERER_INL_HPP

#include <hamon/render/opengl/context.hpp>
#include <hamon/render/opengl/glext.hpp>
#include <cstdio>

namespace hamon
{

inline namespace render
{

inline
OpenGLRenderer::OpenGLRenderer(Window const& window)
	: m_context(new gl::Context(window))
{
	gl::glDebugMessageCallback(DebugCallback, nullptr);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

inline
OpenGLRenderer::~OpenGLRenderer()
{
}

inline void
OpenGLRenderer::Begin(void)
{
	::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	::glDepthMask(GL_TRUE);
	::glStencilMask(~0u);
	::glClearColor(0.4f, 0.4f, 0.4f, 0);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

inline void
OpenGLRenderer::End(void)
{
	m_context->SwapBuffers();
}

inline void APIENTRY
OpenGLRenderer::DebugCallback(
	::GLenum /*source*/,
	::GLenum /*type*/,
	::GLuint /*id*/,
	::GLenum /*severity*/,
	::GLsizei /*length*/,
	::GLchar const* message,
	void const* /*userParam*/)
{
	std::printf("%s\n", message);
}

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_OPENGL_RENDERER_INL_HPP
