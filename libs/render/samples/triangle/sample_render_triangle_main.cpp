/**
 *	@file	sample_render_triangle_main.cpp
 *
 *	@brief	三角形を描画するサンプル
 */

#include <hamon/window.hpp>
#include <hamon/render.hpp>
#include <memory>
#include <vector>

namespace
{


}

int main()
{
	std::uint32_t const width  = 800;
	std::uint32_t const height = 600;

	std::vector<std::unique_ptr<hamon::Window>> windows;
	std::vector<std::unique_ptr<hamon::Renderer>> renderers;

#if defined(HAMON_HAS_OPEN_GL)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_triangle OpenGL");
		auto renderer = std::make_unique<hamon::OpenGLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if 0//defined(HAMON_HAS_D3D11)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_triangle D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if 0//defined(HAMON_HAS_D3D12)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_triangle D3D12");
		auto renderer = std::make_unique<hamon::D3D12Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif
#if 0//defined(HAMON_HAS_VULKAN)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_triangle Vulkan");
		auto renderer = std::make_unique<hamon::VulkanRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
	}
#endif

	hamon::VertexLayout const vertex_layout
	{
		28,
		{
			{ hamon::Semantic::Position, hamon::Type::Float, 3, 0 },
			{ hamon::Semantic::Color,    hamon::Type::Float, 4, 12 },
		},
	};

	std::vector<float> const vertices
	{
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
	};

	hamon::Geometry const geometry
	{
		hamon::PrimitiveTopology::Triangles, vertex_layout, vertices
	};

	std::vector<hamon::Shader> const shaders
	{
		{
			hamon::ShaderLanguage::GLSL,
			hamon::ShaderStage::Vertex,
			R"(
				#version 450
				layout(location = 0) in vec3 aPosition;
				layout(location = 1) in vec4 aColor;

				layout(location = 0) out vec4 vColor;

				void main()
				{
					gl_Position = vec4(aPosition, 1.0);
					vColor = aColor;
				}
			)"
		},
		{
			hamon::ShaderLanguage::GLSL,
			hamon::ShaderStage::Fragment,
			R"(
				#version 450
				layout(location = 0) in vec4 vColor;

				layout(location = 0) out vec4 oColor;

				void main()
				{
					oColor = vColor;
				}
			)"
		},
	};

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		hamon::ClearValue clear_value;
		clear_value.r = 0.4f;
		clear_value.g = 0.4f;
		clear_value.b = 0.4f;
		clear_value.a = 1.0f;
		clear_value.depth = 0.0f;
		clear_value.stencil = 0;

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(clear_value);

			renderer->Render(geometry, shaders);

			renderer->EndRenderPass();
			renderer->End();
		}
	}

	return 0;
}
