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
	}

	void EndRenderPass(void) override
	{
	}

private:
	template <typename T, typename Map, typename Id, typename... Args>
	typename Map::mapped_type
	GetOrCreate(Map& map, Id const& id, Args&&... args)
	{
		auto it = map.find(id);
		if (it != map.end())
		{
			return it->second;
		}
		else
		{
			auto p = std::make_shared<T>(std::forward<Args>(args)...);
			map[id] = p;
			return p;
		}
	}

public:
	void Render(
		Geometry const& geometry,
		Program const& program,
		RenderState const& render_state) override
	{
		gl::RasterizerState::Apply(render_state.rasterizer_state);
		gl::BlendState::Apply(render_state.blend_state);
		gl::DepthStencilState::Apply(render_state.depth_stencil_state);

		auto gl_geometry = GetOrCreate<gl::Geometry>(
			m_geometry_map, geometry.GetID(), geometry);
		auto gl_program = GetOrCreate<gl::Program>(
			m_program_map, program.GetID(), program);

		gl_program->Use();
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
	std::unordered_map<detail::Identifier, std::shared_ptr<gl::Program>>	m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<gl::Geometry>>	m_geometry_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_GL_RENDERER_HPP
