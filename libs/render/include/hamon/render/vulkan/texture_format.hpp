/**
 *	@file	texture_format.hpp
 *
 *	@brief	TextureFormat
 */

#ifndef HAMON_RENDER_VULKAN_TEXTURE_FORMAT_HPP
#define HAMON_RENDER_VULKAN_TEXTURE_FORMAT_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/texture_format.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkFormat
TextureFormat(render::TextureFormat format)
{
    switch (format)
    {
	case render::TextureFormat::R8_UNORM:		        return VK_FORMAT_R8_UNORM;
	case render::TextureFormat::R8_SNORM:		        return VK_FORMAT_R8_SNORM;
	case render::TextureFormat::R8_UINT:			    return VK_FORMAT_R8_UINT;
	case render::TextureFormat::R8_SINT:			    return VK_FORMAT_R8_SINT;
	case render::TextureFormat::R8G8_UNORM:		        return VK_FORMAT_R8G8_UNORM;
	case render::TextureFormat::R8G8_SNORM:		        return VK_FORMAT_R8G8_SNORM;
	case render::TextureFormat::R8G8_UINT:		        return VK_FORMAT_R8G8_UINT;
	case render::TextureFormat::R8G8_SINT:		        return VK_FORMAT_R8G8_SINT;
	case render::TextureFormat::R8G8B8_UNORM:	        return VK_FORMAT_R8G8B8_UNORM;
	case render::TextureFormat::R8G8B8_SNORM:	        return VK_FORMAT_R8G8B8_SNORM;
	case render::TextureFormat::R8G8B8_UINT:		    return VK_FORMAT_R8G8B8_UINT;
	case render::TextureFormat::R8G8B8_SINT:		    return VK_FORMAT_R8G8B8_SINT;
	case render::TextureFormat::B8G8R8_UNORM:	        return VK_FORMAT_B8G8R8_UNORM;
	case render::TextureFormat::B8G8R8_SNORM:	        return VK_FORMAT_B8G8R8_SNORM;
	case render::TextureFormat::B8G8R8_UINT:		    return VK_FORMAT_B8G8R8_UINT;
	case render::TextureFormat::B8G8R8_SINT:		    return VK_FORMAT_B8G8R8_SINT;
	case render::TextureFormat::R8G8B8A8_UNORM:	        return VK_FORMAT_R8G8B8A8_UNORM;
	case render::TextureFormat::R8G8B8A8_SNORM:	        return VK_FORMAT_R8G8B8A8_SNORM;
	case render::TextureFormat::R8G8B8A8_UINT:	        return VK_FORMAT_R8G8B8A8_UINT;
	case render::TextureFormat::R8G8B8A8_SINT:	        return VK_FORMAT_R8G8B8A8_SINT;
	case render::TextureFormat::B8G8R8A8_UNORM:	        return VK_FORMAT_B8G8R8A8_UNORM;
	case render::TextureFormat::B8G8R8A8_SNORM:	        return VK_FORMAT_B8G8R8A8_SNORM;
	case render::TextureFormat::B8G8R8A8_UINT:	        return VK_FORMAT_B8G8R8A8_UINT;
	case render::TextureFormat::B8G8R8A8_SINT:	        return VK_FORMAT_B8G8R8A8_SINT;
	case render::TextureFormat::R16_UNORM:		        return VK_FORMAT_R16_UNORM;
	case render::TextureFormat::R16_SNORM:		        return VK_FORMAT_R16_SNORM;
	case render::TextureFormat::R16_UINT:		        return VK_FORMAT_R16_UINT;
	case render::TextureFormat::R16_SINT:		        return VK_FORMAT_R16_SINT;
	case render::TextureFormat::R16_SFLOAT:		        return VK_FORMAT_R16_SFLOAT;
	case render::TextureFormat::R16G16_UNORM:	        return VK_FORMAT_R16G16_UNORM;
	case render::TextureFormat::R16G16_SNORM:	        return VK_FORMAT_R16G16_SNORM;
	case render::TextureFormat::R16G16_UINT:		    return VK_FORMAT_R16G16_UINT;
	case render::TextureFormat::R16G16_SINT:		    return VK_FORMAT_R16G16_SINT;
	case render::TextureFormat::R16G16_SFLOAT:	        return VK_FORMAT_R16G16_SFLOAT;
	case render::TextureFormat::R16G16B16_UNORM:	    return VK_FORMAT_R16G16B16_UNORM;
	case render::TextureFormat::R16G16B16_SNORM:	    return VK_FORMAT_R16G16B16_SNORM;
	case render::TextureFormat::R16G16B16_UINT:	        return VK_FORMAT_R16G16B16_UINT;
	case render::TextureFormat::R16G16B16_SINT:	        return VK_FORMAT_R16G16B16_SINT;
	case render::TextureFormat::R16G16B16_SFLOAT:       return VK_FORMAT_R16G16B16_SFLOAT;
	case render::TextureFormat::R16G16B16A16_UNORM:	    return VK_FORMAT_R16G16B16A16_UNORM;
	case render::TextureFormat::R16G16B16A16_SNORM:	    return VK_FORMAT_R16G16B16A16_SNORM;
	case render::TextureFormat::R16G16B16A16_UINT:	    return VK_FORMAT_R16G16B16A16_UINT;
	case render::TextureFormat::R16G16B16A16_SINT:	    return VK_FORMAT_R16G16B16A16_SINT;
	case render::TextureFormat::R16G16B16A16_SFLOAT:	return VK_FORMAT_R16G16B16A16_SFLOAT;
	case render::TextureFormat::R32_UINT:			    return VK_FORMAT_R32_UINT;
	case render::TextureFormat::R32_SINT:			    return VK_FORMAT_R32_SINT;
	case render::TextureFormat::R32_SFLOAT:			    return VK_FORMAT_R32_SFLOAT;
	case render::TextureFormat::R32G32_UINT:			return VK_FORMAT_R32G32_UINT;
	case render::TextureFormat::R32G32_SINT:			return VK_FORMAT_R32G32_SINT;
	case render::TextureFormat::R32G32_SFLOAT:		    return VK_FORMAT_R32G32_SFLOAT;
	case render::TextureFormat::R32G32B32_UINT:		    return VK_FORMAT_R32G32B32_UINT;
	case render::TextureFormat::R32G32B32_SINT:		    return VK_FORMAT_R32G32B32_SINT;
	case render::TextureFormat::R32G32B32_SFLOAT:	    return VK_FORMAT_R32G32B32_SFLOAT;
	case render::TextureFormat::R32G32B32A32_UINT:	    return VK_FORMAT_R32G32B32A32_UINT;
	case render::TextureFormat::R32G32B32A32_SINT:	    return VK_FORMAT_R32G32B32A32_SINT;
	case render::TextureFormat::R32G32B32A32_SFLOAT:	return VK_FORMAT_R32G32B32A32_SFLOAT;
	case render::TextureFormat::R64_UINT:			    return VK_FORMAT_R64_UINT;
	case render::TextureFormat::R64_SINT:			    return VK_FORMAT_R64_SINT;
	case render::TextureFormat::R64_SFLOAT:				return VK_FORMAT_R64_SFLOAT;
	case render::TextureFormat::R64G64_UINT:			return VK_FORMAT_R64G64_UINT;
	case render::TextureFormat::R64G64_SINT:			return VK_FORMAT_R64G64_SINT;
	case render::TextureFormat::R64G64_SFLOAT:			return VK_FORMAT_R64G64_SFLOAT;
	case render::TextureFormat::R64G64B64_UINT:			return VK_FORMAT_R64G64B64_UINT;
	case render::TextureFormat::R64G64B64_SINT:			return VK_FORMAT_R64G64B64_SINT;
	case render::TextureFormat::R64G64B64_SFLOAT:	    return VK_FORMAT_R64G64B64_SFLOAT;
	case render::TextureFormat::R64G64B64A64_UINT:		return VK_FORMAT_R64G64B64A64_UINT;
	case render::TextureFormat::R64G64B64A64_SINT:		return VK_FORMAT_R64G64B64A64_SINT;
	case render::TextureFormat::R64G64B64A64_SFLOAT:	return VK_FORMAT_R64G64B64A64_SFLOAT;
	case render::TextureFormat::D16_UNORM:			    return VK_FORMAT_D16_UNORM;
	case render::TextureFormat::X8_D24_UNORM_PACK32:	return VK_FORMAT_X8_D24_UNORM_PACK32;
	case render::TextureFormat::D32_SFLOAT:			    return VK_FORMAT_D32_SFLOAT;
	case render::TextureFormat::S8_UINT:				return VK_FORMAT_S8_UINT;
	case render::TextureFormat::D16_UNORM_S8_UINT:		return VK_FORMAT_D16_UNORM_S8_UINT;
	case render::TextureFormat::D24_UNORM_S8_UINT:	    return VK_FORMAT_D24_UNORM_S8_UINT;
	case render::TextureFormat::D32_SFLOAT_S8_UINT:	    return VK_FORMAT_D32_SFLOAT_S8_UINT;
    }
    return VK_FORMAT_UNDEFINED;
}

