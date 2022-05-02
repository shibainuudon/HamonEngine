/**
 *	@file	sampler_descriptor.hpp
 *
 *	@brief	SamplerDescriptor
 */

#ifndef HAMON_RENDER_D3D12_SAMPLER_DESCRIPTOR_HPP
#define HAMON_RENDER_D3D12_SAMPLER_DESCRIPTOR_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/resource_map.hpp>
#include <string>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class SamplerDescriptor
{
public:
	explicit SamplerDescriptor(::D3D12_SHADER_INPUT_BIND_DESC const& desc)
		: m_name(desc.Name)
	{
	}

	void LoadUniforms(
		d3d12::Device* device,
		d3d12::ResourceMap* resource_map,
		d3d12::DescriptorHeap* descriptor_heap,
		render::Uniforms const& uniforms)
	{
		auto uniform = uniforms[m_name];
		if (uniform == nullptr)
		{
			return;
		}

		using type = render::Sampler;
		auto data = static_cast<type const*>(uniform->GetData());
		auto sampler = resource_map->GetSampler(*data);
		device->CreateSampler(
			sampler->GetDesc(),
			descriptor_heap->AssignCpuDescriptorHandle());
	}

private:
	std::string		m_name;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SAMPLER_DESCRIPTOR_HPP
