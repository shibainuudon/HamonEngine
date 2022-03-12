/**
 *	@file	opengl_renderer.hpp
 *
 *	@brief	OpenGLRenderer
 */

#ifndef HAMON_RENDER_OPENGL_OPENGL_RENDERER_HPP
#define HAMON_RENDER_OPENGL_OPENGL_RENDERER_HPP

#include <hamon/render/opengl/context.hpp>
#include <hamon/render/opengl/glext.hpp>
#include <hamon/render/opengl/gl.hpp>
#include <hamon/render/renderer.hpp>
#include <memory>
#include <cstdio>

namespace hamon
{

class Window;

inline namespace render
{

class OpenGLRenderer : public Renderer
{
public:
	explicit OpenGLRenderer(Window const& window)
		: m_context(new gl::Context(window))
	{
		gl::glDebugMessageCallback(DebugCallback, nullptr);
		::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

	~OpenGLRenderer()
	{
	}

	void Begin(void) override
	{
	}

	void End(void) override
	{
		m_context->SwapBuffers();
	}

	void BeginRenderPass(ClearValue const& clear_value) override
	{
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		::glDepthMask(GL_TRUE);
		::glStencilMask(~0u);
		::glClearColor(
			clear_value.r,
			clear_value.g,
			clear_value.b,
			clear_value.a);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void EndRenderPass(void) override
	{
	}

private:
	static void APIENTRY DebugCallback(
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

private:
	std::unique_ptr<gl::Context>	m_context;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_OPENGL_RENDERER_HPP
