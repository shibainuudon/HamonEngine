/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode
 */

#ifndef HAMON_RENDER_GL_FILTER_MODE_HPP
#define HAMON_RENDER_GL_FILTER_MODE_HPP

#include <hamon/render/filter_mode.hpp>
#include <hamon/render/mipmap_mode.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum FilterMode(render::FilterMode mag_filter)
{
	switch (mag_filter)
	{
	case render::FilterMode::Nearest:	return GL_NEAREST;
	case render::FilterMode::Linear:	return GL_LINEAR;
	}
	return GL_LINEAR;
}

inline ::GLenum FilterMode(render::FilterMode min_filter, render::MipmapMode mip_filter)
{
	switch (min_filter)
	{
	case render::FilterMode::Nearest:
		switch (mip_filter)
		{
		case render::MipmapMode::Disable:	return GL_NEAREST;
		case render::MipmapMode::Nearest:	return GL_NEAREST_MIPMAP_NEAREST;
		case render::MipmapMode::Linear:	return GL_NEAREST_MIPMAP_LINEAR;
		}
		break;
	case render::FilterMode::Linear:
		switch (mip_filter)
		{
		case render::MipmapMode::Disable:	return GL_LINEAR;
		case render::MipmapMode::Nearest:	return GL_LINEAR_MIPMAP_NEAREST;
		case render::MipmapMode::Linear:	return GL_LINEAR_MIPMAP_LINEAR;
		}
		break;
	}
	return GL_NEAREST_MIPMAP_LINEAR;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_FILTER_MODE_HPP
