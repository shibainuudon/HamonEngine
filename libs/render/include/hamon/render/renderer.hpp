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
class Program;
class Uniforms;
struct RenderPassState;
struct RenderState;

class Renderer
{
public:
	virtual ~Renderer() {}

	virtual void Begin(void) = 0;
	virtual void End(void) = 0;

	virtual void BeginRenderPass(RenderPassState const& render_pass_state) = 0;
	virtual void EndRenderPass(void) = 0;

	virtual void Render(
		Geometry const& geometry,
		Program const& program,
		Uniforms const& uniforms,
		RenderState const& render_state) = 0;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RENDERER_HPP
