/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP
#define HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class RasterizerState
{
public:
	explicit RasterizerState(render::RasterizerState const& rasterizer_state)
	{
		m_desc.FillMode              = ToD3D12FillMode(rasterizer_state.fill_mode);
		m_desc.CullMode              = ToD3D12CullMode(rasterizer_state.cull_mode);
		m_desc.FrontCounterClockwise = rasterizer_state.front_face == FrontFace::CounterClockwise;
		m_desc.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
		m_desc.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		m_desc.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		m_desc.DepthClipEnable       = TRUE;
		m_desc.MultisampleEnable     = FALSE;
		m_desc.AntialiasedLineEnable = FALSE;
		m_desc.ForcedSampleCount     = 0;
		m_desc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}
	
	::D3D12_RASTERIZER_DESC const& Get(void) const { return m_desc; }

private:
	static ::D3D12_FILL_MODE ToD3D12FillMode(render::FillMode fill_mode)
	{
		switch (fill_mode)
		{
		case render::FillMode::Solid:		return D3D12_FILL_MODE_SOLID;
		case render::FillMode::Wireframe:	return D3D12_FILL_MODE_WIREFRAME;
		}
		return D3D12_FILL_MODE_SOLID;
	}

	static ::D3D12_CULL_MODE ToD3D12CullMode(render::CullMode cull_mode)
	{
		switch (cull_mode)
		{
		case render::CullMode::None:	return D3D12_CULL_MODE_NONE;
		case render::CullMode::Front:	return D3D12_CULL_MODE_FRONT;
		case render::CullMode::Back:	return D3D12_CULL_MODE_BACK;
		}
		return D3D12_CULL_MODE_NONE;
	}

private:
	::D3D12_RASTERIZER_DESC	m_desc{};
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_RASTERIZER_STATE_HPP
