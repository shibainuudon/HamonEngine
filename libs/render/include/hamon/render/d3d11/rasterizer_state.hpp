/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState
 */

#ifndef HAMON_RENDER_D3D11_RASTERIZER_STATE_HPP
#define HAMON_RENDER_D3D11_RASTERIZER_STATE_HPP

#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class RasterizerState
{
public:
	explicit RasterizerState(render::RasterizerState const& state)
	{
		m_desc.FillMode              = ToD3D11FillMode(state.fill_mode);
		m_desc.CullMode              = ToD3D11CullMode(state.cull_mode);
		m_desc.FrontCounterClockwise = (state.front_face == FrontFace::CounterClockwise);
		m_desc.DepthBias             = D3D11_DEFAULT_DEPTH_BIAS;
		m_desc.DepthBiasClamp        = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
		m_desc.SlopeScaledDepthBias  = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		m_desc.DepthClipEnable       = FALSE;
		m_desc.ScissorEnable         = FALSE;
		m_desc.MultisampleEnable     = FALSE;
		m_desc.AntialiasedLineEnable = FALSE;
	}
	
	::D3D11_RASTERIZER_DESC const& Get(void) const { return m_desc; }

private:
	static ::D3D11_FILL_MODE ToD3D11FillMode(render::FillMode fill_mode)
	{
		switch (fill_mode)
		{
		case render::FillMode::Solid:     return D3D11_FILL_SOLID;
		case render::FillMode::Wireframe: return D3D11_FILL_WIREFRAME;
		}
		return D3D11_FILL_SOLID;
	}

	static ::D3D11_CULL_MODE ToD3D11CullMode(render::CullMode cull_mode)
	{
		switch (cull_mode)
		{
		case render::CullMode::None:  return D3D11_CULL_NONE;
		case render::CullMode::Front: return D3D11_CULL_FRONT;
		case render::CullMode::Back:  return D3D11_CULL_BACK;
		}
		return D3D11_CULL_NONE;
	}

private:
	::D3D11_RASTERIZER_DESC	m_desc{};
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_rasterizer_state_HPP
