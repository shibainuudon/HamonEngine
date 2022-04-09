/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP
#define HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/opengl/glext.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class RasterizerState
{
public:
	static void Apply(render::RasterizerState const& state)
	{
		if (state.cull_mode != render::CullMode::None)
		{
			::glEnable(GL_CULL_FACE);
			::glCullFace(ToGlCullMode(state.cull_mode));
		}
		else
		{
			::glDisable(GL_CULL_FACE);
		}

		::glFrontFace(ToGlFrontFace(state.front_face));

		::glPolygonMode(GL_FRONT_AND_BACK, ToGlFillMode(state.fill_mode));
	}

private:
	static ::GLenum ToGlCullMode(render::CullMode cull_mode)
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

	static ::GLenum ToGlFrontFace(render::FrontFace front_face)
	{
		switch (front_face)
		{
		case render::FrontFace::CW:  return GL_CW;
		case render::FrontFace::CCW: return GL_CCW;
		}
		return GL_CW;
	}

	static ::GLenum ToGlFillMode(render::FillMode fill_mode)
	{
		switch (fill_mode)
		{
		case render::FillMode::Solid:		return GL_FILL;
		case render::FillMode::Wireframe:	return GL_LINE;
		}
		return GL_FILL;
	}
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_RASTERIZER_STATE_HPP
