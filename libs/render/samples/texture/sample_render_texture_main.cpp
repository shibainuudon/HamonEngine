/**
 *	@file	sample_render_texture_main.cpp
 *
 *	@brief	テクスチャを描画するサンプル
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
					layout(location = 1) in vec2 aTexCoord;

					layout(location = 0) out vec2 vTexCoord;

					void main()
					{
						gl_Position = vec4(aPosition, 1.0);
						vTexCoord = aTexCoord;
					}
				)"
			},
			{
				hamon::ShaderStage::Fragment,
				R"(
					#version 450
					layout(location = 0) in vec2 vTexCoord;

					layout(location = 0) out vec4 oColor;

					layout(binding = 0) uniform sampler2D uSampler2D;

					void main()
					{
						oColor = texture(uSampler2D, vTexCoord);
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
						float2 uv    : TEXCOORD;
					};

					struct VS_OUTPUT
					{
						float4 pos   : SV_POSITION;
						float2 uv    : TEXCOORD;
					};

					VS_OUTPUT main(VS_INPUT input)
					{
						VS_OUTPUT output;
						output.pos = float4(input.pos, 1.0);
						output.uv = input.uv;
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
						float2 uv    : TEXCOORD;
					};

					Texture2D    uTexture : register(t0);
					SamplerState uSampler : register(s0);

					float4 main(PS_INPUT input) : SV_Target
					{
						return uTexture.Sample(uSampler, input.uv);
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
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_texture OpenGL");
		auto renderer = std::make_unique<hamon::GLRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetGLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D11)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_texture D3D11");
		auto renderer = std::make_unique<hamon::D3D11Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_D3D12)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_texture D3D12");
		auto renderer = std::make_unique<hamon::D3D12Renderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetHLSLProgram());
	}
#endif
#if defined(HAMON_HAS_VULKAN)
	{
		auto window = std::make_unique<hamon::Window>(width, height, "sample_render_texture Vulkan");
		auto renderer = std::make_unique<hamon::VulkanRenderer>(*window);
		windows.push_back(std::move(window));
		renderers.push_back(std::move(renderer));
		programs.push_back(GetGLSLProgram());
	}
#endif

	hamon::VertexLayout const vertex_layout
	{
		20,
		{
			{ hamon::Semantic::Position, hamon::Type::Float, 3, 0 },
			{ hamon::Semantic::TexCoord, hamon::Type::Float, 2, 12 },
		},
	};

	std::vector<float> const vertices
	{
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f,	// 左上
		 0.5f,  0.5f, 0.0f,  0.0f, 1.0f,	// 右上
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,	// 左下
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f,	// 右下
	};

	std::uint16_t const indices[]
	{
		0, 1, 2,
		2, 1, 3,
	};

	hamon::Geometry const geometry
	{
		hamon::PrimitiveTopology::TriangleList, vertex_layout, vertices, indices
	};

	int const tex_width = 16;
	int const tex_height = 16;
	std::vector<std::uint8_t>	pixels(tex_width * tex_height * 4);
	for (int y = 0; y < tex_height; ++y)
	{
		for (int x = 0; x < tex_width; ++x)
		{
			pixels[(y * tex_height + x) * 4 + 0] = static_cast<std::uint8_t>(x*16); 
			pixels[(y * tex_height + x) * 4 + 1] = static_cast<std::uint8_t>(y*16); 
			pixels[(y * tex_height + x) * 4 + 2] = static_cast<std::uint8_t>(0); 
			pixels[(y * tex_height + x) * 4 + 3] = static_cast<std::uint8_t>(255); 
		}
	}
	hamon::Texture texture(hamon::TextureFormat::R8G8B8A8_UNORM, tex_width, tex_height, 1, pixels.data());

	hamon::Sampler sampler;
	sampler.min_filter = hamon::FilterMode::Nearest;
	sampler.mag_filter = hamon::FilterMode::Nearest;
	sampler.mip_filter = hamon::MipmapMode::Disable;

	hamon::Uniforms uniforms;
	uniforms["uSampler2D"] = std::make_pair(texture, sampler);
	uniforms["uTexture"] = texture;
	uniforms["uSampler"] = sampler;

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
		render_pass.clear_value.color = { 0.4f, 0.4f, 0.4f, 1.0f };
		render_pass.viewport = { 0, 0, width, height };

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
	}

	return 0;
}
