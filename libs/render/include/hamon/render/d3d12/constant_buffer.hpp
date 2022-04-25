/**
 *	@file	constant_buffer.hpp
 *
 *	@brief	ConstantBuffer
 */

#ifndef HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP
#define HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/descriptor_heap.hpp>
#include <hamon/render/d3d12/resource.hpp>
#include <hamon/render/d3d12/shader_reflection.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/d3d12shader.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <string>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class ConstantBuffer
{
private:
	static ::UINT RoundUp(::UINT x, ::UINT align)
	{
		return (x + (align - 1)) & ~(align - 1);
	}

public:
	explicit ConstantBuffer(
		d3d12::Device* device,
		d3d12::ShaderReflectionConstantBuffer const& reflection)
		: ConstantBuffer(device, reflection, reflection.GetDesc())
	{}

private:
	explicit ConstantBuffer(
		d3d12::Device* device,
		d3d12::ShaderReflectionConstantBuffer const& reflection,
		::D3D12_SHADER_BUFFER_DESC const& desc)
		: m_name(desc.Name)
		, m_size(RoundUp(desc.Size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT))
		, m_resource(device, m_size, nullptr)
	{
		for (::UINT i = 0; i < desc.Variables; ++i)
		{
			auto const variable_desc = reflection.GetVariableByIndex(i).GetDesc();

			if (variable_desc.uFlags & D3D_SVF_USED)
			{
				m_variables.emplace_back(
					variable_desc.Name,
					variable_desc.StartOffset,
					variable_desc.Size);
			}
		}

		m_mapped_resource = static_cast<std::uint8_t*>(m_resource.Map(0, nullptr));
	}

public:
	void LoadUniforms(
		d3d12::Device* device,
		d3d12::DescriptorHeap* descriptor_heap,
		render::Uniforms const& uniforms)
	{
		for (auto const& variable : m_variables)
		{
			auto uniform = uniforms[variable.name];
			if (uniform != nullptr)
			{
				std::memcpy(
					&m_mapped_resource[variable.start_offset],
					uniform->GetData(),
					variable.size);
			}
		}

		::D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
		desc.BufferLocation = m_resource.Get()->GetGPUVirtualAddress();
		desc.SizeInBytes = m_size;

		auto dest = descriptor_heap->AssignCpuDescriptorHandle();
		device->CreateConstantBufferView(&desc, dest);
	}

private:
	struct Variable
	{
		std::string name;
		::UINT		start_offset;
		::UINT		size;
	};

	std::string				m_name;
	::UINT					m_size;
	std::vector<Variable>	m_variables;
	d3d12::Resource			m_resource;
	std::uint8_t*			m_mapped_resource;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_CONSTANT_BUFFER_HPP
