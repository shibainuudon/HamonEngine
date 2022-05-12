/**
 *	@file	pipeline_vertex_input_state.hpp
 *
 *	@brief	PipelineVertexInputState
 */

#ifndef HAMON_RENDER_VULKAN_PIPELINE_VERTEX_INPUT_STATE_HPP
#define HAMON_RENDER_VULKAN_PIPELINE_VERTEX_INPUT_STATE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/format.hpp>
#include <hamon/render/vertex_layout.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class PipelineVertexInputState
{
public:
	explicit PipelineVertexInputState(render::VertexLayout const& layout)
	{
		{
			::VkVertexInputBindingDescription desc;
			desc.binding   = 0;
			desc.stride    = static_cast<std::uint32_t>(layout.GetBytes());
			desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			m_bindings.push_back(desc);
		}

		std::uint32_t i = 0;
		for (auto const& attr : layout.GetAttributes())
		{
			::VkVertexInputAttributeDescription desc;
			desc.location = i;
			desc.binding  = 0;
			desc.format   = vulkan::Format(attr.type, attr.element_num);
			desc.offset   = static_cast<std::uint32_t>(attr.offset);
			m_attributes.push_back(desc);
			++i;
		}

		m_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		m_info.pNext                           = nullptr;
		m_info.flags                           = 0;
		m_info.vertexBindingDescriptionCount   = static_cast<std::uint32_t>(m_bindings.size());	// TODO
		m_info.pVertexBindingDescriptions      = m_bindings.data();	// TODO
		m_info.vertexAttributeDescriptionCount = static_cast<std::uint32_t>(m_attributes.size());	// TODO
		m_info.pVertexAttributeDescriptions    = m_attributes.data();	// TODO
	}

	::VkPipelineVertexInputStateCreateInfo const& Get(void) const
	{
		return m_info;
	}

private:
	::VkPipelineVertexInputStateCreateInfo				m_info{};
	std::vector<::VkVertexInputBindingDescription>		m_bindings;
	std::vector<::VkVertexInputAttributeDescription>	m_attributes;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PIPELINE_VERTEX_INPUT_STATE_HPP
