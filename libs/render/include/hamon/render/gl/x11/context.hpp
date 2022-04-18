/**
 *	@file	context.hpp
 *
 *	@brief	Context
 */

#ifndef HAMON_RENDER_GL_X11_CONTEXT_HPP
#define HAMON_RENDER_GL_X11_CONTEXT_HPP

#include <hamon/window.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Context
{
public:
	explicit Context(Window const& window)
		: m_display(window.GetDisplay())
		, m_window(window.GetWindow())
	{
		int const attributes[] =
		{
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,   GLX_RGBA_BIT,
			GLX_DOUBLEBUFFER,  True,  /* Request a double-buffered color buffer with */
			GLX_RED_SIZE,      1,     /* the maximum number of bits per component    */
			GLX_GREEN_SIZE,    1, 
			GLX_BLUE_SIZE,     1,
			None
		};

		int fbConfigsNum;
		auto fbConfigs = glXChooseFBConfig(
			m_display,
			DefaultScreen(m_display),
			attributes,
			&fbConfigsNum);

		m_context = glXCreateNewContext(
			m_display,
			fbConfigs[0],
			GLX_RGBA_TYPE,
			NULL,
			True);

		glXMakeContextCurrent(m_display, m_window, m_window, m_context);
	}

	~Context()
	{
	}

	void SwapBuffers(void)
	{
		glXSwapBuffers(m_display, m_window);
	}

private:
	GLXContext	m_context;
	Display*	m_display;
	::Window	m_window;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_X11_CONTEXT_HPP
