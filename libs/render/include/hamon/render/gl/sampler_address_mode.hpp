/**
 *	@file	sampler_address_mode.hpp
 *
 *	@brief	SamplerAddressMode
 */

#ifndef HAMON_RENDER_GL_SAMPLER_ADDRESS_MODE_HPP
#define HAMON_RENDER_GL_SAMPLER_ADDRESS_MODE_HPP

#include <hamon/render/sampler_address_mode.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum SamplerAddressMode(render::SamplerAddressMode mode)
{
	switch (mode)
	{
	case hamon::render::SamplerAddressMode::Repeat:				return GL_REPEAT;
	case hamon::render::SamplerAddressMode::MirroredRepeat:		return GL_MIRRORED_REPEAT;
	case hamon::render::SamplerAddressMode::ClampToEdge:		return GL_CLAMP_TO_EDGE;
	case hamon::render::SamplerAddressMode::ClampToBorder:		return GL_CLAMP_TO_BORDER;
	case hamon::render::SamplerAddressMode::MirrorClampToEdge:	return GL_MIRROR_CLAMP_TO_EDGE;
	}
	return GL_REPEAT;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_SAMPLER_ADDRESS_MODE_HPP
