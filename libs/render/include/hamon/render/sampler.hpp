/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler
 */

#ifndef HAMON_RENDER_SAMPLER_HPP
#define HAMON_RENDER_SAMPLER_HPP

#include <hamon/render/filter_mode.hpp>
#include <hamon/render/mipmap_mode.hpp>
#include <hamon/render/sampler_address_mode.hpp>
#include <hamon/render/compare_operation.hpp>
#include <hamon/render/border_color.hpp>

namespace hamon
{

inline namespace render
{

struct Sampler
{
	FilterMode			mag_filter        {FilterMode::Linear};
	FilterMode			min_filter        {FilterMode::Nearest};
	MipmapMode			mip_filter        {MipmapMode::Disable};
	SamplerAddressMode	address_mode_u    {SamplerAddressMode::Repeat};
	SamplerAddressMode	address_mode_v    {SamplerAddressMode::Repeat};
	SamplerAddressMode	address_mode_w    {SamplerAddressMode::Repeat};
	float				mip_lod_bias      {0.0f};
	bool				anisotropy_enable {false};
	float				max_anisotropy    {0.0f};
	bool				compare_enable    {false};
	CompareOperation	compare_operation {CompareOperation::Always};
	float               min_lod           {-1000};
	float               max_lod           {1000};
	BorderColor			border_color      {BorderColor::TransparentBlack};
//	bool				unnormalized_coordinates;
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/detail/hash_combine.hpp>
#include <functional>

namespace std
{

template <>
struct hash<hamon::render::Sampler>
{
	std::size_t operator()(hamon::render::Sampler const& arg) const
	{
		return hamon::render::detail::HashCombine(
			arg.mag_filter,
			arg.min_filter,
			arg.mip_filter,
			arg.address_mode_u,
			arg.address_mode_v,
			arg.address_mode_w,
			arg.mip_lod_bias,
			arg.anisotropy_enable,
			arg.max_anisotropy,
			arg.compare_enable,
			arg.compare_operation,
			arg.min_lod,
			arg.max_lod,
			arg.border_color);
//			arg.unnormalized_coordinates;
	}
};

}	// namespace std

#endif // HAMON_RENDER_SAMPLER_HPP
