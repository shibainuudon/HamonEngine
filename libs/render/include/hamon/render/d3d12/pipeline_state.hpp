﻿/**
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
#include <hamon/render/d3d12/rasterizer_state.hpp>
#include <hamon/render/primitive_topology.hpp>
#include <hamon/render/rasterizer_state.hpp>
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
		d3d12::InputLayout const& input_layout,
		d3d12::RootSignature const& root_signature,
		std::vector<d3d12::Shader*>	shaders,
		render::PrimitiveTopology primitive_topology,
		render::RasterizerState const& rasterizer_state)
	{
		::D3D12_BLEND_DESC blend_desc {};
		blend_desc.AlphaToCoverageEnable  = FALSE;
		blend_desc.IndependentBlendEnable = FALSE;
		for (auto& rt : blend_desc.RenderTarget)
		{
			rt.BlendEnable = FALSE;
			rt.LogicOpEnable = FALSE;
			//rt.SrcBlend;
			//rt.DestBlend;
			//rt.BlendOp;
			//rt.SrcBlendAlpha;
			//rt.DestBlendAlpha;
			//rt.BlendOpAlpha;
			//rt.LogicOp;
			rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		}

		::D3D12_DEPTH_STENCIL_DESC depth_stencil_desc {};
		depth_stencil_desc.DepthEnable = FALSE;
		//depth_stencil_desc.DepthWriteMask;
		//depth_stencil_desc.DepthFunc;
		depth_stencil_desc.StencilEnable = FALSE;
		//depth_stencil_desc.StencilReadMask;
		//depth_stencil_desc.StencilWriteMask;
		//depth_stencil_desc.FrontFace;
		//depth_stencil_desc.BackFace;

		::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
		desc.pRootSignature        = root_signature.Get();
//		desc.StreamOutput;
		desc.BlendState            = blend_desc;
		desc.SampleMask            = UINT_MAX;
		desc.RasterizerState       = d3d12::RasterizerState(rasterizer_state).Get();
		desc.DepthStencilState     = depth_stencil_desc;
		desc.InputLayout           = input_layout.Get();
//		desc.IBStripCutValue;
		desc.PrimitiveTopologyType = ToD3D12PrimitiveTopologyType(primitive_topology);
		desc.NumRenderTargets      = 1;
		desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
//		desc.DSVFormat;
		desc.SampleDesc.Count      = 1;
//		desc.NodeMask;
//		desc.CachedPSO;
//		desc.Flags;

		for (auto const& shader : shaders)
		{
			switch (shader->GetStage())
			{
			case render::ShaderStage::Vertex:   desc.VS = shader->GetBytecode(); break;
			case render::ShaderStage::Hull:     desc.HS = shader->GetBytecode(); break;
			case render::ShaderStage::Domain:   desc.DS = shader->GetBytecode(); break;
			case render::ShaderStage::Geometry: desc.GS = shader->GetBytecode(); break;
			case render::ShaderStage::Pixel:    desc.PS = shader->GetBytecode(); break;
			case render::ShaderStage::Compute:  break;
			}
		}

		m_pipeline_state = device->CreateGraphicsPipelineState(&desc);
	}
	
	::ID3D12PipelineState* Get(void) const { return m_pipeline_state.Get(); }

private:
	::D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopologyType(
		render::PrimitiveTopology primitive_topology)
	{
		switch (primitive_topology)
		{
		case render::PrimitiveTopology::Points:		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
		case render::PrimitiveTopology::Lines:		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		case render::PrimitiveTopology::Triangles:	return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		}
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
	}

private:
	ComPtr<::ID3D12PipelineState>	m_pipeline_state;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PIPELINE_STATE_HPP