inline std::size_t GetBytesPerPixel(::VkFormat format)
{
	switch (format)
	{
	case VK_FORMAT_R8_UNORM:
	case VK_FORMAT_R8_SNORM:
	case VK_FORMAT_R8_UINT:
	case VK_FORMAT_R8_SINT:
		return 1;
	case VK_FORMAT_R8G8_UNORM:
	case VK_FORMAT_R8G8_SNORM:
	case VK_FORMAT_R8G8_UINT:
	case VK_FORMAT_R8G8_SINT:
		return 2;
	case VK_FORMAT_R8G8B8_UNORM:
	case VK_FORMAT_R8G8B8_SNORM:
	case VK_FORMAT_R8G8B8_UINT:
	case VK_FORMAT_R8G8B8_SINT:
	case VK_FORMAT_B8G8R8_UNORM:
	case VK_FORMAT_B8G8R8_SNORM:
	case VK_FORMAT_B8G8R8_UINT:
	case VK_FORMAT_B8G8R8_SINT:
		return 3;
	case VK_FORMAT_R8G8B8A8_UNORM:
	case VK_FORMAT_R8G8B8A8_SNORM:
	case VK_FORMAT_R8G8B8A8_UINT:
	case VK_FORMAT_R8G8B8A8_SINT:
	case VK_FORMAT_B8G8R8A8_UNORM:
	case VK_FORMAT_B8G8R8A8_SNORM:
	case VK_FORMAT_B8G8R8A8_UINT:
	case VK_FORMAT_B8G8R8A8_SINT:
		return 4;
	case VK_FORMAT_R16_UNORM:
	case VK_FORMAT_R16_SNORM:
	case VK_FORMAT_R16_UINT:
	case VK_FORMAT_R16_SINT:
	case VK_FORMAT_R16_SFLOAT:
		return 2;
	case VK_FORMAT_R16G16_UNORM:
	case VK_FORMAT_R16G16_SNORM:
	case VK_FORMAT_R16G16_UINT:
	case VK_FORMAT_R16G16_SINT:
	case VK_FORMAT_R16G16_SFLOAT:
		return 4;
	case VK_FORMAT_R16G16B16_UNORM:
	case VK_FORMAT_R16G16B16_SNORM:
	case VK_FORMAT_R16G16B16_UINT:
	case VK_FORMAT_R16G16B16_SINT:
	case VK_FORMAT_R16G16B16_SFLOAT:
		return 6;
	case VK_FORMAT_R16G16B16A16_UNORM:
	case VK_FORMAT_R16G16B16A16_SNORM:
	case VK_FORMAT_R16G16B16A16_UINT:
	case VK_FORMAT_R16G16B16A16_SINT:
	case VK_FORMAT_R16G16B16A16_SFLOAT:
		return 8;
	case VK_FORMAT_R32_UINT:
	case VK_FORMAT_R32_SINT:
	case VK_FORMAT_R32_SFLOAT:
		return 4;
	case VK_FORMAT_R32G32_UINT:
	case VK_FORMAT_R32G32_SINT:
	case VK_FORMAT_R32G32_SFLOAT:
		return 8;
	case VK_FORMAT_R32G32B32_UINT:
	case VK_FORMAT_R32G32B32_SINT:
	case VK_FORMAT_R32G32B32_SFLOAT:
		return 12;
	case VK_FORMAT_R32G32B32A32_UINT:
	case VK_FORMAT_R32G32B32A32_SINT:
	case VK_FORMAT_R32G32B32A32_SFLOAT:
		return 16;
	case VK_FORMAT_R64_UINT:
	case VK_FORMAT_R64_SINT:
	case VK_FORMAT_R64_SFLOAT:
		return 8;
	case VK_FORMAT_R64G64_UINT:
	case VK_FORMAT_R64G64_SINT:
	case VK_FORMAT_R64G64_SFLOAT:
		return 16;
	case VK_FORMAT_R64G64B64_UINT:
	case VK_FORMAT_R64G64B64_SINT:
	case VK_FORMAT_R64G64B64_SFLOAT:
		return 24;
	case VK_FORMAT_R64G64B64A64_UINT:
	case VK_FORMAT_R64G64B64A64_SINT:
	case VK_FORMAT_R64G64B64A64_SFLOAT:
		return 32;
	case VK_FORMAT_D16_UNORM:
		return 2;
	case VK_FORMAT_X8_D24_UNORM_PACK32:
	case VK_FORMAT_D32_SFLOAT:
		return 4;
	case VK_FORMAT_S8_UINT:
		return 1;
	case VK_FORMAT_D16_UNORM_S8_UINT:
		return 3;
	case VK_FORMAT_D24_UNORM_S8_UINT:
		return 4;
	case VK_FORMAT_D32_SFLOAT_S8_UINT:
		return 5;
	}
	return 0;
}

inline std::size_t GetSizeInBytes(
	::VkFormat format,
	std::uint32_t width,
	std::uint32_t height)
{
	return GetBytesPerPixel(format) * width * height;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_TEXTURE_FORMAT_HPP
