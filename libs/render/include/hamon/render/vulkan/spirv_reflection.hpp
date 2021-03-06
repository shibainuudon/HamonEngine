/**
 *	@file	spirv_reflection.hpp
 *
 *	@brief	SpirvReflection
 */

#ifndef HAMON_RENDER_VULKAN_SPIRV_REFLECTION_HPP
#define HAMON_RENDER_VULKAN_SPIRV_REFLECTION_HPP

#include <hamon/render/vulkan/spirv_program.hpp>
#include <spirv_glsl.hpp>
#include <cstdint>
#include <string>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class SpirvReflection
{
public:
	struct Uniform
	{
		struct Member
		{
			std::string		name;
			std::size_t		bytes;
			std::uint32_t	offset;
		};

		render::ShaderStage	stage;
		std::uint32_t	set;
		std::uint32_t	binding;
		std::string		name;
		std::size_t		bytes;
		std::vector<Member>	members;
	};

	void AddUniform(
		spirv_cross::CompilerGLSL const& compiler,
		spirv_cross::SmallVector<spirv_cross::Resource> const& resources,
		render::ShaderStage stage,
		std::vector<Uniform>* uniforms)
	{
		for (auto const& resource : resources)
		{
			auto const spirv_type = compiler.get_type(resource.type_id);
			auto const set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			auto const binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			auto const& name = resource.name;
			auto const bytes =
				(spirv_type.basetype == spirv_cross::SPIRType::Struct) ?
				compiler.get_declared_struct_size(spirv_type) :
				0;
			auto const member_count = spirv_type.member_types.size();

			m_max_set = std::max(m_max_set, set);

			Uniform uniform;
			uniform.stage = stage;
			uniform.set = set;
			uniform.binding = binding;
			uniform.name = name;
			uniform.bytes = bytes;
			uniform.members.resize(member_count);
			for (std::uint32_t i = 0; i < member_count; ++i)
			{
				uniform.members[i].name = compiler.get_member_name(resource.base_type_id, i);
				uniform.members[i].bytes = compiler.get_declared_struct_member_size(spirv_type, i);
				uniform.members[i].offset = compiler.get_member_decoration(resource.base_type_id, i, spv::DecorationOffset);
			}

			uniforms->push_back(uniform);
		}
	}

	explicit SpirvReflection(SpirvProgram const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			auto const stage = shader.GetStage();

			spirv_cross::CompilerGLSL compiler(shader.GetCode());
			auto resources = compiler.get_shader_resources();
			AddUniform(compiler, resources.uniform_buffers, stage, &m_uniform_buffers);
			AddUniform(compiler, resources.sampled_images, stage, &m_combined_image_samplers);
		}
	}

	auto const& GetUniformBuffers(void) const
	{
		return m_uniform_buffers;
	}

	auto const& GetCombinedImageSamplers(void) const
	{
		return m_combined_image_samplers;
	}

	auto const& GetMaxSet(void) const
	{
		return m_max_set;
	}

private:
	std::vector<Uniform>	m_uniform_buffers;
	std::vector<Uniform>	m_combined_image_samplers;
	std::uint32_t			m_max_set {};
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_SPIRV_REFLECTION_HPP
