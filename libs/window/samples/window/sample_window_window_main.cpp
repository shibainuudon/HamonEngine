/**
 *	@file	sample_window_window_main.cpp
 *
 *	@brief	Window のサンプル
 */

#include <hamon/window.hpp>

int main()
{
	hamon::Window window(800, 600, L"サンプルウィンドウ");

	while (window.Update())
	{
	}

	return 0;
}
