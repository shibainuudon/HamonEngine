/**
 *	@file	sample_render_uniform_main.cpp
 *
 *	@brief	ユニフォーム変数を設定するサンプル
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

					layout (set=0, binding=0)
					uniform UniformBuffer1
					{
						vec3 uOffset;
						mat4 uMat;
					};

					layout(location = 0) in vec3 aPosition;

					void main()
					{
						gl_Position = uMat * vec4(aPosition, 1.0) + vec4(uOffset, 0.0);
					}
				)"
			},
			{
				hamon::ShaderStage::Fragment,
				R"(
					#version 450

					layout (set=0, binding=1)
					uniform UniformBuffer2
					{
						float uRed;
						float uGreen;
						float uBlue;
					};

					layout(location = 0) out vec4 oColor;

					void main()
					{
						oColor = vec4(uRed, uGreen, uBlue, 1);
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
					};

					struct VS_OUTPUT
					{
						float4 pos   : SV_POSITION;
					};

					cbuffer ConstantBuffer1 : register(b1)
					{
						float3 uOffset;
						row_major float4x4 uMat;
					};

					VS_OUTPUT main(VS_INPUT input)
					{
						VS_OUTPUT output;
						output.pos = mul(float4(input.pos, 1.0), uMat) + float4(uOffset, 0.0);
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
					};

					cbuffer ConstantBuffer2 : register(b2)
					{
						float uRed;
						float uGreen;
						float uBlue;
					};

					float4 main(PS_INPUT input) : SV_Target
					{
						return float4(uRed, uGreen, uBlue, 1);
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
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_uniform OpenGL");
		auto renderer = std::make_unique<hamon::GLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetGLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D11)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_uniform D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D12)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_uniform D3D12");
		auto renderer = std::make_unique<hamon::D3D12Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_VULKAN)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_uniform Vulkan");
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
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
	};

	hamon::Geometry const geometry
	{
		hamon::PrimitiveTopology::TriangleList, vertex_layout, vertices
	};

	hamon::Uniforms uniforms;

	std::vector<float> const color = {1, 0, 1};
	uniforms["uColor"] = color;
	
	uniforms["uGreen"] = 0.5f;

	struct Vector3
	{
		float x;
		float y;
		float z;
	};
	Vector3 offset {0, 0, 0};

	float a = 0;
	float r = 0;
	float b = 0;
	float t = 0;
	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		offset.x = std::sin(t);
		uniforms["uOffset"] = offset;

		uniforms["uRed"] = r;
		uniforms["uBlue"] = b;

		float mat[4 * 4] =
		{
			 std::cos(a), std::sin(a), 0, 0,
			-std::sin(a), std::cos(a), 0, 0,
			 0,           0,           1, 0,
			 0,           0,           0, 1,
		};
		uniforms["uMat"] = mat;

		hamon::RenderPassState render_pass;
		render_pass.clear_value.color = { 0.4f, 0.4f, 0.4f, 1.0f };
		render_pass.clear_value.depth = 0.0f;
		render_pass.clear_value.stencil = 0;
		render_pass.viewport.width  = width;
		render_pass.viewport.height = height;

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass);

			renderer->Render(geometry, programs[i], uniforms, {});

			renderer->EndRenderPass();
			renderer->End();
			++i;
		}

		a += 0.01f;
		t += 0.02f;
		r += 0.01f;
		if (r > 1.0f)
		{
			r = 0.0f;
		}
		b += 0.02f;
		if (b > 1.0f)
		{
			b = 0.0f;
		}
	}

	return 0;
}
