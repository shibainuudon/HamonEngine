/**
 *	@file	resource_map.hpp
 *
 *	@brief	ResourceMap
 */

#ifndef HAMON_RENDER_VULKAN_RESOURCE_MAP_HPP
#define HAMON_RENDER_VULKAN_RESOURCE_MAP_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/program.hpp>
#include <hamon/render/geometry.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/sampler.hpp>
#include <hamon/render/texture.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Program;
class Geometry;
class PipelineLayout;
class GraphicsPipeline;
class Sampler;
class Texture;

class ResourceMap
{
public:
	std::shared_ptr<vulkan::Program>
	GetProgram(vulkan::Device* device, render::Program const& program)
	{
		return GetOrCreate<vulkan::Program>(
			m_program_map, program.GetID(), device, program);
	}

	std::shared_ptr<vulkan::Geometry>
	GetGeometry(vulkan::Device* device, render::Geometry const& geometry)
	{
		return GetOrCreate<vulkan::Geometry>(
			m_geometry_map, geometry.GetID(), device, geometry);
	}

	std::shared_ptr<vulkan::PipelineLayout>
	GetPipelineLayout(vulkan::Device* device, render::Program const& program)
	{
		return GetOrCreate<vulkan::PipelineLayout>(
			m_pipeline_layout_map,
			program.GetID(),
			device,
			GetProgram(device, program).get());
	}

	std::shared_ptr<vulkan::GraphicsPipeline>
	GetGraphicsPipeline(
		vulkan::Device* device,
		vulkan::RenderPass* render_pass,
		render::Geometry const& geometry,
		render::Program const& program,
		render::RenderState const& render_state)
	{
		auto id = render::detail::HashCombine(
			geometry.GetID(),
			program.GetID(),
			render_state);
		return GetOrCreate<vulkan::GraphicsPipeline>(
			m_graphics_pipeline_map,
			id,
			device,
			GetPipelineLayout(device, program).get(),
			render_pass,
			*GetProgram(device, program),
			geometry,
			render_state);
	}

	std::shared_ptr<vulkan::Sampler> GetSampler(
		vulkan::Device* device,
		render::Sampler const& sampler)
	{
		auto id = render::detail::HashCombine(sampler);
		return GetOrCreate<vulkan::Sampler>(
			m_sampler_map, id, device, sampler);
	}

	std::shared_ptr<vulkan::Texture> GetTexture(
		vulkan::Device* device,
		vulkan::CommandPool* command_pool,
		render::Texture const& texture)
	{
		return GetOrCreate<vulkan::Texture>(
			m_texture_map,
			texture.GetID(),
			device,
			command_pool,
			texture);
	}

private:
	template <typename T, typename Map, typename Id, typename... Args>
	typename Map::mapped_type
	GetOrCreate(Map& map, Id const& id, Args&&... args)
	{
		auto it = map.find(id);
		if (it != map.end())
		{
			return it->second;
		}
		else
		{
			auto p = std::make_shared<T>(std::forward<Args>(args)...);
			map[id] = p;
			return p;
		}
	}

private:
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::Program>>	m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::Geometry>>	m_geometry_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::PipelineLayout>>	m_pipeline_layout_map;
	std::unordered_map<std::size_t, std::shared_ptr<vulkan::GraphicsPipeline>>	m_graphics_pipeline_map;
	std::unordered_map<std::size_t,        std::shared_ptr<vulkan::Sampler>>	m_sampler_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<vulkan::Texture>>	m_texture_map;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_RESOURCE_MAP_HPP
