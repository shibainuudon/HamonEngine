/**
 *	@file	gl_renderer.hpp
 *
 *	@brief	GLRenderer
 */

#ifndef HAMON_RENDER_GL_GL_RENDERER_HPP
#define HAMON_RENDER_GL_GL_RENDERER_HPP

#include <hamon/render/gl/context.hpp>
#include <hamon/render/gl/glext.hpp>
#include <hamon/render/gl/gl.hpp>
#include <hamon/render/gl/geometry.hpp>
#include <hamon/render/gl/program.hpp>
#include <hamon/render/gl/rasterizer_state.hpp>
#include <hamon/render/gl/blend_state.hpp>
#include <hamon/render/gl/depth_stencil_state.hpp>
#include <hamon/render/gl/clear_value.hpp>
#include <hamon/render/gl/viewport.hpp>
#include <hamon/render/gl/scissor_state.hpp>
#include <hamon/render/gl/sampler.hpp>
#include <hamon/render/gl/resource_map.hpp>
#include <hamon/render/renderer.hpp>
#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/clear_value.hpp>
#include <hamon/render/viewport.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/render_pass_state.hpp>
#include <memory>
#include <cstdio>

namespace hamon
{

class Window;

inline namespace render
{

class GLRenderer : public Renderer
{
public:
	explicit GLRenderer(Window const& window)
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

	~GLRenderer()
	{
	}

	void Begin(void) override
	{
	}

	void End(void) override
	{
		m_context->SwapBuffers();
	}

	void BeginRenderPass(RenderPassState const& render_pass_state) override
	{
		gl::ClearValue::Apply(render_pass_state.clear_value);
		gl::Viewport::Apply(render_pass_state.viewport);
		gl::ScissorState::Apply(render_pass_state.scissor);
	}

	void EndRenderPass(void) override
	{
	}

public:
	void Render(
		Geometry const& geometry,
		Program const& program,
		Uniforms const& uniforms,
		RenderState const& render_state) override
	{
		gl::RasterizerState::Apply(render_state.rasterizer_state);
		gl::BlendState::Apply(render_state.blend_state);
		gl::DepthStencilState::Apply(render_state.depth_stencil_state);

		auto gl_geometry = m_resource_map.GetGeometry(geometry);
		auto gl_program = m_resource_map.GetProgram(program);

		gl_program->Use();
		gl_program->LoadUniforms(uniforms, &m_resource_map);
		gl_geometry->Draw();
		gl_program->Unuse();
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
	gl::ResourceMap					m_resource_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_GL_RENDERER_HPP
