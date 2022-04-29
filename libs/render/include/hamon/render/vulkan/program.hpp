/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_VULKAN_PROGRAM_HPP
#define HAMON_RENDER_VULKAN_PROGRAM_HPP

#include <hamon/render/vulkan/shader.hpp>
#include <hamon/render/vulkan/descriptor_set_layout.hpp>
#include <hamon/render/vulkan/uniform_buffer.hpp>
#include <hamon/render/vulkan/uniform_buffer_descriptor.hpp>
#include <hamon/render/vulkan/spirv_program.hpp>
#include <hamon/render/vulkan/spirv_reflection.hpp>
#include <hamon/render/program.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Program
{
public:
	explicit Program(vulkan::Device* device, render::Program const& program)
		: m_spirv_program(program)
	{
		for (auto const& shader : m_spirv_program.GetShaders())
		{
			m_shaders.emplace_back(device, shader.GetStage(), shader.GetCode());
		}

		SpirvReflection reflection(m_spirv_program);
		CreateDescriptorSetLayouts(device, reflection);

		for (auto const& uniform_buffer : reflection.GetUniformBuffers())
		{
			m_uniform_buffer_descriptors.emplace_back(uniform_buffer);
		}
	}
	
	void LoadUniforms(
		vulkan::UniformBuffer* uniform_buffer,
		render::Uniforms const& uniforms)
	{
		for (auto& uniform_buffer_descriptor : m_uniform_buffer_descriptors)
		{
			uniform_buffer_descriptor.LoadUniforms(uniform_buffer, uniforms);
		}
	}

	auto const& GetShaders(void) const
	{
		return m_shaders;
	}

	auto GetDescriptorSetLayouts(void) const
	{
		std::vector<::VkDescriptorSetLayout> result;
		for (auto const& descriptor_set_layout : m_descriptor_set_layouts)
		{
			result.push_back(descriptor_set_layout.Get());
		}
		return result;
	}

	auto CreateWriteDescriptorSets(std::vector<::VkDescriptorSet> const& descriptor_sets)
	{
		std::vector<::VkWriteDescriptorSet> writes;
		for (auto& uniform_buffer_descriptor : m_uniform_buffer_descriptors)
		{
			writes.push_back(uniform_buffer_descriptor.CreateWriteDescriptorSet(descriptor_sets));
		}
		return writes;
	}

private:
	void CreateDescriptorSetLayouts(vulkan::Device* device, SpirvReflection const& reflection)
	{
		std::vector<std::vector<::VkDescriptorSetLayoutBinding>>	layout_binding_mat;
		layout_binding_mat.resize(reflection.GetMaxSet() + 1);

		for (auto const& uniform_buffer : reflection.GetUniformBuffers())
		{
			::VkDescriptorSetLayoutBinding layout_binding{};
			layout_binding.binding            = uniform_buffer.binding;
			layout_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			layout_binding.descriptorCount    = 1;
			layout_binding.stageFlags         = vulkan::ShaderStage(uniform_buffer.stage);
			layout_binding.pImmutableSamplers = NULL;
			
			layout_binding_mat[uniform_buffer.set].push_back(layout_binding);
		}

		for (auto const& layout_bindings : layout_binding_mat)
		{
			m_descriptor_set_layouts.emplace_back(
				device,
				layout_bindings);
		}
	}

private:
	vulkan::SpirvProgram							m_spirv_program;
	std::vector<vulkan::Shader>						m_shaders;
	std::vector<vulkan::DescriptorSetLayout>		m_descriptor_set_layouts;
	std::vector<vulkan::UniformBufferDescriptor>	m_uniform_buffer_descriptors;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_PROGRAM_HPP
