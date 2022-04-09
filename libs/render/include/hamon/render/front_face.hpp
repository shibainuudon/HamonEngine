/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace
 */

#ifndef HAMON_RENDER_FRONT_FACE_HPP
#define HAMON_RENDER_FRONT_FACE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class FrontFace : std::uint32_t
{
	Clockwise,
	CounterClockwise,

	// alias
	CW = Clockwise,
	CCW = CounterClockwise,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_FRONT_FACE_HPP
