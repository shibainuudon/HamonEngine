/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler
 */

#ifndef HAMON_RENDER_D3D12_SAMPLER_HPP
#define HAMON_RENDER_D3D12_SAMPLER_HPP

#include <hamon/render/sampler.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/filter_mode.hpp>
#include <hamon/render/d3d12/sampler_address_mode.hpp>
#include <hamon/render/d3d12/comparison_func.hpp>
#include <hamon/render/d3d12/border_color.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Sampler
{
public:
	explicit Sampler(render::Sampler const& sampler)
	{
		m_desc.Filter         = d3d12::FilterMode(
			sampler.min_filter,
			sampler.mag_filter,
			sampler.mip_filter, 
			sampler.compare_enable);
		m_desc.AddressU       = d3d12::SamplerAddressMode(sampler.address_mode_u);
		m_desc.AddressV       = d3d12::SamplerAddressMode(sampler.address_mode_v);
		m_desc.AddressW       = d3d12::SamplerAddressMode(sampler.address_mode_w);
		m_desc.MipLODBias     = 0;	// TODO sampler.mip_lod_bias;
		m_desc.MaxAnisotropy  = 16;	// TODO sampler.max_anisotropy;
		m_desc.ComparisonFunc = d3d12::ComparisonFunc(sampler.compare_operation);
		auto border_color   = d3d12::BorderColor(sampler.border_color);
		m_desc.BorderColor[0] = border_color[0];
		m_desc.BorderColor[1] = border_color[1];
		m_desc.BorderColor[2] = border_color[2];
		m_desc.BorderColor[3] = border_color[3];
		m_desc.MinLOD         = sampler.min_lod;
		m_desc.MaxLOD         = sampler.max_lod;

		// TODO
		//sampler.anisotropy_enable;
	}
	
	::D3D12_SAMPLER_DESC const& GetDesc(void) const
	{
		return m_desc;
	}

private:
	::D3D12_SAMPLER_DESC	m_desc;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SAMPLER_HPP
