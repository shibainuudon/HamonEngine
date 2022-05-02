/**
 *	@file	sampler_address_mode.hpp
 *
 *	@brief	SamplerAddressMode
 */

#ifndef HAMON_RENDER_D3D11_SAMPLER_ADDRESS_MODE_HPP
#define HAMON_RENDER_D3D11_SAMPLER_ADDRESS_MODE_HPP

#include <hamon/render/sampler_address_mode.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_TEXTURE_ADDRESS_MODE
SamplerAddressMode(render::SamplerAddressMode mode)
{
	switch (mode)
	{
	case render::SamplerAddressMode::Repeat:			return D3D11_TEXTURE_ADDRESS_WRAP;
	case render::SamplerAddressMode::MirroredRepeat:	return D3D11_TEXTURE_ADDRESS_MIRROR;
	case render::SamplerAddressMode::ClampToEdge:		return D3D11_TEXTURE_ADDRESS_CLAMP;
	case render::SamplerAddressMode::ClampToBorder:		return D3D11_TEXTURE_ADDRESS_BORDER;
	case render::SamplerAddressMode::MirrorClampToEdge:	return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	}
	return D3D11_TEXTURE_ADDRESS_WRAP;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_SAMPLER_ADDRESS_MODE_HPP
