/**
 *	@file	context.hpp
 *
 *	@brief	Context
 */

#ifndef HAMON_RENDER_OPENGL_CONTEXT_HPP
#define HAMON_RENDER_OPENGL_CONTEXT_HPP

#include <hamon/window.hpp>
#include <hamon/render/opengl/wglext.hpp>

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
		: m_hwnd(window.GetNativeHandle())
		, m_hdc(::GetDC(m_hwnd))
	{
		SetPixelFormat(m_hdc, 32);

		// 仮のGLコンテキストの作成
		auto hglrc_dummy = ::wglCreateContext(m_hdc);
		::wglMakeCurrent(m_hdc, hglrc_dummy);

		// 使用する OpenGL のバージョンとプロファイルの指定
		static const int att[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0,
		};

		// 使用するGLコンテキストの作成
		m_hglrc = gl::wglCreateContextAttribsARB(m_hdc, NULL, att);
		::wglMakeCurrent(m_hdc, m_hglrc);

		// 仮のGLコンテキストの削除
		::wglDeleteContext(hglrc_dummy);
	}

	~Context()
	{
		::wglDeleteContext(m_hglrc);
		::ReleaseDC(m_hwnd, m_hdc);
	}

	void SwapBuffers(void)
	{
		::SwapBuffers(m_hdc);
	}

private:
	static void SetPixelFormat(::HDC hdc, int color_depth)
	{
		::PIXELFORMATDESCRIPTOR const pfd =
		{
			sizeof(::PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
			PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
			(::BYTE)color_depth, //Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24, //Number of bits for the depthbuffer
			8, //Number of bits for the stencilbuffer
			0, //Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int const format = ::ChoosePixelFormat(hdc, &pfd);

		if (format == 0)
		{
			return; // 該当するピクセルフォーマットが無い
		}

		// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
		if (!::SetPixelFormat(hdc, format, &pfd))
		{
			return; // DCへフォーマットを設定するのに失敗
		}
	}

private:
	::HWND  m_hwnd  = nullptr;
	::HDC   m_hdc   = nullptr;
	::HGLRC m_hglrc = nullptr;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_CONTEXT_HPP
