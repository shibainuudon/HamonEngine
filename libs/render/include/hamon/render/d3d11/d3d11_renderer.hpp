/**
 *	@file	d3d11_renderer.hpp
 *
 *	@brief	D3D11Renderer
 */

#ifndef HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
#define HAMON_RENDER_D3D11_D3D11_RENDERER_HPP

#include <hamon/render/renderer.hpp>
#include <hamon/render/geometry.hpp>
#include <hamon/render/shader.hpp>
#include <hamon/render/clear_value.hpp>
#include <hamon/render/viewport.hpp>
#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/render_target_view.hpp>
#include <hamon/render/d3d11/geometry.hpp>
#include <hamon/render/d3d11/shader.hpp>
#include <memory>
#include <vector>

namespace hamon
{

class Window;

inline namespace render
{

class D3D11Renderer : public Renderer
{
public:
	explicit D3D11Renderer(Window const& window)
	{
		m_factory = std::make_unique<DXGIFactory>();
		m_device = std::make_unique<d3d11::Device>(m_factory->EnumAdapters());
		m_device_context = std::make_unique<d3d11::DeviceContext>(m_device->GetImmediateContext());

		::UINT const buffer_count = 2;	// TODO
		::UINT const width  = window.GetClientWidth();
		::UINT const height = window.GetClientHeight();
		::HWND const hwnd   = window.GetNativeHandle();

		m_swap_chain = std::make_unique<DXGISwapChain>(
			m_factory.get(), m_device->Get(), buffer_count, width, height, hwnd);

		m_factory->MakeWindowAssociation(
			hwnd,
			DXGI_MWA_NO_WINDOW_CHANGES |
			DXGI_MWA_NO_ALT_ENTER |
			DXGI_MWA_NO_PRINT_SCREEN);

		m_render_target_view = std::make_unique<d3d11::RenderTargetView>(m_device.get(), m_swap_chain.get());
	}

	~D3D11Renderer()
	{
		m_device_context->ClearState();
	}

	void Begin(void) override
	{
	}

	void End(void) override
	{
		m_swap_chain->Present(1, 0);
	}

	void BeginRenderPass(ClearValue const& clear_value, Viewport const& viewport) override
	{
		{
			ID3D11RenderTargetView* rtv = m_render_target_view->Get();
			m_device_context->OMSetRenderTargets(
				1,
				&rtv,
				nullptr);
		}

		float const clear_color[] =
		{
			clear_value.r,
			clear_value.g,
			clear_value.b,
			clear_value.a,
		};
		m_device_context->ClearRenderTargetView(
			m_render_target_view->Get(),
			clear_color);

		::D3D11_VIEWPORT vp;
		vp.Width    = viewport.width;
		vp.Height   = viewport.height;
		vp.MinDepth = viewport.min_depth;
		vp.MaxDepth = viewport.max_depth;
		vp.TopLeftX = viewport.left;
		vp.TopLeftY = viewport.top;
		m_device_context->RSSetViewports(1, &vp);
	}

	void EndRenderPass(void) override
	{
	}

	void Render(
		Geometry const& geometry,
		std::vector<render::Shader> const& shaders,
		RasterizerState const& rasterizer_state) override
	{
		{
			::D3D11_RASTERIZER_DESC desc {};
			desc.FillMode              = ToD3D11FillMode(rasterizer_state.fill_mode);
			desc.CullMode              = ToD3D11CullMode(rasterizer_state.cull_mode);
			desc.FrontCounterClockwise = (rasterizer_state.front_face == FrontFace::CounterClockwise);
			desc.DepthBias             = D3D11_DEFAULT_DEPTH_BIAS;
			desc.DepthBiasClamp        = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
			desc.SlopeScaledDepthBias  = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			desc.DepthClipEnable       = FALSE;
			desc.ScissorEnable         = FALSE;
			desc.MultisampleEnable     = FALSE;
			desc.AntialiasedLineEnable = FALSE;

			auto state = m_device->CreateRasterizerState(&desc);
			m_device_context->RSSetState(state.Get());
		}

		std::vector<std::unique_ptr<d3d11::Shader>> d3d11_shaders;
		for (auto const& shader : shaders)
		{
			switch (shader.GetStage())
			{
			case render::ShaderStage::Compute:
				d3d11_shaders.push_back(std::make_unique<d3d11::ComputeShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Vertex:
				d3d11_shaders.push_back(std::make_unique<d3d11::VertexShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Hull:
				d3d11_shaders.push_back(std::make_unique<d3d11::HullShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Domain:
				d3d11_shaders.push_back(std::make_unique<d3d11::DomainShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Geometry:
				d3d11_shaders.push_back(std::make_unique<d3d11::GeometryShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Pixel:
				d3d11_shaders.push_back(std::make_unique<d3d11::PixelShader>(m_device.get(), shader));
				break;
			}
		}
		d3d11::Geometry d3d11_geometry(m_device.get(), geometry);

		for (auto const& shader : d3d11_shaders)
		{
			shader->Bind(m_device_context.get());
		}

		d3d11_geometry.Draw(m_device_context.get());
	}

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
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d11::Device>				m_device;
	std::unique_ptr<d3d11::DeviceContext>		m_device_context;
	std::unique_ptr<d3d11::RenderTargetView>	m_render_target_view;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
