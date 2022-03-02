/**
 *	@file	win32.hpp
 *
 *	@brief
 */

#ifndef HAMON_WINDOW_WIN32_WIN32_HPP
#define HAMON_WINDOW_WIN32_WIN32_HPP

#include <Windows.h>

#undef CreateWindowEx
#undef RegisterClassEx
#undef DefWindowProc

namespace hamon
{

namespace win32
{

inline HWND
CreateWindowEx(
    DWORD dwExStyle,
    char const* lpClassName,
    char const* lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam)
{
	return ::CreateWindowExA(
		dwExStyle,
		lpClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam);
}

inline HWND
CreateWindowEx(
    DWORD dwExStyle,
    wchar_t const* lpClassName,
    wchar_t const* lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam)
{
	return ::CreateWindowExW(
		dwExStyle,
		lpClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam);
}

inline ATOM RegisterClassEx(CONST WNDCLASSEXA * wc)
{
	return ::RegisterClassExA(wc);
}
inline ATOM RegisterClassEx(CONST WNDCLASSEXW * wc)
{
	return ::RegisterClassExW(wc);
}

template <typename CharT>
LRESULT CALLBACK
DefWindowProc(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

template <>
LRESULT CALLBACK
DefWindowProc<char>(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam)
{
	return ::DefWindowProcA(hWnd, Msg, wParam, lParam);
}

template <>
LRESULT CALLBACK
DefWindowProc<wchar_t>(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, Msg, wParam, lParam);
}

template <typename CharT>
struct TWndClassEX;

template <>
struct TWndClassEX<char>
{
	using type = ::WNDCLASSEXA;
};
template <>
struct TWndClassEX<wchar_t>
{
	using type = ::WNDCLASSEXW;
};

template <typename CharT>
using WndClassEX = typename TWndClassEX<CharT>::type;

}	// namespace win32

}	// namespace hamon

#endif // HAMON_WINDOW_WIN32_WIN32_HPP
