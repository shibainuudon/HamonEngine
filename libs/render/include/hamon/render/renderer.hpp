/**
 *	@file	renderer.hpp
 *
 *	@brief	Renderer
 */

#ifndef HAMON_RENDER_RENDERER_HPP
#define HAMON_RENDER_RENDERER_HPP

#include <vector>

namespace hamon
{

inline namespace render
{

class Geometry;
class Shader;
struct ClearValue;
struct Viewport;
struct RasterizerState;
struct BlendState;
struct DepthStencilState;

class Renderer
{
public:
	virtual ~Renderer() {}

	virtual void Begin(void) = 0;
	virtual void End(void) = 0;

	virtual void BeginRenderPass(ClearValue const& clear_value, Viewport const& viewport) = 0;
	virtual void EndRenderPass(void) = 0;

	virtual void Render(
		Geometry const& geometry,
		std::vector<Shader> const& shaders,
		RasterizerState const& rasterizer_state,
		BlendState const& blend_state,
		DepthStencilState const& depth_stencil_state) = 0;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RENDERER_HPP
