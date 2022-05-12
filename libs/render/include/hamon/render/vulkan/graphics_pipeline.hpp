/**
 *	@file	graphics_pipeline.hpp
 *
 *	@brief	GraphicsPipeline
 */

#ifndef HAMON_RENDER_VULKAN_GRAPHICS_PIPELINE_HPP
#define HAMON_RENDER_VULKAN_GRAPHICS_PIPELINE_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/program.hpp>
#include <hamon/render/vulkan/pipeline_layout.hpp>
#include <hamon/render/vulkan/pipeline_input_assembly_state.hpp>
#include <hamon/render/vulkan/pipeline_rasterization_state.hpp>
#include <hamon/render/vulkan/pipeline_multisample_state.hpp>
#include <hamon/render/vulkan/pipeline_depth_stencil_state.hpp>
#include <hamon/render/vulkan/pipeline_color_blend_state.hpp>
#include <hamon/render/vulkan/pipeline_shader_stage.hpp>
#include <hamon/render/vulkan/pipeline_dynamic_state.hpp>
#include <hamon/render/vulkan/pipeline_viewport_state.hpp>
#include <hamon/render/vulkan/pipeline_vertex_input_state.hpp>
#include <hamon/render/vulkan/render_pass.hpp>
#include <hamon/render/vulkan/vulkan.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class GraphicsPipeline
{
public:
	explicit GraphicsPipeline(
		vulkan::Device* device,
		vulkan::PipelineLayout* pipeline_layout,
		vulkan::RenderPass* render_pass,
		vulkan::Program const& program,
		render::Geometry const& geometry,
		render::RenderState const& render_state)
		: m_device(device)
	{
		std::vector<::VkDynamicState> const dynamic_state_enables
		{
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR,
		};

		auto const vertex_input_state           = vulkan::PipelineVertexInputState(geometry.GetLayout());
		auto const input_assembly_state         = vulkan::PipelineInputAssemblyState(geometry.GetPrimitiveTopology());
		auto const dynamic_state                = vulkan::PipelineDynamicState(dynamic_state_enables);
		auto const viewport_state               = vulkan::PipelineViewportState();
		auto const rasterization_state          = vulkan::PipelineRasterizationState(render_state.rasterizer_state);
		auto const multisample_state            = vulkan::PipelineMultisampleState(VK_SAMPLE_COUNT_1_BIT);
		auto const pipeline_depth_stencil_state = vulkan::PipelineDepthStencilState(render_state.depth_stencil_state);
		auto const color_blend_state            = vulkan::PipelineColorBlendState(render_state.blend_state);

		std::vector<::VkPipelineShaderStageCreateInfo>	shader_stages;
		for (auto const& shader : program.GetShaders())
		{
			shader_stages.push_back(vulkan::PipelineShaderStage(shader));
		}

		::VkGraphicsPipelineCreateInfo info{};
		info.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		info.pNext               = nullptr;
		info.flags               = 0;
		info.stageCount          = static_cast<std::uint32_t>(shader_stages.size());	// TODO
		info.pStages             = shader_stages.data();	// TODO
		info.pVertexInputState   = &vertex_input_state.Get();
		info.pInputAssemblyState = &input_assembly_state;
		info.pTessellationState  = nullptr;
		info.pViewportState      = &viewport_state;
		info.pRasterizationState = &rasterization_state;
		info.pMultisampleState   = &multisample_state;
		info.pDepthStencilState  = &pipeline_depth_stencil_state;
		info.pColorBlendState    = &color_blend_state.Get();
		info.pDynamicState       = &dynamic_state;
		info.layout              = pipeline_layout->Get();
		info.renderPass          = render_pass->Get();
		info.subpass             = 0;
		info.basePipelineHandle  = VK_NULL_HANDLE;
		info.basePipelineIndex   = 0;

		m_pipeline = m_device->CreateGraphicsPipeline(VK_NULL_HANDLE, info);
	}

	~GraphicsPipeline()
	{
		m_device->DestroyPipeline(m_pipeline);
	}

	void Bind(vulkan::CommandBuffer* command_buffer)
	{
		command_buffer->BindPipeline(VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
	}

private:
	::VkPipeline		m_pipeline {VK_NULL_HANDLE};
	vulkan::Device*		m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_GRAPHICS_PIPELINE_HPP
