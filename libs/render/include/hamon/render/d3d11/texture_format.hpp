/**
 *	@file	texture_format.hpp
 *
 *	@brief	TextureFormat
 */

#ifndef HAMON_RENDER_D3D11_TEXTURE_FORMAT_HPP
#define HAMON_RENDER_D3D11_TEXTURE_FORMAT_HPP

#include <hamon/render/texture_format.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::DXGI_FORMAT TextureFormat(render::TextureFormat format)
{
    switch (format)
    {
	case render::TextureFormat::R8_UNORM:		        return DXGI_FORMAT_R8_UNORM;
	case render::TextureFormat::R8_SNORM:		        return DXGI_FORMAT_R8_SNORM;
	case render::TextureFormat::R8_UINT:			    return DXGI_FORMAT_R8_UINT;
	case render::TextureFormat::R8_SINT:			    return DXGI_FORMAT_R8_SINT;
	case render::TextureFormat::R8G8_UNORM:		        return DXGI_FORMAT_R8G8_UNORM;
	case render::TextureFormat::R8G8_SNORM:		        return DXGI_FORMAT_R8G8_SNORM;
	case render::TextureFormat::R8G8_UINT:		        return DXGI_FORMAT_R8G8_UINT;
	case render::TextureFormat::R8G8_SINT:		        return DXGI_FORMAT_R8G8_SINT;
	//case render::TextureFormat::R8G8B8_UNORM:	        return 
	//case render::TextureFormat::R8G8B8_SNORM:	        return 
	//case render::TextureFormat::R8G8B8_UINT:		    return 
	//case render::TextureFormat::R8G8B8_SINT:		    return 
	//case render::TextureFormat::B8G8R8_UNORM:	        return 
	//case render::TextureFormat::B8G8R8_SNORM:	        return 
	//case render::TextureFormat::B8G8R8_UINT:		    return 
	//case render::TextureFormat::B8G8R8_SINT:		    return 
	case render::TextureFormat::R8G8B8A8_UNORM:	        return DXGI_FORMAT_R8G8B8A8_UNORM;
	case render::TextureFormat::R8G8B8A8_SNORM:	        return DXGI_FORMAT_R8G8B8A8_SNORM;
	case render::TextureFormat::R8G8B8A8_UINT:	        return DXGI_FORMAT_R8G8B8A8_UINT;
	case render::TextureFormat::R8G8B8A8_SINT:	        return DXGI_FORMAT_R8G8B8A8_SINT;
	case render::TextureFormat::B8G8R8A8_UNORM:	        return DXGI_FORMAT_B8G8R8A8_UNORM;
//	case render::TextureFormat::B8G8R8A8_SNORM:	        return DXGI_FORMAT_B8G8R8A8_SNORM;
//	case render::TextureFormat::B8G8R8A8_UINT:	        return DXGI_FORMAT_B8G8R8A8_UINT;
//	case render::TextureFormat::B8G8R8A8_SINT:	        return DXGI_FORMAT_B8G8R8A8_SINT;
	case render::TextureFormat::R16_UNORM:		        return DXGI_FORMAT_R16_UNORM;
	case render::TextureFormat::R16_SNORM:		        return DXGI_FORMAT_R16_SNORM;
	case render::TextureFormat::R16_UINT:		        return DXGI_FORMAT_R16_UINT;
	case render::TextureFormat::R16_SINT:		        return DXGI_FORMAT_R16_SINT;
	case render::TextureFormat::R16_SFLOAT:		        return DXGI_FORMAT_R16_FLOAT;
	case render::TextureFormat::R16G16_UNORM:	        return DXGI_FORMAT_R16G16_UNORM;
	case render::TextureFormat::R16G16_SNORM:	        return DXGI_FORMAT_R16G16_SNORM;
	case render::TextureFormat::R16G16_UINT:		    return DXGI_FORMAT_R16G16_UINT;
	case render::TextureFormat::R16G16_SINT:		    return DXGI_FORMAT_R16G16_SINT;
	case render::TextureFormat::R16G16_SFLOAT:	        return DXGI_FORMAT_R16G16_FLOAT;
	//case render::TextureFormat::R16G16B16_UNORM:	    return 
	//case render::TextureFormat::R16G16B16_SNORM:	    return 
	//case render::TextureFormat::R16G16B16_UINT:	        return 
	//case render::TextureFormat::R16G16B16_SINT:	        return 
	//case render::TextureFormat::R16G16B16_SFLOAT:       return 
	case render::TextureFormat::R16G16B16A16_UNORM:	    return DXGI_FORMAT_R16G16B16A16_UNORM;
	case render::TextureFormat::R16G16B16A16_SNORM:	    return DXGI_FORMAT_R16G16B16A16_SNORM;
	case render::TextureFormat::R16G16B16A16_UINT:	    return DXGI_FORMAT_R16G16B16A16_UINT;
	case render::TextureFormat::R16G16B16A16_SINT:	    return DXGI_FORMAT_R16G16B16A16_SINT;
	case render::TextureFormat::R16G16B16A16_SFLOAT:	return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case render::TextureFormat::R32_UINT:			    return DXGI_FORMAT_R32_UINT;
	case render::TextureFormat::R32_SINT:			    return DXGI_FORMAT_R32_SINT;
	case render::TextureFormat::R32_SFLOAT:			    return DXGI_FORMAT_R32_FLOAT;
	case render::TextureFormat::R32G32_UINT:			return DXGI_FORMAT_R32G32_UINT;
	case render::TextureFormat::R32G32_SINT:			return DXGI_FORMAT_R32G32_SINT;
	case render::TextureFormat::R32G32_SFLOAT:		    return DXGI_FORMAT_R32G32_FLOAT;
	case render::TextureFormat::R32G32B32_UINT:		    return DXGI_FORMAT_R32G32B32_UINT;
	case render::TextureFormat::R32G32B32_SINT:		    return DXGI_FORMAT_R32G32B32_SINT;
	case render::TextureFormat::R32G32B32_SFLOAT:	    return DXGI_FORMAT_R32G32B32_FLOAT;
	case render::TextureFormat::R32G32B32A32_UINT:	    return DXGI_FORMAT_R32G32B32A32_UINT;
	case render::TextureFormat::R32G32B32A32_SINT:	    return DXGI_FORMAT_R32G32B32A32_SINT;
	case render::TextureFormat::R32G32B32A32_SFLOAT:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
	//case render::TextureFormat::R64_UINT:			    return 
	//case render::TextureFormat::R64_SINT:			    return 
	//case render::TextureFormat::R64_SFLOAT:			return 
	//case render::TextureFormat::R64G64_UINT:			return 
	//case render::TextureFormat::R64G64_SINT:			return 
	//case render::TextureFormat::R64G64_SFLOAT:		return 
	//case render::TextureFormat::R64G64B64_UINT:		return 
	//case render::TextureFormat::R64G64B64_SINT:		return 
	//case render::TextureFormat::R64G64B64_SFLOAT:	    return 
	//case render::TextureFormat::R64G64B64A64_UINT:	return 
	//case render::TextureFormat::R64G64B64A64_SINT:	return 
	//case render::TextureFormat::R64G64B64A64_SFLOAT:	return 
	case render::TextureFormat::D16_UNORM:			    return DXGI_FORMAT_D16_UNORM;
	//case render::TextureFormat::X8_D24_UNORM_PACK32:	return 
	case render::TextureFormat::D32_SFLOAT:			    return DXGI_FORMAT_D32_FLOAT;
	//case render::TextureFormat::S8_UINT:				return 
	//case render::TextureFormat::D16_UNORM_S8_UINT:	return 
	case render::TextureFormat::D24_UNORM_S8_UINT:	    return DXGI_FORMAT_D24_UNORM_S8_UINT;
	//case render::TextureFormat::D32_SFLOAT_S8_UINT:	    return 
    }
    return DXGI_FORMAT_UNKNOWN;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_TEXTURE_FORMAT_HPP
