/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_D3D12_SHADER_HPP
#define HAMON_RENDER_D3D12_SHADER_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/d3dcompiler.hpp>
#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/shader.hpp>

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
	}
	
	render::ShaderStage	GetStage(void) const { return m_stage; }

	::D3D12_SHADER_BYTECODE GetBytecode(void) const
	{
		return
		{
			m_micro_code->GetBufferPointer(),
			m_micro_code->GetBufferSize(),
		};
	}

private:
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
	render::ShaderStage	m_stage;
	ComPtr<::ID3DBlob>	m_micro_code;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SHADER_HPP
