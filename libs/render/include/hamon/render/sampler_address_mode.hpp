/**
 *	@file	sampler_address_mode.hpp
 *
 *	@brief	SamplerAddressMode
 */

#ifndef HAMON_RENDER_SAMPLER_ADDRESS_MODE_HPP
#define HAMON_RENDER_SAMPLER_ADDRESS_MODE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class SamplerAddressMode : std::uint32_t
{
	Repeat,
	MirroredRepeat,
	ClampToEdge,
	ClampToBorder,
	MirrorClampToEdge,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SAMPLER_ADDRESS_MODE_HPP
