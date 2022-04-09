/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode
 */

#ifndef HAMON_RENDER_OPENGL_CULL_MODE_HPP
#define HAMON_RENDER_OPENGL_CULL_MODE_HPP

#include <hamon/render/cull_mode.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum CullMode(render::CullMode cull_mode)
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

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_CULL_MODE_HPP
