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
			switch (shader.GetStage())
			{
			case render::ShaderStage::Compute:
				m_shaders.push_back(std::make_unique<d3d11::ComputeShader>(device, shader));
				break;
			case render::ShaderStage::Vertex:
				m_shaders.push_back(std::make_unique<d3d11::VertexShader>(device, shader));
				break;
			case render::ShaderStage::Hull:
				m_shaders.push_back(std::make_unique<d3d11::HullShader>(device, shader));
				break;
			case render::ShaderStage::Domain:
				m_shaders.push_back(std::make_unique<d3d11::DomainShader>(device, shader));
				break;
			case render::ShaderStage::Geometry:
				m_shaders.push_back(std::make_unique<d3d11::GeometryShader>(device, shader));
				break;
			case render::ShaderStage::Pixel:
				m_shaders.push_back(std::make_unique<d3d11::PixelShader>(device, shader));
				break;
			}
		}
	}

	void Bind(DeviceContext* device_context)
	{
		for (auto const& shader : m_shaders)
		{
			shader->Bind(device_context);
		}
	}

private:
	std::vector<std::unique_ptr<d3d11::Shader>>	m_shaders;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_PROGRAM_HPP
