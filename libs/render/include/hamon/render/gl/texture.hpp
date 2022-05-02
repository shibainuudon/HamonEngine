/**
 *	@file	texture.hpp
 *
 *	@brief	Texture
 */

#ifndef HAMON_RENDER_GL_TEXTURE_HPP
#define HAMON_RENDER_GL_TEXTURE_HPP

#include <hamon/render/texture.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Texture
{
	static GLenum ToGlFormat(render::TextureFormat format)
	{
		switch (format)
		{
		case hamon::render::TextureFormat::R8_UNORM:
		case hamon::render::TextureFormat::R8_SNORM:
		case hamon::render::TextureFormat::R8_UINT:
		case hamon::render::TextureFormat::R8_SINT:
		case hamon::render::TextureFormat::R16_UNORM:
		case hamon::render::TextureFormat::R16_SNORM:
		case hamon::render::TextureFormat::R16_UINT:
		case hamon::render::TextureFormat::R16_SINT:
		case hamon::render::TextureFormat::R16_SFLOAT:
		case hamon::render::TextureFormat::R32_UINT:
		case hamon::render::TextureFormat::R32_SINT:
		case hamon::render::TextureFormat::R32_SFLOAT:
			return GL_RED;
		case hamon::render::TextureFormat::R8G8_UNORM:
		case hamon::render::TextureFormat::R8G8_SNORM:
		case hamon::render::TextureFormat::R8G8_UINT:
		case hamon::render::TextureFormat::R8G8_SINT:
		case hamon::render::TextureFormat::R16G16_UNORM:
		case hamon::render::TextureFormat::R16G16_SNORM:
		case hamon::render::TextureFormat::R16G16_UINT:
		case hamon::render::TextureFormat::R16G16_SINT:
		case hamon::render::TextureFormat::R16G16_SFLOAT:
		case hamon::render::TextureFormat::R32G32_UINT:
		case hamon::render::TextureFormat::R32G32_SINT:
		case hamon::render::TextureFormat::R32G32_SFLOAT:
			return GL_RG;
		case hamon::render::TextureFormat::R8G8B8_UNORM:
		case hamon::render::TextureFormat::R8G8B8_SNORM:
		case hamon::render::TextureFormat::R8G8B8_UINT:
		case hamon::render::TextureFormat::R8G8B8_SINT:
		case hamon::render::TextureFormat::R16G16B16_UNORM:
		case hamon::render::TextureFormat::R16G16B16_SNORM:
		case hamon::render::TextureFormat::R16G16B16_UINT:
		case hamon::render::TextureFormat::R16G16B16_SINT:
		case hamon::render::TextureFormat::R16G16B16_SFLOAT:
		case hamon::render::TextureFormat::R32G32B32_UINT:
		case hamon::render::TextureFormat::R32G32B32_SINT:
		case hamon::render::TextureFormat::R32G32B32_SFLOAT:
			return GL_RGB;
		case hamon::render::TextureFormat::B8G8R8_UNORM:
		case hamon::render::TextureFormat::B8G8R8_SNORM:
		case hamon::render::TextureFormat::B8G8R8_UINT:
		case hamon::render::TextureFormat::B8G8R8_SINT:
			return GL_BGR;
		case hamon::render::TextureFormat::R8G8B8A8_UNORM:
		case hamon::render::TextureFormat::R8G8B8A8_SNORM:
		case hamon::render::TextureFormat::R8G8B8A8_UINT:
		case hamon::render::TextureFormat::R8G8B8A8_SINT:
		case hamon::render::TextureFormat::R16G16B16A16_UNORM:
		case hamon::render::TextureFormat::R16G16B16A16_SNORM:
		case hamon::render::TextureFormat::R16G16B16A16_UINT:
		case hamon::render::TextureFormat::R16G16B16A16_SINT:
		case hamon::render::TextureFormat::R16G16B16A16_SFLOAT:
		case hamon::render::TextureFormat::R32G32B32A32_UINT:
		case hamon::render::TextureFormat::R32G32B32A32_SINT:
		case hamon::render::TextureFormat::R32G32B32A32_SFLOAT:
			return GL_RGBA;
		case hamon::render::TextureFormat::B8G8R8A8_UNORM:
		case hamon::render::TextureFormat::B8G8R8A8_SNORM:
		case hamon::render::TextureFormat::B8G8R8A8_UINT:
		case hamon::render::TextureFormat::B8G8R8A8_SINT:
			return GL_BGRA;
		//case hamon::render::TextureFormat::R64_UINT:			return GL_R64UI;
		//case hamon::render::TextureFormat::R64_SINT:			return GL_R64I;
		//case hamon::render::TextureFormat::R64_SFLOAT:			return GL_R64F;
		//case hamon::render::TextureFormat::R64G64_UINT:			return GL_RG64UI;
		//case hamon::render::TextureFormat::R64G64_SINT:			return GL_RG64I;
		//case hamon::render::TextureFormat::R64G64_SFLOAT:		return GL_RG64F;
		//case hamon::render::TextureFormat::R64G64B64_UINT:		return GL_RGB64UI;
		//case hamon::render::TextureFormat::R64G64B64_SINT:		return GL_RGB64I;
		//case hamon::render::TextureFormat::R64G64B64_SFLOAT:	return GL_RGB64F;
		//case hamon::render::TextureFormat::R64G64B64A64_UINT:	return GL_RGBA64UI;
		//case hamon::render::TextureFormat::R64G64B64A64_SINT:	return GL_RGBA64I;
		//case hamon::render::TextureFormat::R64G64B64A64_SFLOAT:	return GL_RGBA64F;
		case hamon::render::TextureFormat::D16_UNORM:
		case hamon::render::TextureFormat::X8_D24_UNORM_PACK32:
		case hamon::render::TextureFormat::D32_SFLOAT:
			return GL_DEPTH_COMPONENT;
		case hamon::render::TextureFormat::S8_UINT:
			return GL_STENCIL_INDEX;
		//case hamon::render::TextureFormat::D16_UNORM_S8_UINT:	
		case hamon::render::TextureFormat::D24_UNORM_S8_UINT:
		case hamon::render::TextureFormat::D32_SFLOAT_S8_UINT:
			return GL_DEPTH_STENCIL;
		}
		return 0;
	}

	static GLenum ToGlInternalFormat(render::TextureFormat format)
	{
		switch (format)
		{
		case hamon::render::TextureFormat::R8_UNORM:		return GL_R8;
		case hamon::render::TextureFormat::R8_SNORM:		return GL_R8_SNORM;
		case hamon::render::TextureFormat::R8_UINT:			return GL_R8UI;
		case hamon::render::TextureFormat::R8_SINT:			return GL_R8I;
		case hamon::render::TextureFormat::R8G8_UNORM:		return GL_RG8;
		case hamon::render::TextureFormat::R8G8_SNORM:		return GL_RG8_SNORM;
		case hamon::render::TextureFormat::R8G8_UINT:		return GL_RG8UI;
		case hamon::render::TextureFormat::R8G8_SINT:		return GL_RG8I;
		case hamon::render::TextureFormat::R8G8B8_UNORM:	return GL_RGB8;
		case hamon::render::TextureFormat::R8G8B8_SNORM:	return GL_RGB8_SNORM;
		case hamon::render::TextureFormat::R8G8B8_UINT:		return GL_RGB8UI;
		case hamon::render::TextureFormat::R8G8B8_SINT:		return GL_RGB8I;
		case hamon::render::TextureFormat::B8G8R8_UNORM:	return GL_RGB8;
		case hamon::render::TextureFormat::B8G8R8_SNORM:	return GL_RGB8_SNORM;
		case hamon::render::TextureFormat::B8G8R8_UINT:		return GL_RGB8UI;
		case hamon::render::TextureFormat::B8G8R8_SINT:		return GL_RGB8I;
		case hamon::render::TextureFormat::R8G8B8A8_UNORM:	return GL_RGBA8;
		case hamon::render::TextureFormat::R8G8B8A8_SNORM:	return GL_RGBA8_SNORM;
		case hamon::render::TextureFormat::R8G8B8A8_UINT:	return GL_RGBA8UI;
		case hamon::render::TextureFormat::R8G8B8A8_SINT:	return GL_RGBA8I;
		case hamon::render::TextureFormat::B8G8R8A8_UNORM:	return GL_RGBA8;
		case hamon::render::TextureFormat::B8G8R8A8_SNORM:	return GL_RGBA8_SNORM;
		case hamon::render::TextureFormat::B8G8R8A8_UINT:	return GL_RGBA8UI;
		case hamon::render::TextureFormat::B8G8R8A8_SINT:	return GL_RGBA8I;
		case hamon::render::TextureFormat::R16_UNORM:		return GL_R16;
		case hamon::render::TextureFormat::R16_SNORM:		return GL_R16_SNORM;
		case hamon::render::TextureFormat::R16_UINT:		return GL_R16UI;
		case hamon::render::TextureFormat::R16_SINT:		return GL_R16I;
		case hamon::render::TextureFormat::R16_SFLOAT:		return GL_R16F;
		case hamon::render::TextureFormat::R16G16_UNORM:	return GL_RG16;
		case hamon::render::TextureFormat::R16G16_SNORM:	return GL_RG16_SNORM;
		case hamon::render::TextureFormat::R16G16_UINT:		return GL_RG16UI;
		case hamon::render::TextureFormat::R16G16_SINT:		return GL_RG16I;
		case hamon::render::TextureFormat::R16G16_SFLOAT:	return GL_RG16F;
		case hamon::render::TextureFormat::R16G16B16_UNORM:	return GL_RGB16;
		case hamon::render::TextureFormat::R16G16B16_SNORM:	return GL_RGB16_SNORM;
		case hamon::render::TextureFormat::R16G16B16_UINT:	return GL_RGB16UI;
		case hamon::render::TextureFormat::R16G16B16_SINT:	return GL_RGB16I;
		case hamon::render::TextureFormat::R16G16B16_SFLOAT:return GL_RGB16F;
		case hamon::render::TextureFormat::R16G16B16A16_UNORM:	return GL_RGBA16;
		case hamon::render::TextureFormat::R16G16B16A16_SNORM:	return GL_RGBA16_SNORM;
		case hamon::render::TextureFormat::R16G16B16A16_UINT:	return GL_RGBA16UI;
		case hamon::render::TextureFormat::R16G16B16A16_SINT:	return GL_RGBA16I;
		case hamon::render::TextureFormat::R16G16B16A16_SFLOAT:	return GL_RGBA16F;
		case hamon::render::TextureFormat::R32_UINT:			return GL_R32UI;
		case hamon::render::TextureFormat::R32_SINT:			return GL_R32I;
		case hamon::render::TextureFormat::R32_SFLOAT:			return GL_R32F;
		case hamon::render::TextureFormat::R32G32_UINT:			return GL_RG32UI;
		case hamon::render::TextureFormat::R32G32_SINT:			return GL_RG32I;
		case hamon::render::TextureFormat::R32G32_SFLOAT:		return GL_RG32F;
		case hamon::render::TextureFormat::R32G32B32_UINT:		return GL_RGB32UI;
		case hamon::render::TextureFormat::R32G32B32_SINT:		return GL_RGB32I;
		case hamon::render::TextureFormat::R32G32B32_SFLOAT:	return GL_RGB32F;
		case hamon::render::TextureFormat::R32G32B32A32_UINT:	return GL_RGBA32UI;
		case hamon::render::TextureFormat::R32G32B32A32_SINT:	return GL_RGBA32I;
		case hamon::render::TextureFormat::R32G32B32A32_SFLOAT:	return GL_RGBA32F;
		//case hamon::render::TextureFormat::R64_UINT:			return GL_R64UI;
		//case hamon::render::TextureFormat::R64_SINT:			return GL_R64I;
		//case hamon::render::TextureFormat::R64_SFLOAT:			return GL_R64F;
		//case hamon::render::TextureFormat::R64G64_UINT:			return GL_RG64UI;
		//case hamon::render::TextureFormat::R64G64_SINT:			return GL_RG64I;
		//case hamon::render::TextureFormat::R64G64_SFLOAT:		return GL_RG64F;
		//case hamon::render::TextureFormat::R64G64B64_UINT:		return GL_RGB64UI;
		//case hamon::render::TextureFormat::R64G64B64_SINT:		return GL_RGB64I;
		//case hamon::render::TextureFormat::R64G64B64_SFLOAT:	return GL_RGB64F;
		//case hamon::render::TextureFormat::R64G64B64A64_UINT:	return GL_RGBA64UI;
		//case hamon::render::TextureFormat::R64G64B64A64_SINT:	return GL_RGBA64I;
		//case hamon::render::TextureFormat::R64G64B64A64_SFLOAT:	return GL_RGBA64F;
		case hamon::render::TextureFormat::D16_UNORM:			return GL_DEPTH_COMPONENT16;
		case hamon::render::TextureFormat::X8_D24_UNORM_PACK32:	return GL_DEPTH_COMPONENT24;
		case hamon::render::TextureFormat::D32_SFLOAT:			return GL_DEPTH_COMPONENT32F;
		case hamon::render::TextureFormat::S8_UINT:				return GL_STENCIL_INDEX8;
		//case hamon::render::TextureFormat::D16_UNORM_S8_UINT:	return GL_DEPTH16_STENCIL8;
		case hamon::render::TextureFormat::D24_UNORM_S8_UINT:	return GL_DEPTH24_STENCIL8;
		case hamon::render::TextureFormat::D32_SFLOAT_S8_UINT:	return GL_DEPTH32F_STENCIL8;
		}
		return 0;
	}

	static GLenum ToGlType(render::TextureFormat format)
	{
		switch (format)
		{
		case hamon::render::TextureFormat::R8_UNORM:
		case hamon::render::TextureFormat::R8_UINT:
		case hamon::render::TextureFormat::R8G8_UNORM:
		case hamon::render::TextureFormat::R8G8_UINT:
		case hamon::render::TextureFormat::R8G8B8_UNORM:
		case hamon::render::TextureFormat::R8G8B8_UINT:
		case hamon::render::TextureFormat::B8G8R8_UNORM:
		case hamon::render::TextureFormat::B8G8R8_UINT:
		case hamon::render::TextureFormat::R8G8B8A8_UNORM:
		case hamon::render::TextureFormat::R8G8B8A8_UINT:
		case hamon::render::TextureFormat::B8G8R8A8_UNORM:
		case hamon::render::TextureFormat::B8G8R8A8_UINT:
			return GL_UNSIGNED_BYTE;
		case hamon::render::TextureFormat::R8_SNORM:
		case hamon::render::TextureFormat::R8_SINT:
		case hamon::render::TextureFormat::R8G8_SNORM:
		case hamon::render::TextureFormat::R8G8_SINT:
		case hamon::render::TextureFormat::R8G8B8_SNORM:
		case hamon::render::TextureFormat::R8G8B8_SINT:
		case hamon::render::TextureFormat::B8G8R8_SNORM:
		case hamon::render::TextureFormat::B8G8R8_SINT:
		case hamon::render::TextureFormat::R8G8B8A8_SNORM:
		case hamon::render::TextureFormat::R8G8B8A8_SINT:
		case hamon::render::TextureFormat::B8G8R8A8_SNORM:
		case hamon::render::TextureFormat::B8G8R8A8_SINT:
			return GL_BYTE;
		case hamon::render::TextureFormat::R16_UNORM:
		case hamon::render::TextureFormat::R16_UINT:
		case hamon::render::TextureFormat::R16G16_UNORM:
		case hamon::render::TextureFormat::R16G16_UINT:
		case hamon::render::TextureFormat::R16G16B16_UNORM:
		case hamon::render::TextureFormat::R16G16B16_UINT:
		case hamon::render::TextureFormat::R16G16B16A16_UNORM:
		case hamon::render::TextureFormat::R16G16B16A16_UINT:
			return GL_UNSIGNED_SHORT;
		case hamon::render::TextureFormat::R16_SNORM:
		case hamon::render::TextureFormat::R16_SINT:
		case hamon::render::TextureFormat::R16G16_SNORM:
		case hamon::render::TextureFormat::R16G16_SINT:
		case hamon::render::TextureFormat::R16G16B16_SNORM:
		case hamon::render::TextureFormat::R16G16B16_SINT:
		case hamon::render::TextureFormat::R16G16B16A16_SNORM:
		case hamon::render::TextureFormat::R16G16B16A16_SINT:
			return GL_SHORT;
		case hamon::render::TextureFormat::R16_SFLOAT:
		case hamon::render::TextureFormat::R16G16_SFLOAT:
		case hamon::render::TextureFormat::R16G16B16_SFLOAT:
		case hamon::render::TextureFormat::R16G16B16A16_SFLOAT:
			return GL_FLOAT;
		case hamon::render::TextureFormat::R32_UINT:
		case hamon::render::TextureFormat::R32G32_UINT:
		case hamon::render::TextureFormat::R32G32B32_UINT:
		case hamon::render::TextureFormat::R32G32B32A32_UINT:
			return GL_UNSIGNED_INT;
		case hamon::render::TextureFormat::R32_SINT:
		case hamon::render::TextureFormat::R32G32_SINT:
		case hamon::render::TextureFormat::R32G32B32_SINT:
		case hamon::render::TextureFormat::R32G32B32A32_SINT:
			return GL_INT;
		case hamon::render::TextureFormat::R32_SFLOAT:
		case hamon::render::TextureFormat::R32G32_SFLOAT:
		case hamon::render::TextureFormat::R32G32B32_SFLOAT:
		case hamon::render::TextureFormat::R32G32B32A32_SFLOAT:
			return GL_FLOAT;
		//case hamon::render::TextureFormat::R64_UINT:			
		//case hamon::render::TextureFormat::R64_SINT:			
		//case hamon::render::TextureFormat::R64_SFLOAT:		
		//case hamon::render::TextureFormat::R64G64_UINT:		
		//case hamon::render::TextureFormat::R64G64_SINT:		
		//case hamon::render::TextureFormat::R64G64_SFLOAT:		
		//case hamon::render::TextureFormat::R64G64B64_UINT:	
		//case hamon::render::TextureFormat::R64G64B64_SINT:	
		//case hamon::render::TextureFormat::R64G64B64_SFLOAT:	
		//case hamon::render::TextureFormat::R64G64B64A64_UINT:	
		//case hamon::render::TextureFormat::R64G64B64A64_SINT:	
		//case hamon::render::TextureFormat::R64G64B64A64_SFLOAT:	
		case hamon::render::TextureFormat::D16_UNORM:
		case hamon::render::TextureFormat::X8_D24_UNORM_PACK32:
		case hamon::render::TextureFormat::D32_SFLOAT:
		case hamon::render::TextureFormat::S8_UINT:
			//case hamon::render::TextureFormat::D16_UNORM_S8_UINT:	
		case hamon::render::TextureFormat::D24_UNORM_S8_UINT:
		case hamon::render::TextureFormat::D32_SFLOAT_S8_UINT:
			return GL_FLOAT;	// TODO
		}
		return 0;
	}

public:
	explicit Texture(render::Texture const& texture)
	{
		gl::glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

		auto const mipmap_count = texture.GetMipmapCount();
		auto const format = texture.GetFormat();
		auto width = texture.GetWidth();
		auto height = texture.GetHeight();
		auto data = static_cast<std::uint8_t const*>(texture.GetData());

		auto const gl_format = ToGlFormat(format);
		auto const gl_internal_format = ToGlInternalFormat(format);
		auto const gl_type = ToGlType(format);

		gl::glTextureStorage2D(
			m_id,
			mipmap_count,
			gl_internal_format,
			width,
			height);

		if (data == nullptr)
		{
			return;
		}

		for (std::uint32_t i = 0; i < mipmap_count; ++i)
		{
			gl::glTextureSubImage2D(
				m_id,
				i,
				0,
				0,
				width,
				height,
				gl_format,
				gl_type,
				data);

			data += GetSizeInBytes(format, width, height);
			width  = std::max(width  / 2, 1u);
			height = std::max(height / 2, 1u);
		}
	}

	~Texture()
	{
		::glDeleteTextures(1, &m_id);
	}

	void Bind(::GLint location) const
	{
		gl::glBindTextureUnit(location, m_id);
	}

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_TEXTURE_HPP
