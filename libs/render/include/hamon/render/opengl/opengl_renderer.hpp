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
#include <hamon/render/opengl/geometry.hpp>
#include <hamon/render/opengl/program.hpp>
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
		// NOTIFICATION レベルの報告を無効化
		gl::glDebugMessageControl(
			GL_DONT_CARE,
			GL_DONT_CARE,
			GL_DEBUG_SEVERITY_NOTIFICATION,
			0,
			nullptr,
			GL_FALSE);
		// コールバック関数を指定
		gl::glDebugMessageCallback(DebugCallback, nullptr);
		// DebugOutputを有効化
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

	void BeginRenderPass(ClearValue const& clear_value, Viewport const& viewport) override
	{
		// Clear
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		::glDepthMask(GL_TRUE);
		::glStencilMask(~0u);
		::glClearColor(
			clear_value.r,
			clear_value.g,
			clear_value.b,
			clear_value.a);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Setup Viewport
		::glViewport(
			static_cast<::GLint>(viewport.left),
			static_cast<::GLint>(viewport.top),
			static_cast<::GLsizei>(viewport.width),
			static_cast<::GLsizei>(viewport.height));
		gl::glDepthRangef(
			viewport.min_depth,
			viewport.max_depth);
	}

	void EndRenderPass(void) override
	{
	}

	void Render(Geometry const& geometry, std::vector<Shader> const& shaders) override
	{
		gl::Program gl_program(shaders);
		gl::Geometry gl_geometry(geometry);

		gl_program.Use();
		gl_geometry.Draw();
		gl_program.Unuse();
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
