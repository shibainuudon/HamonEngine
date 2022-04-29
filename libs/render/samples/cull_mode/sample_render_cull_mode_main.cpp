/**
 *	@file	sample_render_cull_mode_main.cpp
 *
 *	@brief	CullModeを設定するサンプル
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
						mat4 uRotMat;
						mat4 uTransMat;
					};

					layout(location = 0) in vec3 aPosition;
					layout(location = 1) in vec4 aColor;

					layout(location = 0) out vec4 vColor;

					void main()
					{
						gl_Position = uTransMat * uRotMat * vec4(aPosition, 1.0);
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
					cbuffer ConstantBuffer1 : register(b1)
					{
						row_major float4x4 uRotMat;
						row_major float4x4 uTransMat;
					};

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
						output.pos = mul(mul(float4(input.pos, 1.0), uRotMat), uTransMat);
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

class Triangle
{
public:
	Triangle(hamon::FrontFace front_face, hamon::CullMode cull_mode, float x, float y)
	{
		m_render_state.rasterizer_state.front_face = front_face;
		m_render_state.rasterizer_state.cull_mode = cull_mode;

		float const trans_mat[4 * 4] =
		{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				x, y, 0.5f, 1,	// depth clippingされないようにZを0.5オフセット
		};
		m_uniforms["uTransMat"] = trans_mat;

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
			 0.0f,   0.25f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.25f, -0.25f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.25f, -0.25f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		m_geometry = std::make_unique<hamon::Geometry>(
			hamon::PrimitiveTopology::TriangleList, vertex_layout, vertices);
	}

	void Update(void)
	{
		auto const a = m_angle;
		float const rot_mat[4 * 4] =
		{
			 std::cos(a), 0, -std::sin(a), 0,
			 0,           1,  0,           0,
			 std::sin(a), 0,  std::cos(a), 0,
			 0,           0,  0,           1,
		};
		m_uniforms["uRotMat"] = rot_mat;

		m_angle += 0.02f;
	}

	void Draw(hamon::Renderer* renderer, hamon::Program const& program)
	{
		renderer->Render(*m_geometry, program, m_uniforms, m_render_state);
	}

private:
	hamon::Uniforms						m_uniforms;
	hamon::RenderState					m_render_state;
	std::unique_ptr<hamon::Geometry>	m_geometry;
	float								m_angle{};
};

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

	std::vector<Triangle> triangles;
	triangles.emplace_back(hamon::FrontFace::CW,  hamon::CullMode::None, -0.6f,  0.5f);
	triangles.emplace_back(hamon::FrontFace::CW,  hamon::CullMode::Back,  0.0f,  0.5f);
	triangles.emplace_back(hamon::FrontFace::CW,  hamon::CullMode::Front, 0.6f,  0.5f);
	triangles.emplace_back(hamon::FrontFace::CCW, hamon::CullMode::None, -0.6f, -0.5f);
	triangles.emplace_back(hamon::FrontFace::CCW, hamon::CullMode::Back,  0.0f, -0.5f);
	triangles.emplace_back(hamon::FrontFace::CCW, hamon::CullMode::Front, 0.6f, -0.5f);

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
		render_pass.clear_value.depth = 1.0f;
		render_pass.clear_value.stencil = 0;
		render_pass.viewport.width  = width;
		render_pass.viewport.height = height;

		for (auto& t : triangles)
		{
			t.Update();
		}

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass);

			for (auto& t : triangles)
			{
				t.Draw(renderer.get(), programs[i]);
			}

			renderer->EndRenderPass();
			renderer->End();
			++i;
		}
	}

	return 0;
}
