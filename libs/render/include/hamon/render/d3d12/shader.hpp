/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_D3D12_SHADER_HPP
#define HAMON_RENDER_D3D12_SHADER_HPP

#include <hamon/render/d3d12/shader_reflection.hpp>
#include <hamon/render/d3d12/shader_visibility.hpp>
#include <hamon/render/d3d12/constant_buffer_descriptor.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/descriptor_heap.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/d3dcompiler.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/shader.hpp>
#include <hamon/render/uniforms.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Shader
{
public:
	explicit Shader(render::Shader const& shader)
		: m_stage(shader.GetStage())
	{
		m_micro_code = Compile(shader);
		d3d12::ShaderReflection reflection(m_micro_code.Get());
		CreateDescriptorRanges(reflection);
		CreateConstantBufferDescriptors(reflection);
	}

	void LoadUniforms(
		d3d12::Device* device,
		d3d12::DescriptorHeap* descriptor_heap,
		d3d12::ConstantBuffer* constant_buffer,
		render::Uniforms const& uniforms)
	{
		for (auto& constant_buffer_descriptor : m_constant_buffer_descriptors)
		{
			constant_buffer_descriptor.LoadUniforms(device, descriptor_heap, constant_buffer, uniforms);
		}
	}

	render::ShaderStage	GetStage(void) const
	{
		return m_stage;
	}

	::D3D12_SHADER_BYTECODE GetBytecode(void) const
	{
		return
		{
			m_micro_code->GetBufferPointer(),
			m_micro_code->GetBufferSize(),
		};
	}

	auto const& GetDescriptorRanges(::D3D12_DESCRIPTOR_HEAP_TYPE heap_type) const
	{
		return m_descriptor_ranges[heap_type];
	}

private:
	static ::D3D12_DESCRIPTOR_HEAP_TYPE
	ToDescriptorHeapType(::D3D12_DESCRIPTOR_RANGE_TYPE range_type)
	{
		switch (range_type)
		{
		case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
			return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
		case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
		case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
		case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
			return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		}
		return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	}

	static ::D3D12_DESCRIPTOR_RANGE_TYPE
	ToDescriptorRangeType(::D3D_SHADER_INPUT_TYPE type)
	{
		switch (type)
		{
		case D3D_SIT_CBUFFER: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		case D3D_SIT_TEXTURE: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		case D3D_SIT_SAMPLER: return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
		}
		return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	}

	void CreateDescriptorRanges(d3d12::ShaderReflection const& reflection)
	{
		auto const desc = reflection.GetDesc();
		for (::UINT i = 0; i < desc.BoundResources; ++i)
		{
			auto const input_bind_desc = reflection.GetResourceBindingDesc(i);

			auto const range_type = ToDescriptorRangeType(input_bind_desc.Type);
			auto const heap_type = ToDescriptorHeapType(range_type);

			::D3D12_DESCRIPTOR_RANGE1 descriptor_range;
			descriptor_range.RangeType          = range_type;
			descriptor_range.NumDescriptors     = 1;
			descriptor_range.BaseShaderRegister = input_bind_desc.BindPoint;
			descriptor_range.RegisterSpace      = input_bind_desc.Space;
			descriptor_range.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;
			descriptor_range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			m_descriptor_ranges[heap_type].push_back(descriptor_range);
		}
	}

	void CreateConstantBufferDescriptors(d3d12::ShaderReflection const& reflection)
	{
		auto const shader_desc = reflection.GetDesc();

		for (::UINT i = 0; i < shader_desc.BoundResources; ++i)
		{
			auto const input_bind_desc = reflection.GetResourceBindingDesc(i);

			switch (input_bind_desc.Type)
			{
			case D3D_SIT_CBUFFER:
				{
					auto cbuffer = reflection.GetConstantBufferByName(input_bind_desc.Name);
					m_constant_buffer_descriptors.emplace_back(cbuffer);
				}
				break;
			}
		}
	}

	static const char* GetTargetString(render::ShaderStage stage)
	{
		switch (stage)
		{
		case render::ShaderStage::Compute:	return "cs_5_0";
		case render::ShaderStage::Vertex:	return "vs_5_0";
		case render::ShaderStage::Hull:		return "hs_5_0";
		case render::ShaderStage::Domain:	return "ds_5_0";
		case render::ShaderStage::Geometry:	return "gs_5_0";
		case render::ShaderStage::Pixel:	return "ps_5_0";
		}
		return "";
	}

	static ComPtr<::ID3DBlob> Compile(render::Shader const& shader)
	{
		const char* target = GetTargetString(shader.GetStage());
		::UINT flags1 =
			D3DCOMPILE_DEBUG |
			0;

		ComPtr<::ID3DBlob>	micro_code;
		ComPtr<::ID3DBlob>	error_msgs;
		auto const hr = ::D3DCompile(
			shader.GetSource().c_str(),
			shader.GetSource().size(),
			nullptr,	// source_name
			nullptr,	// defines
			nullptr,	// include
			"main",
			target,
			flags1,
			0,			// flags2
			&micro_code,
			&error_msgs);

		if (error_msgs)
		{
			std::cout << static_cast<const char*>(error_msgs->GetBufferPointer()) << std::endl;
		}

		if (FAILED(hr))
		{
			return {};
		}

		return micro_code;
	}

private:
	render::ShaderStage								m_stage;
	ComPtr<::ID3DBlob>								m_micro_code;
	std::vector<::D3D12_DESCRIPTOR_RANGE1>			m_descriptor_ranges[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	std::vector<d3d12::ConstantBufferDescriptor>	m_constant_buffer_descriptors;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SHADER_HPP
