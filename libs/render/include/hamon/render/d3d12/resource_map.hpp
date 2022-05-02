/**
 *	@file	resource_map.hpp
 *
 *	@brief	ResourceMap
 */

#ifndef HAMON_RENDER_D3D12_RESOURCE_MAP_HPP
#define HAMON_RENDER_D3D12_RESOURCE_MAP_HPP

#include <hamon/render/d3d12/command_allocator.hpp>
#include <hamon/render/d3d12/command_list.hpp>
//#include <hamon/render/d3d12/pipeline_state.hpp>
//#include <hamon/render/d3d12/program.hpp>
#include <hamon/render/d3d12/geometry.hpp>
#include <hamon/render/d3d12/sampler.hpp>
#include <hamon/render/d3d12/texture.hpp>
#include <hamon/render/program.hpp>
#include <hamon/render/geometry.hpp>
#include <hamon/render/sampler.hpp>
#include <hamon/render/texture.hpp>
#include <hamon/render/render_state.hpp>
#include <hamon/render/detail/hash_combine.hpp>
#include <unordered_map>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Program;
class PipelineState;

class ResourceMap
{
public:
	ResourceMap(d3d12::Device* device)
	{
		m_command_queue     = std::make_unique<d3d12::CommandQueue>(device);
		m_command_allocator = std::make_unique<d3d12::CommandAllocator>(device);
		m_command_list      = std::make_unique<d3d12::CommandList>(device, m_command_allocator.get());
		m_command_list->Close();
		m_fence             = std::make_unique<d3d12::Fence>(device, 1);
	}

	std::shared_ptr<d3d12::PipelineState> GetPipelineState(
		d3d12::Device* device,
		render::Geometry const& geometry,
		render::Program const& program,
		render::RenderState const& render_state)
	{
		auto id = render::detail::HashCombine(
			geometry.GetID(),
			program.GetID(),
			render_state);
		return GetOrCreate<d3d12::PipelineState>(
			m_pipeline_state_map,
			id,
			device,
			*GetGeometry(device, geometry),
			*GetProgram(device, program),
			render_state);
	}

	std::shared_ptr<d3d12::Program> GetProgram(d3d12::Device* device, render::Program const& program)
	{
		return GetOrCreate<d3d12::Program>(
			m_program_map, program.GetID(), device, program);
	}
	
	std::shared_ptr<d3d12::Geometry> GetGeometry(d3d12::Device* device, render::Geometry const& geometry)
	{
		return GetOrCreate<d3d12::Geometry>(
			m_geometry_map, geometry.GetID(), device, geometry);
	}

	std::shared_ptr<d3d12::Sampler> GetSampler(render::Sampler const& sampler)
	{
		auto id = render::detail::HashCombine(sampler);
		return GetOrCreate<d3d12::Sampler>(
			m_sampler_map, id, sampler);
	}

	std::shared_ptr<d3d12::Texture> GetTexture(d3d12::Device* device, render::Texture const& texture)
	{
		return GetOrCreate<d3d12::Texture>(
			m_texture_map, texture.GetID(),
			device,
			m_command_allocator.get(),
			m_command_list.get(),
			m_command_queue.get(),
			m_fence.get(),
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
	std::unique_ptr<d3d12::CommandAllocator>	m_command_allocator;
	std::unique_ptr<d3d12::CommandList>			m_command_list;
	std::unique_ptr<d3d12::CommandQueue>		m_command_queue;
	std::unique_ptr<d3d12::Fence>				m_fence;
	std::unordered_map<std::size_t, std::shared_ptr<d3d12::PipelineState>>		m_pipeline_state_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d12::Program>>		m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d12::Geometry>>	m_geometry_map;
	std::unordered_map<std::size_t,        std::shared_ptr<d3d12::Sampler>>		m_sampler_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d12::Texture>>		m_texture_map;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_RESOURCE_MAP_HPP
