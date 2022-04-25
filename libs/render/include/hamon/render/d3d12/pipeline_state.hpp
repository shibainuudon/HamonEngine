/**
 *	@file	pipeline_state.hpp
 *
 *	@brief	PipelineState
 */

#ifndef HAMON_RENDER_D3D12_PIPELINE_STATE_HPP
#define HAMON_RENDER_D3D12_PIPELINE_STATE_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d/com_ptr.hpp>
//#include <hamon/render/d3d/throw_if_failed.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/input_layout.hpp>
#include <hamon/render/d3d12/root_signature.hpp>
#include <hamon/render/d3d12/shader.hpp>
#include <hamon/render/d3d12/program.hpp>
#include <hamon/render/d3d12/rasterizer_state.hpp>
#include <hamon/render/d3d12/blend_state.hpp>
#include <hamon/render/d3d12/depth_stencil_state.hpp>
#include <hamon/render/d3d12/primitive_topology_type.hpp>
#include <hamon/render/d3d12/geometry.hpp>
#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/blend_state.hpp>
#include <hamon/render/depth_stencil_state.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class PipelineState
{
public:
	PipelineState(
		d3d12::Device* device,
		d3d12::Geometry const& geometry,
		d3d12::Program const& program,
		render::RenderState const& render_state)
	{
		::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
		desc.pRootSignature        = program.GetRootSignature();
//		desc.StreamOutput;
		desc.BlendState            = d3d12::BlendState(render_state.blend_state);
		desc.SampleMask            = UINT_MAX;
		desc.RasterizerState       = d3d12::RasterizerState(render_state.rasterizer_state);
		desc.DepthStencilState     = d3d12::DepthStencilState(render_state.depth_stencil_state);
		desc.InputLayout           = geometry.GetInputLayout().GetDesc();
//		desc.IBStripCutValue;
		desc.PrimitiveTopologyType = geometry.GetPrimitiveTopologyType();
		desc.NumRenderTargets      = 1;
		desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
//		desc.DSVFormat;
		desc.SampleDesc.Count      = 1;
//		desc.NodeMask;
//		desc.CachedPSO;
//		desc.Flags;

		for (auto const& shader : program.GetShaders())
		{
			switch (shader.GetStage())
			{
			case render::ShaderStage::Vertex:   desc.VS = shader.GetBytecode(); break;
			case render::ShaderStage::Hull:     desc.HS = shader.GetBytecode(); break;
			case render::ShaderStage::Domain:   desc.DS = shader.GetBytecode(); break;
			case render::ShaderStage::Geometry: desc.GS = shader.GetBytecode(); break;
			case render::ShaderStage::Pixel:    desc.PS = shader.GetBytecode(); break;
			case render::ShaderStage::Compute:  break;
			}
		}

		m_pipeline_state = device->CreateGraphicsPipelineState(&desc);
	}
	
	::ID3D12PipelineState* Get(void) const { return m_pipeline_state.Get(); }

private:
	ComPtr<::ID3D12PipelineState>	m_pipeline_state;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PIPELINE_STATE_HPP
