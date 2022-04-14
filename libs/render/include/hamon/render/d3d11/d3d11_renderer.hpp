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
#include <hamon/render/program.hpp>
#include <hamon/render/clear_value.hpp>
#include <hamon/render/viewport.hpp>
#include <hamon/render/rasterizer_state.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d11/device.hpp>
#include <hamon/render/d3d11/device_context.hpp>
#include <hamon/render/d3d11/render_target_view.hpp>
#include <hamon/render/d3d11/geometry.hpp>
#include <hamon/render/d3d11/shader.hpp>
#include <hamon/render/d3d11/program.hpp>
#include <hamon/render/d3d11/rasterizer_state.hpp>
#include <hamon/render/d3d11/blend_state.hpp>
#include <hamon/render/d3d11/depth_stencil_state.hpp>
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
			clear_value.color.r,
			clear_value.color.g,
			clear_value.color.b,
			clear_value.color.a,
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

private:
	template <typename T, typename Map, typename Id, typename... Args>
	typename Map::mapped_type
	GetOrCreate(Map& map, Id const& id, Args&&... args)
	{
		auto it = map.find(id);
		if (it != map.end())
		{
			return it->second;
		}
		else
		{
			auto p = std::make_shared<T>(std::forward<Args>(args)...);
			map[id] = p;
			return p;
		}
	}

public:
	void Render(
		Geometry const& geometry,
		Program const& program,
		RenderState const& render_state) override
	{
		{
			auto state = m_device->CreateRasterizerState(
				d3d11::RasterizerState(render_state.rasterizer_state));
			m_device_context->RSSetState(state.Get());
		}
		{
			auto state = m_device->CreateBlendState(
				d3d11::BlendState(render_state.blend_state));
			float const blend_factor[4] {};
			::UINT const sample_mask = 0xffffffff;
			m_device_context->OMSetBlendState(state.Get(), blend_factor, sample_mask);
		}
		{
			auto state = m_device->CreateDepthStencilState(
				d3d11::DepthStencilState(render_state.depth_stencil_state));
			m_device_context->OMSetDepthStencilState(
				state.Get(), render_state.depth_stencil_state.stencil.reference);
		}

		auto d3d11_geometry = GetOrCreate<d3d11::Geometry>(
			m_geometry_map, geometry.GetID(), m_device.get(), geometry);
		auto d3d11_program = GetOrCreate<d3d11::Program>(
			m_program_map, program.GetID(), m_device.get(), program);

		d3d11_program->Bind(m_device_context.get());
		d3d11_geometry->Draw(m_device_context.get());
	}

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d11::Device>				m_device;
	std::unique_ptr<d3d11::DeviceContext>		m_device_context;
	std::unique_ptr<d3d11::RenderTargetView>	m_render_target_view;

	std::unordered_map<detail::Identifier, std::shared_ptr<d3d11::Program>>		m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d11::Geometry>>	m_geometry_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_D3D11_RENDERER_HPP
