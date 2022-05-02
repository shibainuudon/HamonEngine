/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode
 */

#ifndef HAMON_RENDER_FILTER_MODE_HPP
#define HAMON_RENDER_FILTER_MODE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class FilterMode : std::uint32_t
{
    Nearest,
    Linear,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_FILTER_MODE_HPP
