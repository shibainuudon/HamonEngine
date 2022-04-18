/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode
 */

#ifndef HAMON_RENDER_GL_FILL_MODE_HPP
#define HAMON_RENDER_GL_FILL_MODE_HPP

#include <hamon/render/fill_mode.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum FillMode(render::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case render::FillMode::Solid:		return GL_FILL;
	case render::FillMode::Wireframe:	return GL_LINE;
	}
	return GL_FILL;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_FILL_MODE_HPP
