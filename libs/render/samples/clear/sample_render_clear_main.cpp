/**
 *	@file	sample_render_clear_main.cpp
 *
 *	@brief	レンダーターゲットをクリアするサンプル
 */

#include <hamon/window.hpp>
#include <hamon/render.hpp>
#include <memory>
#include <vector>

int main()
{
	std::vector<std::unique_ptr<hamon::Window>> windows;
	std::vector<std::unique_ptr<hamon::Renderer>> renderers;

	{
		auto window = std::make_unique<hamon::Window>(1280, 960, "sample_render_clear OpenGL");
		auto renderer = std::make_unique<hamon::OpenGLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
	{
		auto window = std::make_unique<hamon::Window>(1280, 960, "sample_render_clear D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->End();
		}
	}

	return 0;
}
