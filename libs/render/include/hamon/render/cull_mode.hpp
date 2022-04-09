/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode
 */

#ifndef HAMON_RENDER_CULL_MODE_HPP
#define HAMON_RENDER_CULL_MODE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class CullMode : std::uint32_t
{
	None,
	Front,
	Back,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_CULL_MODE_HPP
