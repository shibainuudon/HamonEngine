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
#include <hamon/render/opengl/rasterizer_state.hpp>
#include <hamon/render/opengl/blend_state.hpp>
#include <hamon/render/opengl/depth_stencil_state.hpp>
#include <hamon/render/opengl/clear_value.hpp>
#include <hamon/render/opengl/viewport.hpp>
#include <hamon/render/renderer.hpp>
#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/clear_value.hpp>
#include <hamon/render/viewport.hpp>
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
		gl::ClearValue::Apply(clear_value);
		gl::Viewport::Apply(viewport);
	}

	void EndRenderPass(void) override
	{
	}

	void Render(
		Geometry const& geometry,
		Program const& program,
		RasterizerState const& rasterizer_state,
		BlendState const& blend_state,
		DepthStencilState const& depth_stencil_state) override
	{
		gl::RasterizerState::Apply(rasterizer_state);
		gl::BlendState::Apply(blend_state);
		gl::DepthStencilState::Apply(depth_stencil_state);

		gl::Program gl_program(program);
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
