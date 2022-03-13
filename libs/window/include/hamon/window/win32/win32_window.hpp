/**
 *	@file	win32_window.hpp
 *
 *	@brief
 */

#ifndef HAMON_WINDOW_WIN32_WIN32_WINDOW_HPP
#define HAMON_WINDOW_WIN32_WIN32_WINDOW_HPP

#include <cstdint>
#include <string_view>
#include <string>
#include <hamon/window/win32/win32.hpp>

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
		m_hwnd = Create(width, height, title);
		::ShowWindow(m_hwnd, SW_SHOW);
	}
	Window(
		std::uint32_t width,
		std::uint32_t height,
		std::wstring_view title)
	{
		m_hwnd = Create(width, height, title);
		::ShowWindow(m_hwnd, SW_SHOW);
	}

	~Window()
	{
		Destroy();
	}

	bool Update(void)
	{
		::MSG msg;
		while(::PeekMessage(&msg, m_hwnd, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return false;
			}

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		return true;
	}

	::HWND GetNativeHandle(void) const { return m_hwnd; }

	std::uint32_t GetClientWidth(void) const
	{
		::RECT rect;
		::GetClientRect(m_hwnd, &rect);
		return rect.right;
	}

	std::uint32_t GetClientHeight(void) const
	{
		::RECT rect;
		::GetClientRect(m_hwnd, &rect);
		return rect.bottom;
	}

private:

	static int GetUniqueNumber(void)
	{
		static int s_count = 0;
		return s_count++;
	}

	template <typename CharT>
	std::basic_string<CharT> GetUniqueClassName(void);

	template <>
	std::basic_string<char> GetUniqueClassName(void)
	{
		return "HamonWindow" + std::to_string(GetUniqueNumber());
	}

	template <>
	std::basic_string<wchar_t> GetUniqueClassName(void)
	{
		return L"HamonWindow" + std::to_wstring(GetUniqueNumber());
	}

	template <typename CharT>
	static LRESULT CALLBACK WndProc(
		::HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_CREATE)
		{
			auto const* create_struct = reinterpret_cast<LPCREATESTRUCT>(lparam);
			::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create_struct->lpCreateParams));
			return 0;
		}

		auto* this_ = reinterpret_cast<Window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

		switch (msg)
		{
		case WM_CLOSE:
			this_->Destroy();
			return 0;

		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		}

		return win32::DefWindowProc<CharT>(hwnd, msg, wparam, lparam);
	}

	template <typename CharT>
	static bool RegisterWindowClass(std::basic_string<CharT> const& class_name)
	{
		auto const instance = ::GetModuleHandleW(nullptr);
		using WC = win32::WndClassEX<CharT>;
		WC const wc =
		{
			sizeof(WC),
			CS_OWNDC,
			WndProc<CharT>,
			0,
			0,
			instance,
			::LoadIcon(nullptr, IDI_APPLICATION),
			::LoadCursor(nullptr, IDC_ARROW),
			::CreateSolidBrush(RGB(0, 0, 0)),
			nullptr,
			class_name.c_str(),
			nullptr
		};

		return win32::RegisterClassEx(&wc) != 0;
	}

	template <typename CharT>
	::HWND Create(
		std::uint32_t width,
		std::uint32_t height,
		std::basic_string_view<CharT> title)
	{
		auto const class_name = GetUniqueClassName<CharT>();

		if (!RegisterWindowClass(class_name))
		{
			return nullptr;
		}

		DWORD const window_style_ex = WS_EX_OVERLAPPEDWINDOW;
		DWORD const window_style = WS_OVERLAPPEDWINDOW;

		RECT rect{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
		AdjustWindowRectEx(&rect, window_style, FALSE, window_style_ex);

		return win32::CreateWindowEx(
			window_style_ex,
			class_name.c_str(),
			title.data(),
			window_style,
			0,	// x
			0,	// y
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,	// parent
			0,	// menu
			::GetModuleHandleW(nullptr),
			this);
	}

	void Destroy(void)
	{
		if (m_hwnd)
		{
			::DestroyWindow(m_hwnd);
		}
		m_hwnd = nullptr;
	}

private:
	::HWND m_hwnd = nullptr;
};

}	// namespace hamon

#endif // HAMON_WINDOW_WIN32_WIN32_WINDOW_HPP
