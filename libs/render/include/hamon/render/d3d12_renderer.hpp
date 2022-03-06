/**
 *	@file	d3d12_renderer.hpp
 *
 *	@brief	D3D12Renderer
 */

#ifndef HAMON_RENDER_D3D12_RENDERER_HPP
#define HAMON_RENDER_D3D12_RENDERER_HPP

#include <hamon/render/renderer.hpp>
#include <hamon/render/d3d/dxgi_factory.hpp>
#include <hamon/render/d3d/dxgi_swap_chain.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_queue.hpp>
#include <hamon/render/d3d12/command_allocator.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d12/fence.hpp>
#include <hamon/render/d3d12/render_target_view.hpp>
#include <memory>

namespace hamon
{

class Window;

inline namespace render
{

class D3D12Renderer : public Renderer
{
public:
	explicit D3D12Renderer(Window const& window);
	~D3D12Renderer();

	void Begin(void) override;
	void End(void) override;

private:
	std::unique_ptr<DXGIFactory>				m_factory;
	std::unique_ptr<DXGISwapChain>				m_swap_chain;
	std::unique_ptr<d3d12::Device>				m_device;
	std::unique_ptr<d3d12::CommandQueue>		m_command_queue;
	std::unique_ptr<d3d12::CommandAllocator>	m_command_allocator;
	std::unique_ptr<d3d12::CommandList>			m_command_list;
	std::unique_ptr<d3d12::Fence>				m_fence;
	std::unique_ptr<d3d12::RenderTargetView>	m_render_target_view;
	::UINT										m_frame_index;
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/d3d12/d3d12_renderer_inl.hpp>

#endif // HAMON_RENDER_D3D12_RENDERER_HPP
