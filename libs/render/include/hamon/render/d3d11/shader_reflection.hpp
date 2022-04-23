/**
 *	@file	shader_reflection.hpp
 *
 *	@brief	ShaderReflection
 */

#ifndef HAMON_RENDER_D3D11_SHADER_REFLECTION_HPP
#define HAMON_RENDER_D3D11_SHADER_REFLECTION_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <hamon/render/d3d/d3dcompiler.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

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
	
	::D3D11_SHADER_DESC GetDesc(void) const
	{
		::D3D11_SHADER_DESC desc;
		ThrowIfFailed(m_reflection->GetDesc(&desc));
		return desc;
	}

	::D3D11_SHADER_INPUT_BIND_DESC GetResourceBindingDesc(::UINT resource_index) const
	{
		::D3D11_SHADER_INPUT_BIND_DESC desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(resource_index, &desc));
		return desc;
	}

	::D3D11_SIGNATURE_PARAMETER_DESC GetInputParameterDesc(::UINT parameter_index) const
	{
		::D3D11_SIGNATURE_PARAMETER_DESC desc;
		ThrowIfFailed(m_reflection->GetInputParameterDesc(parameter_index, &desc));
		return desc;
	}
	
	::ID3D11ShaderReflectionConstantBuffer* GetConstantBufferByName(const char* name) const
	{
		return m_reflection->GetConstantBufferByName(name);
	}

private:
	ComPtr<::ID3D11ShaderReflection> m_reflection;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_SHADER_REFLECTION_HPP
