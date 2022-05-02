/**
 *	@file	texture.hpp
 *
 *	@brief	Texture
 */

#ifndef HAMON_RENDER_D3D11_TEXTURE_HPP
#define HAMON_RENDER_D3D11_TEXTURE_HPP

#include <hamon/render/texture.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/texture_format.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Texture
{
public:
	explicit Texture(d3d11::Device* device, render::Texture const& texture)
	{
		::D3D11_TEXTURE2D_DESC desc;
		desc.Width              = texture.GetWidth();
		desc.Height             = texture.GetHeight();
		desc.MipLevels          = texture.GetMipmapCount();
		desc.ArraySize          = 1;
		desc.Format             = d3d11::TextureFormat(texture.GetFormat());
		desc.SampleDesc.Count   = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage              = D3D11_USAGE_DEFAULT;
		desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags     = 0;
		desc.MiscFlags          = 0;

		auto const format = texture.GetFormat();
		auto width  = texture.GetWidth();
		auto height = texture.GetHeight();
		auto data   = static_cast<std::uint8_t const*>(texture.GetData());

		std::vector<::D3D11_SUBRESOURCE_DATA> initial_data;
		for (std::uint32_t i = 0; i < texture.GetMipmapCount(); ++i)
		{
			::D3D11_SUBRESOURCE_DATA subresource_data;
			subresource_data.pSysMem = data;
			subresource_data.SysMemPitch = static_cast<::UINT>(GetBytesPerPixel(format) * width);
			subresource_data.SysMemSlicePitch = 0;

			initial_data.push_back(subresource_data);

			data += GetSizeInBytes(format, width, height);
			width  = std::max(width  / 2, 1u);
			height = std::max(height / 2, 1u);
		}

		m_texture = device->CreateTexture2D(desc, initial_data.data());

		{
			::D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
		    srv_desc.Format                    = desc.Format;
			srv_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
			srv_desc.Texture2D.MostDetailedMip = 0;
			srv_desc.Texture2D.MipLevels       = desc.MipLevels;
			m_shader_resource_view = device->CreateShaderResourceView(m_texture.Get(), srv_desc);
		}
	}

	::ID3D11ShaderResourceView* GetShaderResourceView(void) const
	{
		return m_shader_resource_view.Get();
	}

private:
	ComPtr<::ID3D11Texture2D>	m_texture;
	ComPtr<::ID3D11ShaderResourceView>	m_shader_resource_view;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_TEXTURE_HPP
