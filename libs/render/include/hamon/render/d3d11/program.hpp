/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_D3D11_PROGRAM_HPP
#define HAMON_RENDER_D3D11_PROGRAM_HPP

#include <hamon/render/program.hpp>
#include <hamon/render/shader_stage.hpp>
#include <hamon/render/d3d11/shader.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <memory>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Program
{
public:
	explicit Program(Device* device, render::Program const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			auto d3d11_shader = CreateShader(shader.GetStage());
			d3d11_shader->Create(device, shader);
			m_shaders.push_back(std::move(d3d11_shader));
		}
	}

private:
	static std::unique_ptr<d3d11::Shader>
	CreateShader(ShaderStage stage)
	{
		switch (stage)
		{
		case render::ShaderStage::Compute: return std::make_unique<d3d11::ComputeShader>();
		case render::ShaderStage::Vertex:  return std::make_unique<d3d11::VertexShader>();
		case render::ShaderStage::Hull:    return std::make_unique<d3d11::HullShader>();
		case render::ShaderStage::Domain:  return std::make_unique<d3d11::DomainShader>();
		case render::ShaderStage::Geometry:return std::make_unique<d3d11::GeometryShader>();
		case render::ShaderStage::Pixel:   return std::make_unique<d3d11::PixelShader>();
		}
		return {};
	}

public:
	void Bind(DeviceContext* device_context)
	{
		for (auto const& shader : m_shaders)
		{
			shader->Bind(device_context);
		}
	}

	void LoadUniforms(DeviceContext* device_context, render::Uniforms const& uniforms)
	{
		for (auto const& shader : m_shaders)
		{
			shader->LoadUniforms(device_context, uniforms);
		}
	}

private:
	std::vector<std::unique_ptr<d3d11::Shader>>	m_shaders;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_PROGRAM_HPP
