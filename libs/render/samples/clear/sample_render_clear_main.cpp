/**
 *	@file	sample_render_clear_main.cpp
 *
 *	@brief	レンダーターゲットをクリアするサンプル
 */

#include <hamon/window.hpp>
#include <hamon/render.hpp>

int main()
{
	hamon::Window window(640, 480, "sample_render_clear");

	hamon::OpenGLRenderer renderer(window);

	while (window.Update())
	{
		renderer.Begin();
		renderer.End();
	}

	return 0;
}
