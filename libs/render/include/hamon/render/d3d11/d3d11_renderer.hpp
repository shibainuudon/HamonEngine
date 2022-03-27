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

	void BeginRenderPass(ClearValue const& clear_value) override
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

		::D3D11_VIEWPORT viewport;
		viewport.Width = 800;
		viewport.Height = 600;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		m_device_context->RSSetViewports(1, &viewport);
	}

	void EndRenderPass(void) override
	{
	}

	void Render(Geometry const& geometry, std::vector<render::Shader> const& shaders) override
	{
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
			case render::ShaderStage::TessellationControl:
				d3d11_shaders.push_back(std::make_unique<d3d11::HullShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::TessellationEvaluation:
				d3d11_shaders.push_back(std::make_unique<d3d11::DomainShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Geometry:
				d3d11_shaders.push_back(std::make_unique<d3d11::GeometryShader>(m_device.get(), shader));
				break;
			case render::ShaderStage::Fragment:
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
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d11::Device>				m_device;
	std::unique_ptr<d3d11::DeviceContext>		m_device_context;
	std::unique_ptr<d3d11::RenderTargetView>	m_render_target_view;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
