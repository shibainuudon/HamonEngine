/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace
 */

#ifndef HAMON_RENDER_VULKAN_FRONT_FACE_HPP
#define HAMON_RENDER_VULKAN_FRONT_FACE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/front_face.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkFrontFace
FrontFace(render::FrontFace face)
{
	switch (face)
	{
	case render::FrontFace::Clockwise:			return VK_FRONT_FACE_CLOCKWISE;
	case render::FrontFace::CounterClockwise:	return VK_FRONT_FACE_COUNTER_CLOCKWISE;
	}
	return VK_FRONT_FACE_CLOCKWISE;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_FRONT_FACE_HPP
