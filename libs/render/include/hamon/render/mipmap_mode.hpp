/**
 *	@file	mipmap_mode.hpp
 *
 *	@brief	MipmapMode
 */

#ifndef HAMON_RENDER_MIPMAP_MODE_HPP
#define HAMON_RENDER_MIPMAP_MODE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class MipmapMode : std::uint32_t
{
    Disable,
    Nearest,
    Linear,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_MIPMAP_MODE_HPP
