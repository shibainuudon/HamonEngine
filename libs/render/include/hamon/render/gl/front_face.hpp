/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace
 */

#ifndef HAMON_RENDER_GL_FRONT_FACE_HPP
#define HAMON_RENDER_GL_FRONT_FACE_HPP

#include <hamon/render/front_face.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum FrontFace(render::FrontFace front_face)
{
	switch (front_face)
	{
	case render::FrontFace::CW:  return GL_CW;
	case render::FrontFace::CCW: return GL_CCW;
	}
	return GL_CW;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_FRONT_FACE_HPP
