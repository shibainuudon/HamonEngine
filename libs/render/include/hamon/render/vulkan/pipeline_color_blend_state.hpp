/**
 *	@file	pipeline_color_blend_state.hpp
 *
 *	@brief	PipelineColorBlendState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_COLOR_BLEND_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_COLOR_BLEND_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/blend_factor.hpp>
#include <hamon/render/vulkan/blend_operation.hpp>
#include <hamon/render/vulkan/color_write_mask.hpp>
#include <hamon/render/vulkan/logic_operation.hpp>
#include <hamon/render/blend_state.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class PipelineColorBlendState
{
public:
	explicit PipelineColorBlendState(render::BlendState const& state)
	{
		{
			::VkPipelineColorBlendAttachmentState att;
			att.blendEnable         = state.blend_enable;
			att.srcColorBlendFactor = vulkan::BlendFactor(state.color_src_factor);
			att.dstColorBlendFactor = vulkan::BlendFactor(state.color_dest_factor);
			att.colorBlendOp        = vulkan::BlendOperation(state.color_operation);
			att.srcAlphaBlendFactor = vulkan::BlendFactor(state.alpha_src_factor);
			att.dstAlphaBlendFactor = vulkan::BlendFactor(state.alpha_dest_factor);
			att.alphaBlendOp        = vulkan::BlendOperation(state.alpha_operation);
			att.colorWriteMask      = vulkan::ColorWriteMask(state.color_write_mask);
			m_attachments.push_back(att);
		}

		m_info.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_info.pNext             = nullptr;
		m_info.flags             = 0;
		m_info.attachmentCount   = static_cast<std::uint32_t>(m_attachments.size());
		m_info.pAttachments      = m_attachments.data();
		m_info.logicOpEnable     = state.logic_op_enable;
		m_info.logicOp           = vulkan::LogicOperation(state.logic_operation);
		m_info.blendConstants[0] = 1.0f;
		m_info.blendConstants[1] = 1.0f;
		m_info.blendConstants[2] = 1.0f;
		m_info.blendConstants[3] = 1.0f;
	}
	
	::VkPipelineColorBlendStateCreateInfo const* GetAddressOf(void) const { return &m_info; }

private:
	::VkPipelineColorBlendStateCreateInfo				m_info{};
	std::vector<::VkPipelineColorBlendAttachmentState>	m_attachments;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_COLOR_BLEND_STATE_HPP
