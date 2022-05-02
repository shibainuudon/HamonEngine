/**
 *	@file	texture_format.hpp
 *
 *	@brief	TextureFormat
 */

#ifndef HAMON_RENDER_TEXTURE_FORMAT_HPP
#define HAMON_RENDER_TEXTURE_FORMAT_HPP

#include <cstdint>
#include <cstddef>

namespace hamon
{

inline namespace render
{

enum class TextureFormat : std::uint32_t
{
	R8_UNORM,
	R8_SNORM,
	R8_UINT,
	R8_SINT,
	R8G8_UNORM,
	R8G8_SNORM,
	R8G8_UINT,
	R8G8_SINT,
	R8G8B8_UNORM,
	R8G8B8_SNORM,
	R8G8B8_UINT,
	R8G8B8_SINT,
	B8G8R8_UNORM,
	B8G8R8_SNORM,
	B8G8R8_UINT,
	B8G8R8_SINT,
	R8G8B8A8_UNORM,
	R8G8B8A8_SNORM,
	R8G8B8A8_UINT,
	R8G8B8A8_SINT,
	B8G8R8A8_UNORM,
	B8G8R8A8_SNORM,
	B8G8R8A8_UINT,
	B8G8R8A8_SINT,
	R16_UNORM,
	R16_SNORM,
	R16_UINT,
	R16_SINT,
	R16_SFLOAT,
	R16G16_UNORM,
	R16G16_SNORM,
	R16G16_UINT,
	R16G16_SINT,
	R16G16_SFLOAT,
	R16G16B16_UNORM,
	R16G16B16_SNORM,
	R16G16B16_UINT,
	R16G16B16_SINT,
	R16G16B16_SFLOAT,
	R16G16B16A16_UNORM,
	R16G16B16A16_SNORM,
	R16G16B16A16_UINT,
	R16G16B16A16_SINT,
	R16G16B16A16_SFLOAT,
	R32_UINT,
	R32_SINT,
	R32_SFLOAT,
	R32G32_UINT,
	R32G32_SINT,
	R32G32_SFLOAT,
	R32G32B32_UINT,
	R32G32B32_SINT,
	R32G32B32_SFLOAT,
	R32G32B32A32_UINT,
	R32G32B32A32_SINT,
	R32G32B32A32_SFLOAT,
	R64_UINT,
	R64_SINT,
	R64_SFLOAT,
	R64G64_UINT,
	R64G64_SINT,
	R64G64_SFLOAT,
	R64G64B64_UINT,
	R64G64B64_SINT,
	R64G64B64_SFLOAT,
	R64G64B64A64_UINT,
	R64G64B64A64_SINT,
	R64G64B64A64_SFLOAT,
	D16_UNORM,
	X8_D24_UNORM_PACK32,
	D32_SFLOAT,
	S8_UINT,
	D16_UNORM_S8_UINT,
	D24_UNORM_S8_UINT,
	D32_SFLOAT_S8_UINT,
};

inline std::size_t GetBytesPerPixel(TextureFormat format)
{
	switch (format)
	{
	case TextureFormat::R8_UNORM:
	case TextureFormat::R8_SNORM:
	case TextureFormat::R8_UINT:
	case TextureFormat::R8_SINT:
		return 1;
	case TextureFormat::R8G8_UNORM:
	case TextureFormat::R8G8_SNORM:
	case TextureFormat::R8G8_UINT:
	case TextureFormat::R8G8_SINT:
		return 2;
	case TextureFormat::R8G8B8_UNORM:
	case TextureFormat::R8G8B8_SNORM:
	case TextureFormat::R8G8B8_UINT:
	case TextureFormat::R8G8B8_SINT:
	case TextureFormat::B8G8R8_UNORM:
	case TextureFormat::B8G8R8_SNORM:
	case TextureFormat::B8G8R8_UINT:
	case TextureFormat::B8G8R8_SINT:
		return 3;
	case TextureFormat::R8G8B8A8_UNORM:
	case TextureFormat::R8G8B8A8_SNORM:
	case TextureFormat::R8G8B8A8_UINT:
	case TextureFormat::R8G8B8A8_SINT:
	case TextureFormat::B8G8R8A8_UNORM:
	case TextureFormat::B8G8R8A8_SNORM:
	case TextureFormat::B8G8R8A8_UINT:
	case TextureFormat::B8G8R8A8_SINT:
		return 4;
	case TextureFormat::R16_UNORM:
	case TextureFormat::R16_SNORM:
	case TextureFormat::R16_UINT:
	case TextureFormat::R16_SINT:
	case TextureFormat::R16_SFLOAT:
		return 2;
	case TextureFormat::R16G16_UNORM:
	case TextureFormat::R16G16_SNORM:
	case TextureFormat::R16G16_UINT:
	case TextureFormat::R16G16_SINT:
	case TextureFormat::R16G16_SFLOAT:
		return 4;
	case TextureFormat::R16G16B16_UNORM:
	case TextureFormat::R16G16B16_SNORM:
	case TextureFormat::R16G16B16_UINT:
	case TextureFormat::R16G16B16_SINT:
	case TextureFormat::R16G16B16_SFLOAT:
		return 6;
	case TextureFormat::R16G16B16A16_UNORM:
	case TextureFormat::R16G16B16A16_SNORM:
	case TextureFormat::R16G16B16A16_UINT:
	case TextureFormat::R16G16B16A16_SINT:
	case TextureFormat::R16G16B16A16_SFLOAT:
		return 8;
	case TextureFormat::R32_UINT:
	case TextureFormat::R32_SINT:
	case TextureFormat::R32_SFLOAT:
		return 4;
	case TextureFormat::R32G32_UINT:
	case TextureFormat::R32G32_SINT:
	case TextureFormat::R32G32_SFLOAT:
		return 8;
	case TextureFormat::R32G32B32_UINT:
	case TextureFormat::R32G32B32_SINT:
	case TextureFormat::R32G32B32_SFLOAT:
		return 12;
	case TextureFormat::R32G32B32A32_UINT:
	case TextureFormat::R32G32B32A32_SINT:
	case TextureFormat::R32G32B32A32_SFLOAT:
		return 16;
	case TextureFormat::R64_UINT:
	case TextureFormat::R64_SINT:
	case TextureFormat::R64_SFLOAT:
		return 8;
	case TextureFormat::R64G64_UINT:
	case TextureFormat::R64G64_SINT:
	case TextureFormat::R64G64_SFLOAT:
		return 16;
	case TextureFormat::R64G64B64_UINT:
	case TextureFormat::R64G64B64_SINT:
	case TextureFormat::R64G64B64_SFLOAT:
		return 24;
	case TextureFormat::R64G64B64A64_UINT:
	case TextureFormat::R64G64B64A64_SINT:
	case TextureFormat::R64G64B64A64_SFLOAT:
		return 32;
	case TextureFormat::D16_UNORM:
		return 2;
	case TextureFormat::X8_D24_UNORM_PACK32:
	case TextureFormat::D32_SFLOAT:
		return 4;
	case TextureFormat::S8_UINT:
		return 1;
	case TextureFormat::D16_UNORM_S8_UINT:
		return 3;
	case TextureFormat::D24_UNORM_S8_UINT:
		return 4;
	case TextureFormat::D32_SFLOAT_S8_UINT:
		return 5;
	}
	return 0;
}

inline std::size_t GetSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height)
{
	return GetBytesPerPixel(format) * width * height;
}

inline std::size_t GetMipmappedSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height,
	std::uint32_t mipmap_count)
{
	std::size_t result = 0;
		
	while (mipmap_count != 0)
	{
		result += GetSizeInBytes(format, width, height);
		width  /= 2;
		height /= 2;
		--mipmap_count;
	}

	return result;
}

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_TEXTURE_FORMAT_HPP
