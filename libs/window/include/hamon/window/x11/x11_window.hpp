/**
 *	@file	x11_window.hpp
 *
 *	@brief
 */

#ifndef HAMON_WINDOW_X11_X11_WINDOW_HPP
#define HAMON_WINDOW_X11_X11_WINDOW_HPP

#include <cstdint>
#include <string_view>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace hamon
{

class Window
{
public:
	Window(
		std::uint32_t width,
		std::uint32_t height,
		std::string_view title)
	{
		m_display = XOpenDisplay(NULL);
		m_window = XCreateSimpleWindow(
			m_display,
			RootWindow(m_display, 0),
			0, 0,	// x, y
			width, height,
			1,	// border_width
			0,	// border
			0);	// background

		SetTitle(title);
		XSelectInput(
			m_display,
			m_window,
			StructureNotifyMask);
		XMapWindow(m_display, m_window);
		XFlush(m_display);
	}
	//Window(
	//	std::uint32_t width,
	//	std::uint32_t height,
	//	std::wstring_view title)
	//{
	//}

	// コピー不可
	Window(Window const&) = delete;
	Window& operator=(Window const&) = delete;

	~Window()
	{
		//XCloseDisplay(m_display);
	}

	bool Update(void)
	{
		XEvent event;
		XNextEvent(m_display, &event);
		switch (event.type)
		{
		case DestroyNotify:
			XSetCloseDownMode(m_display, DestroyAll);
			XCloseDisplay(m_display);
			return false;
		}
		return true;
	}

	void SetTitle(std::string_view title)
	{
		XTextProperty text;

		text.value = (unsigned char *)title.data();
		text.encoding = XA_STRING;
		text.format = 8;
		text.nitems = title.length();

		XSetWMName(
			m_display,
			m_window,
			&text);

		XFlush(m_display);
	}

	//::HWND GetNativeHandle(void) const { return m_hwnd; }

	//std::uint32_t GetClientWidth(void) const
	//{
	//	::RECT rect;
	//	::GetClientRect(m_hwnd, &rect);
	//	return rect.right;
	//}

	//std::uint32_t GetClientHeight(void) const
	//{
	//	::RECT rect;
	//	::GetClientRect(m_hwnd, &rect);
	//	return rect.bottom;
	//}

	Display* GetDisplay(void) const { return m_display; }
	::Window GetWindow(void) const { return m_window; }

private:
	Display*	m_display;
	::Window	m_window;
};

}	// namespace hamon

#endif // HAMON_WINDOW_X11_X11_WINDOW_HPP
