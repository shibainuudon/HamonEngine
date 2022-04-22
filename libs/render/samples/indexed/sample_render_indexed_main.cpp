/**
 *	@file	sample_render_index_main.cpp
 *
 *	@brief	頂点インデックスを使うサンプル
 */

#include <hamon/window.hpp>
#include <hamon/render.hpp>
#include <memory>
#include <vector>

namespace
{

hamon::Program GetGLSLProgram(void)
{
	return
	{
		hamon::ShaderLanguage::GLSL,
		{
			{
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
		}
	};
}

hamon::Program GetHLSLProgram(void)
{
	return
	{
		hamon::ShaderLanguage::HLSL,
		{
			{
				hamon::ShaderStage::Vertex,
				R"(
					struct VS_INPUT
					{
						float3 pos   : POSITION;
						float4 color : COLOR;
					};

					struct VS_OUTPUT
					{
						float4 pos   : SV_POSITION;
						float4 color : COLOR;
					};

					VS_OUTPUT main(VS_INPUT input)
					{
						VS_OUTPUT output;
						output.pos = float4(input.pos, 1.0);
						output.color = input.color;
						return output;
					}
				)"
			},
			{
				hamon::ShaderStage::Fragment,
				R"(
					struct PS_INPUT
					{
						float4 pos   : SV_POSITION;
						float4 color : COLOR;
					};

					float4 main(PS_INPUT input) : SV_Target
					{
						return input.color;
					}
				)"
			},
		}
	};
}

}

int main()
{
	std::uint32_t const width  = 640;
	std::uint32_t const height = 480;

	std::vector<std::unique_ptr<hamon::Window>>   windows;
	std::vector<std::unique_ptr<hamon::Renderer>> renderers;
	std::vector<hamon::Program>					  programs;

#if defined(HAMON_HAS_OPEN_GL)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_index OpenGL");
		auto renderer = std::make_unique<hamon::GLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetGLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D11)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_index D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D12)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_index D3D12");
		auto renderer = std::make_unique<hamon::D3D12Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_VULKAN)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_index Vulkan");
		auto renderer = std::make_unique<hamon::VulkanRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetGLSLProgram());
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
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,	// 左上
		 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,	// 右上
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,	// 左下
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,	// 右下
	};

#if 1
	std::vector<std::uint16_t> const indices
#elif 0
	std::vector<std::uint32_t> const indices
#elif 0
	std::uint16_t const indices[]
#else
	std::uint32_t const indices[]
#endif
	{
		0, 1, 2,
		2, 1, 3,
	};

	hamon::Geometry const geometry
	{
		hamon::PrimitiveTopology::TriangleList, vertex_layout, vertices, indices
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

		hamon::RenderPassState render_pass;
		render_pass.clear_value.color.r = 0.4f;
		render_pass.clear_value.color.g = 0.4f;
		render_pass.clear_value.color.b = 0.4f;
		render_pass.clear_value.color.a = 1.0f;
		render_pass.clear_value.depth = 0.0f;
		render_pass.clear_value.stencil = 0;
		render_pass.viewport.width  = width;
		render_pass.viewport.height = height;

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass);

			renderer->Render(geometry, programs[i], {}, {});

			renderer->EndRenderPass();
			renderer->End();
			++i;
		}
	}

	return 0;
}
