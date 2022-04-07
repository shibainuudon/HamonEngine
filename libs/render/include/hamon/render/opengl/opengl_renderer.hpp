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

	void Render(
		Geometry const& geometry,
		std::vector<Shader> const& shaders,
		RasterizerState const& rasterizer_state,
		BlendState const& blend_state) override
	{
		// Set Cull Mode
		if (rasterizer_state.cull_mode != render::CullMode::None)
		{
			::glEnable(GL_CULL_FACE);
			::glCullFace(ToGlCullMode(rasterizer_state.cull_mode));
		}
		else
		{
			::glDisable(GL_CULL_FACE);
		}

		::glFrontFace(ToGlFrontFace(rasterizer_state.front_face));

		::glPolygonMode(GL_FRONT_AND_BACK, ToGlFillMode(rasterizer_state.fill_mode));

		// Apply BlendState
		if (blend_state.blend_enable)
		{
			::glEnable(GL_BLEND);
		}
		else
		{
			::glDisable(GL_BLEND);
		}

		gl::glBlendFuncSeparate(
			ToGlBlendFactor(blend_state.color_src_factor),
			ToGlBlendFactor(blend_state.color_dest_factor),
			ToGlBlendFactor(blend_state.alpha_src_factor),
			ToGlBlendFactor(blend_state.alpha_dest_factor));

		gl::glBlendEquationSeparate(
			ToGlBlendOperation(blend_state.color_operation),
			ToGlBlendOperation(blend_state.alpha_operation));

		if (blend_state.logic_op_enable)
		{
			::glEnable(GL_COLOR_LOGIC_OP);
		}
		else
		{
			::glDisable(GL_COLOR_LOGIC_OP);
		}

		::glLogicOp(ToGlLogicOperation(blend_state.logic_operation));

		::glColorMask(
			blend_state.color_write_mask & ColorWriteMask::Red,
			blend_state.color_write_mask & ColorWriteMask::Green,
			blend_state.color_write_mask & ColorWriteMask::Blue,
			blend_state.color_write_mask & ColorWriteMask::Alpha);

		gl::Program gl_program(shaders);
		gl::Geometry gl_geometry(geometry);

		gl_program.Use();
		gl_geometry.Draw();
		gl_program.Unuse();
	}

private:
	static ::GLenum ToGlBlendFactor(render::BlendFactor factor)
	{
		switch (factor)
		{
		case hamon::render::BlendFactor::Zero:			return GL_ZERO;
		case hamon::render::BlendFactor::One:			return GL_ONE;
		case hamon::render::BlendFactor::SrcColor:		return GL_SRC_COLOR;
		case hamon::render::BlendFactor::InvSrcColor:	return GL_ONE_MINUS_SRC_COLOR;
		case hamon::render::BlendFactor::SrcAlpha:		return GL_SRC_ALPHA;
		case hamon::render::BlendFactor::InvSrcAlpha:	return GL_ONE_MINUS_SRC_ALPHA;
		case hamon::render::BlendFactor::DestAlpha:		return GL_DST_ALPHA;
		case hamon::render::BlendFactor::InvDestAlpha:	return GL_ONE_MINUS_DST_ALPHA;
		case hamon::render::BlendFactor::DestColor:		return GL_DST_COLOR;
		case hamon::render::BlendFactor::InvDestColor:	return GL_ONE_MINUS_DST_COLOR;
		case hamon::render::BlendFactor::SrcAlphaSat:	return GL_SRC_ALPHA_SATURATE;
		case hamon::render::BlendFactor::BlendFactor:	return GL_CONSTANT_COLOR;
		case hamon::render::BlendFactor::InvBlendFactor:return GL_ONE_MINUS_CONSTANT_COLOR;
		case hamon::render::BlendFactor::Src1Color:		return GL_SRC1_COLOR;
		case hamon::render::BlendFactor::InvSrc1Color:	return GL_ONE_MINUS_SRC1_COLOR;
		case hamon::render::BlendFactor::Src1Alpha:		return GL_SRC1_ALPHA;
		case hamon::render::BlendFactor::InvSrc1Alpha:	return GL_ONE_MINUS_SRC1_ALPHA;
		}
		return GL_ZERO;
	}

	static ::GLenum ToGlBlendOperation(render::BlendOperation op)
	{
		switch (op)
		{
		case render::BlendOperation::Add:				return GL_FUNC_ADD;
		case render::BlendOperation::Subtract:			return GL_FUNC_SUBTRACT;
		case render::BlendOperation::ReverseSubtract:	return GL_FUNC_REVERSE_SUBTRACT;
		case render::BlendOperation::Min:				return GL_MIN;
		case render::BlendOperation::Max:				return GL_MAX;
		}
		return GL_FUNC_ADD;
	}

	static ::GLenum ToGlLogicOperation(render::LogicOperation op)
	{
		switch (op)
		{
		case render::LogicOperation::Clear:			return GL_CLEAR;
		case render::LogicOperation::Set:			return GL_SET;
		case render::LogicOperation::Copy:			return GL_COPY;
		case render::LogicOperation::CopyInverted:	return GL_COPY_INVERTED;
		case render::LogicOperation::Noop:			return GL_NOOP;
		case render::LogicOperation::Invert:		return GL_INVERT;
		case render::LogicOperation::And:			return GL_AND;
		case render::LogicOperation::Nand:			return GL_NAND;
		case render::LogicOperation::Or:			return GL_OR;
		case render::LogicOperation::Nor:			return GL_NOR;
		case render::LogicOperation::Xor:			return GL_XOR;
		case render::LogicOperation::Equiv:			return GL_EQUIV;
		case render::LogicOperation::AndReverse:	return GL_AND_REVERSE;
		case render::LogicOperation::AndInverted:	return GL_AND_INVERTED;
		case render::LogicOperation::OrReverse:		return GL_OR_REVERSE;
		case render::LogicOperation::OrInverted:	return GL_OR_INVERTED;
		}
		return GL_COPY;
	}

	static GLenum ToGlCullMode(render::CullMode cull_mode)
	{
		switch (cull_mode)
		{
		case render::CullMode::Front:	return GL_FRONT;
		case render::CullMode::Back:	return GL_BACK;
		case render::CullMode::None:
		default:
			// glCullFaceにNONEは設定できないので、適当な値を返す
			// glDisable(GL_CULL_FACE)を呼んでカリングを無効にすること
			return GL_BACK;
		}
	}

	static GLenum ToGlFrontFace(render::FrontFace front_face)
	{
		switch (front_face)
		{
		case render::FrontFace::CW:  return GL_CW;
		case render::FrontFace::CCW: return GL_CCW;
		}
		return GL_CW;
	}

	static GLenum ToGlFillMode(render::FillMode fill_mode)
	{
		switch (fill_mode)
		{
		case render::FillMode::Solid:		return GL_FILL;
		case render::FillMode::Wireframe:	return GL_LINE;
		}
		return GL_FILL;
	}

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
