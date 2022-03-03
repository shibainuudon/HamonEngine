/**
 *	@file	opengl_renderer.hpp
 *
 *	@brief	OpenGLRenderer
 */

#ifndef HAMON_RENDER_OPENGL_RENDERER_HPP
#define HAMON_RENDER_OPENGL_RENDERER_HPP

#include <hamon/render/opengl/gl.hpp>
#include <memory>

namespace hamon
{

class Window;

inline namespace render
{

namespace gl
{
class Context;
}

class OpenGLRenderer
{
public:
	explicit OpenGLRenderer(Window const& window);
	~OpenGLRenderer();

	void Begin(void);
	void End(void);

private:
	static void APIENTRY DebugCallback(
		::GLenum source,
		::GLenum type,
		::GLuint id,
		::GLenum severity,
		::GLsizei length,
		::GLchar const* message,
		void const* userParam);

private:
	std::unique_ptr<gl::Context>	m_context;
};

}	// inline namespace render

}	// namespace hamon

#include <hamon/render/opengl/opengl_renderer_inl.hpp>

#endif // HAMON_RENDER_OPENGL_RENDERER_HPP
