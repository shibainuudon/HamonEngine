/**
 *	@file	sample_render_clear_main.cpp
 *
 *	@brief	レンダーターゲットをクリアするサンプル
 */

#include <hamon/window.hpp>
#include <hamon/render.hpp>
#include <memory>
#include <vector>

namespace
{

struct HSV
{
	float h;
	float s;
	float v;
};

struct RGB
{
	float r;
	float g;
	float b;
};

inline RGB HSVtoRGB(HSV const& hsv)
{
	float h = hsv.h;
	float s = hsv.s;
	float v = hsv.v;

	float r = v;
	float g = v;
	float b = v;
	if (s > 0.0f)
	{
		h *= 6.0f;
		const int i = (int)h;
		const float f = h - (float)i;
		switch (i)
		{
		default:
		case 0:
			g *= 1 - s * (1 - f);
			b *= 1 - s;
			break;
		case 1:
			r *= 1 - s * f;
			b *= 1 - s;
			break;
		case 2:
			r *= 1 - s;
			b *= 1 - s * (1 - f);
			break;
		case 3:
			r *= 1 - s;
			g *= 1 - s * f;
			break;
		case 4:
			r *= 1 - s * (1 - f);
			g *= 1 - s;
			break;
		case 5:
			g *= 1 - s;
			b *= 1 - s * f;
			break;
		}
	}
	return {r, g, b};
}

}

int main()
{
	std::uint32_t const width  = 800;
	std::uint32_t const height = 600;

	std::vector<std::unique_ptr<hamon::Window>> windows;
	std::vector<std::unique_ptr<hamon::Renderer>> renderers;

#if defined(HAMON_HAS_OPEN_GL)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_clear OpenGL");
		auto renderer = std::make_unique<hamon::OpenGLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if defined(HAMON_HAS_D3D11)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_clear D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if defined(HAMON_HAS_D3D12)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_clear D3D12");
		auto renderer = std::make_unique<hamon::D3D12Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if defined(HAMON_HAS_VULKAN)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_clear Vulkan");
		auto renderer = std::make_unique<hamon::VulkanRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif

	HSV hsv;
	hsv.h = 0;
	hsv.s = 1;
	hsv.v = 1;

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		auto rgb = HSVtoRGB(hsv);

		hamon::ClearValue clear_value;
		clear_value.r = rgb.r;
		clear_value.g = rgb.g;
		clear_value.b = rgb.b;
		clear_value.a = 1.0f;
		clear_value.depth = 0.0f;
		clear_value.stencil = 0;

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(clear_value, {});
			renderer->EndRenderPass();
			renderer->End();
		}

		hsv.h += 0.01f;
		if (hsv.h > 1.0f)
		{
			hsv.h = 0;
		}
	}

	return 0;
}
