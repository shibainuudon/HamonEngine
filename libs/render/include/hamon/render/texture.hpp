/**
 *	@file	texture.hpp
 *
 *	@brief	Texture
 */

#ifndef HAMON_RENDER_TEXTURE_HPP
#define HAMON_RENDER_TEXTURE_HPP

#include <hamon/render/texture_format.hpp>
#include <hamon/render/detail/identifiable.hpp>
#include <hamon/render/detail/pixels.hpp>
#include <memory>
#include <cstdint>
#include <cstddef>

namespace hamon
{

inline namespace render
{

class Texture : public detail::Identifiable
{
public:
	explicit Texture(
		TextureFormat format,
		std::uint32_t width,
		std::uint32_t height,
		std::uint32_t mipmap_count,
		void const* data)
		: m_format(format)
		, m_width(width)
		, m_height(height)
		, m_mipmap_count(mipmap_count)
	{
		auto const bytes = GetMipmappedSizeInBytes(
			format, width, height, mipmap_count);
		m_pixels = std::make_shared<detail::Pixels>(bytes, data);
	}
	
	TextureFormat GetFormat(void) const { return m_format; }
	std::uint32_t GetWidth(void) const { return m_width; }
	std::uint32_t GetHeight(void) const { return m_height; }
	std::uint32_t GetMipmapCount(void) const { return m_mipmap_count; }
	void const* GetData(void) const { return m_pixels->GetData(); }

private:
	TextureFormat					m_format;
	std::uint32_t					m_width;
	std::uint32_t					m_height;
	std::uint32_t					m_mipmap_count;
	std::shared_ptr<detail::Pixels>	m_pixels;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_TEXTURE_HPP
