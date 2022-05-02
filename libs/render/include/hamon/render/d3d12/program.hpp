/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_D3D12_PROGRAM_HPP
#define HAMON_RENDER_D3D12_PROGRAM_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/shader.hpp>
#include <hamon/render/d3d12/root_signature.hpp>
#include <hamon/render/d3d12/descriptor_heap.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/program.hpp>
#include <vector>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Program
{
public:
	explicit Program(d3d12::Device* device, render::Program const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			m_shaders.emplace_back(shader);
		}

		for (auto const& shader : m_shaders)
		{
			{
				auto const& descriptor_ranges = shader.GetDescriptorRanges(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
				if (descriptor_ranges.empty())
				{
					continue;
				}

				m_descriptor_heap_types.push_back(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

				::D3D12_ROOT_PARAMETER1 root_param;
				root_param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
				root_param.DescriptorTable.NumDescriptorRanges = static_cast<::UINT>(descriptor_ranges.size());
				root_param.DescriptorTable.pDescriptorRanges   = descriptor_ranges.data();
				root_param.ShaderVisibility = d3d12::ShaderVisibility(shader.GetStage());
				m_root_parameters.push_back(root_param);
			}
			{
				auto const& descriptor_ranges = shader.GetDescriptorRanges(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
				if (descriptor_ranges.empty())
				{
					continue;
				}

				m_descriptor_heap_types.push_back(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

				::D3D12_ROOT_PARAMETER1 root_param;
				root_param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
				root_param.DescriptorTable.NumDescriptorRanges = static_cast<::UINT>(descriptor_ranges.size());
				root_param.DescriptorTable.pDescriptorRanges   = descriptor_ranges.data();
				root_param.ShaderVisibility = d3d12::ShaderVisibility(shader.GetStage());
				m_root_parameters.push_back(root_param);
			}
		}

		m_root_signature = std::make_unique<d3d12::RootSignature>(device, m_root_parameters);
	}

	void LoadUniforms(
		d3d12::Device* device,
		d3d12::ResourceMap* resource_map,
		d3d12::DescriptorHeap* descriptor_heap,
		d3d12::DescriptorHeap* sampler_descriptor_heap,
		d3d12::ConstantBuffer* constant_buffer,
		render::Uniforms const& uniforms)
	{
		for (auto& shader : m_shaders)
		{
			shader.LoadUniforms(device, resource_map, descriptor_heap, sampler_descriptor_heap, constant_buffer, uniforms);
		}
	}

	auto const& GetShaders(void) const
	{
		return m_shaders;
	}

	auto GetRootSignature(void) const
	{
		return m_root_signature->Get();
	}

	auto const& GetRootParameters(void) const
	{
		return m_root_parameters;
	}

	auto const& GetDescriptorHeapTypes(void) const
	{
		return m_descriptor_heap_types;
	}

private:
	std::vector<d3d12::Shader>				m_shaders;
	std::unique_ptr<d3d12::RootSignature>	m_root_signature;
	std::vector<::D3D12_ROOT_PARAMETER1>	m_root_parameters;
	std::vector<::D3D12_DESCRIPTOR_HEAP_TYPE>	m_descriptor_heap_types;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PROGRAM_HPP
