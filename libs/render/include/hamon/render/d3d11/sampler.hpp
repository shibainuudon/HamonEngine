/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler
 */

#ifndef HAMON_RENDER_D3D11_SAMPLER_HPP
#define HAMON_RENDER_D3D11_SAMPLER_HPP

#include <hamon/render/sampler.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d11/filter_mode.hpp>
#include <hamon/render/d3d11/sampler_address_mode.hpp>
#include <hamon/render/d3d11/comparison_func.hpp>
#include <hamon/render/d3d11/border_color.hpp>
#include <hamon/render/d3d11/device.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Sampler
{
public:
	explicit Sampler(d3d11::Device* device, render::Sampler const& sampler)
	{
		::D3D11_SAMPLER_DESC desc;
		desc.Filter         = d3d11::FilterMode(
			sampler.min_filter,
			sampler.mag_filter,
			sampler.mip_filter, 
			sampler.compare_enable);
		desc.AddressU       = d3d11::SamplerAddressMode(sampler.address_mode_u);
		desc.AddressV       = d3d11::SamplerAddressMode(sampler.address_mode_v);
		desc.AddressW       = d3d11::SamplerAddressMode(sampler.address_mode_w);
		desc.MipLODBias     = 0;	// TODO sampler.mip_lod_bias;
		desc.MaxAnisotropy  = 16;	// TODO sampler.max_anisotropy;
		desc.ComparisonFunc = d3d11::ComparisonFunc(sampler.compare_operation);
		auto border_color   = d3d11::BorderColor(sampler.border_color);
		desc.BorderColor[0] = border_color[0];
		desc.BorderColor[1] = border_color[1];
		desc.BorderColor[2] = border_color[2];
		desc.BorderColor[3] = border_color[3];
		desc.MinLOD         = sampler.min_lod;
		desc.MaxLOD         = sampler.max_lod;

		// TODO
		//sampler.anisotropy_enable;

		m_state = device->CreateSamplerState(desc);
	}

	::ID3D11SamplerState* GetState(void) const
	{
		return m_state.Get();
	}

private:
	ComPtr<::ID3D11SamplerState>	m_state;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_SAMPLER_HPP
