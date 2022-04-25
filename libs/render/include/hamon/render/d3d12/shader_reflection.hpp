/**
 *	@file	shader_reflection.hpp
 *
 *	@brief	ShaderReflection
 */

#ifndef HAMON_RENDER_D3D12_SHADER_REFLECTION_HPP
#define HAMON_RENDER_D3D12_SHADER_REFLECTION_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/d3d12shader.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class ShaderReflectionVariable
{
public:
	explicit ShaderReflectionVariable(
		::ID3D12ShaderReflectionVariable* variable)
		: m_variable(variable)
	{}

	auto GetDesc() const
	{
		::D3D12_SHADER_VARIABLE_DESC desc;
		ThrowIfFailed(m_variable->GetDesc(&desc));
		return desc;
	}

private:
	::ID3D12ShaderReflectionVariable*	m_variable;
};

class ShaderReflectionConstantBuffer
{
public:
	explicit ShaderReflectionConstantBuffer(
		::ID3D12ShaderReflectionConstantBuffer*	constant_buffer)
		: m_constant_buffer(constant_buffer)
	{
	}

	auto GetDesc(void) const
	{
		::D3D12_SHADER_BUFFER_DESC desc;
		ThrowIfFailed(m_constant_buffer->GetDesc(&desc));
		return desc;
	}

	auto GetVariableByIndex(::UINT index) const
	{
		return ShaderReflectionVariable
		{
			m_constant_buffer->GetVariableByIndex(index)
		};
	}

	auto GetVariableByName(::LPCSTR Name) const
	{
		return ShaderReflectionVariable
		{
			m_constant_buffer->GetVariableByName(Name)
		};
	}

private:
	::ID3D12ShaderReflectionConstantBuffer*	m_constant_buffer;
};

class ShaderReflection
{
public:
	explicit ShaderReflection(::ID3DBlob* micro_code)
	{
		ThrowIfFailed(::D3DReflect(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			IID_PPV_ARGS(&m_reflection)));
	}
	
	auto GetDesc(void) const
	{
		::D3D12_SHADER_DESC desc;
		ThrowIfFailed(m_reflection->GetDesc(&desc));
		return desc;
	}

	auto GetResourceBindingDesc(::UINT resource_index) const
	{
		::D3D12_SHADER_INPUT_BIND_DESC desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(resource_index, &desc));
		return desc;
	}

	auto GetConstantBufferByName(const char* name) const
	{
		return ShaderReflectionConstantBuffer
		{
			m_reflection->GetConstantBufferByName(name)
		};
	}

private:
	ComPtr<::ID3D12ShaderReflection> m_reflection;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SHADER_REFLECTION_HPP
