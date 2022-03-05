/**
 *	@file	renderer.hpp
 *
 *	@brief	Renderer
 */

#ifndef HAMON_RENDER_RENDERER_HPP
#define HAMON_RENDER_RENDERER_HPP

namespace hamon
{

inline namespace render
{

class Renderer
{
public:
	virtual ~Renderer() {}

	virtual void Begin(void) = 0;
	virtual void End(void) = 0;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_RENDERER_HPP
