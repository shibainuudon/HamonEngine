/**
 *	@file	constant_buffer_descriptor.hpp
 *
 *	@brief	ConstantBufferDescriptor
 */

#ifndef HAMON_RENDER_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP
#define HAMON_RENDER_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP

#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/descriptor_heap.hpp>
#include <hamon/render/d3d12/resource.hpp>
#include <hamon/render/d3d12/shader_reflection.hpp>
#include <hamon/render/d3d12/constant_buffer.hpp>
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

class ConstantBufferDescriptor
{
private:
	static ::UINT RoundUp(::UINT x, ::UINT align)
	{
		return (x + (align - 1)) & ~(align - 1);
	}

public:
	explicit ConstantBufferDescriptor(
		d3d12::ShaderReflectionConstantBuffer const& reflection)
		: ConstantBufferDescriptor(reflection, reflection.GetDesc())
	{}

private:
	explicit ConstantBufferDescriptor(
		d3d12::ShaderReflectionConstantBuffer const& reflection,
		::D3D12_SHADER_BUFFER_DESC const& desc)
		: m_name(desc.Name)
		, m_size(RoundUp(desc.Size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT))
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
	}

public:
	void LoadUniforms(
		d3d12::Device* device,
		d3d12::DescriptorHeap* descriptor_heap,
		d3d12::ConstantBuffer* constant_buffer,
		render::Uniforms const& uniforms)
	{
		auto mem = constant_buffer->Allocate(m_size);

		for (auto const& variable : m_variables)
		{
			auto uniform = uniforms[variable.name];
			if (uniform != nullptr)
			{
				std::memcpy(
					&mem.mapped_resource[variable.start_offset],
					uniform->GetData(),
					variable.size);
			}
		}

		::D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
		desc.BufferLocation = mem.gpu_virtual_address;
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
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP
