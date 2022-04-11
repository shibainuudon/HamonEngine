/**
 *	@file	format.hpp
 *
 *	@brief	Format
 */

#ifndef HAMON_RENDER_VULKAN_FORMAT_HPP
#define HAMON_RENDER_VULKAN_FORMAT_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/type.hpp>
#include <cstddef>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkFormat Format(render::Type type, std::size_t element_num)
{
	switch (element_num)
	{
	case 1:
		switch (type)
		{
		case render::Type::Int8:	return VK_FORMAT_R8_SINT;
		case render::Type::Int16:	return VK_FORMAT_R16_SINT;
		case render::Type::Int32:	return VK_FORMAT_R32_SINT;
		case render::Type::UInt8:	return VK_FORMAT_R8_UINT;
		case render::Type::UInt16:	return VK_FORMAT_R16_UINT;
		case render::Type::UInt32:	return VK_FORMAT_R32_UINT;
		case render::Type::Float:	return VK_FORMAT_R32_SFLOAT;
		}
		break;
	case 2:
		switch (type)
		{
		case render::Type::Int8:	return VK_FORMAT_R8G8_SINT;
		case render::Type::Int16:	return VK_FORMAT_R16G16_SINT;
		case render::Type::Int32:	return VK_FORMAT_R32G32_SINT;
		case render::Type::UInt8:	return VK_FORMAT_R8G8_UINT;
		case render::Type::UInt16:	return VK_FORMAT_R16G16_UINT;
		case render::Type::UInt32:	return VK_FORMAT_R32G32_UINT;
		case render::Type::Float:	return VK_FORMAT_R32G32_SFLOAT;
		}
		break;
	case 3:
		switch (type)
		{
		case render::Type::Int8:	return VK_FORMAT_R8G8B8_SINT;
		case render::Type::Int16:	return VK_FORMAT_R16G16B16_SINT;
		case render::Type::Int32:	return VK_FORMAT_R32G32B32_SINT;
		case render::Type::UInt8:	return VK_FORMAT_R8G8B8_UINT;
		case render::Type::UInt16:	return VK_FORMAT_R16G16B16_UINT;
		case render::Type::UInt32:	return VK_FORMAT_R32G32B32_UINT;
		case render::Type::Float:	return VK_FORMAT_R32G32B32_SFLOAT;
		}
		break;
	case 4:
		switch (type)
		{
		case render::Type::Int8:	return VK_FORMAT_R8G8B8A8_SINT;
		case render::Type::Int16:	return VK_FORMAT_R16G16B16A16_SINT;
		case render::Type::Int32:	return VK_FORMAT_R32G32B32A32_SINT;
		case render::Type::UInt8:	return VK_FORMAT_R8G8B8A8_UINT;
		case render::Type::UInt16:	return VK_FORMAT_R16G16B16A16_UINT;
		case render::Type::UInt32:	return VK_FORMAT_R32G32B32A32_UINT;
		case render::Type::Float:	return VK_FORMAT_R32G32B32A32_SFLOAT;
		}
		break;
	}
	return VK_FORMAT_UNDEFINED;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_FORMAT_HPP
