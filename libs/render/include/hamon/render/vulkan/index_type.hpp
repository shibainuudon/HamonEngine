/**
 *	@file	index_type.hpp
 *
 *	@brief	IndexType
 */

#ifndef HAMON_RENDER_VULKAN_index_type_HPP
#define HAMON_RENDER_VULKAN_index_type_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/index_type.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkIndexType
IndexType(render::IndexType type)
{
	switch (type)
	{
	case render::IndexType::UInt16:	return VK_INDEX_TYPE_UINT16;
	case render::IndexType::UInt32:	return VK_INDEX_TYPE_UINT32;
	}
	return VK_INDEX_TYPE_UINT16;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_index_type_HPP
