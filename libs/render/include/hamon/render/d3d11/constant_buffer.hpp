/**
 *	@file	constant_buffer.hpp
 *
 *	@brief	ConstantBuffer
 */

#ifndef HAMON_RENDER_D3D11_CONSTANT_BUFFER_HPP
#define HAMON_RENDER_D3D11_CONSTANT_BUFFER_HPP

#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/buffer.hpp>
#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d/d3d11shader.hpp>
#include <hamon/render/uniforms.hpp>
#include <cstddef>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class ConstantBuffer
{
public:
	ConstantBuffer(Device* device,
		::ID3D11ShaderReflectionConstantBuffer* reflection,
		::D3D11_SHADER_BUFFER_DESC const& desc,
		::UINT bind_point)
		: m_buffer(
			device,
			desc.Size,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_CONSTANT_BUFFER,
			nullptr)
		, m_buffer_data(desc.Size)
		, m_bind_point(bind_point)
	{
		for (::UINT i = 0; i < desc.Variables; ++i)
		{
			auto variable = reflection->GetVariableByIndex(i);
			::D3D11_SHADER_VARIABLE_DESC variable_desc;
			variable->GetDesc(&variable_desc);

			if (variable_desc.uFlags & D3D_SVF_USED)
			{
				m_variables.emplace_back(
					variable_desc.Name,
					variable_desc.StartOffset,
					variable_desc.Size);
			}
		}
	}

	void LoadUniforms(d3d11::DeviceContext* device_context, render::Uniforms const& uniforms)
	{
		for (auto const& variable : m_variables)
		{
			auto uniform = uniforms[variable.name];
			if (uniform != nullptr)
			{
				std::memcpy(
					&m_buffer_data[variable.start_offset],
					uniform->GetData(),
					variable.size);
			}
		}
		
		device_context->UpdateSubresource(
			m_buffer.Get(),
			0,
			nullptr,
			m_buffer_data.data(),
			0,
			0);
	}

	::ID3D11Buffer* GetBuffer(void) const
	{
		return m_buffer.Get();
	}
	
	::UINT GetBindPoint(void) const
	{
		return m_bind_point;
	}

private:
	struct Variable
	{
		std::string name;
		::UINT		start_offset;
		::UINT		size;
	};

	d3d11::Buffer			m_buffer;
	std::vector<std::byte>	m_buffer_data;
	std::vector<Variable>	m_variables;
	::UINT					m_bind_point;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_CONSTANT_BUFFER_HPP
