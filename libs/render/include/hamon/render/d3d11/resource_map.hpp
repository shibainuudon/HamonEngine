/**
 *	@file	resource_map.hpp
 *
 *	@brief	ResourceMap
 */

#ifndef HAMON_RENDER_D3D11_RESOURCE_MAP_HPP
#define HAMON_RENDER_D3D11_RESOURCE_MAP_HPP

//#include <hamon/render/d3d11/program.hpp>
#include <hamon/render/d3d11/geometry.hpp>
#include <hamon/render/d3d11/sampler.hpp>
#include <hamon/render/d3d11/texture.hpp>
#include <hamon/render/program.hpp>
#include <hamon/render/geometry.hpp>
#include <hamon/render/sampler.hpp>
#include <hamon/render/texture.hpp>
#include <hamon/render/detail/hash_combine.hpp>
#include <unordered_map>
#include <memory>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Program;

class ResourceMap
{
public:
	std::shared_ptr<d3d11::Program>
	GetProgram(d3d11::Device* device, render::Program const& program)
	{
		return GetOrCreate<d3d11::Program>(
			m_program_map, program.GetID(), device, program);
	}
	
	std::shared_ptr<d3d11::Geometry>
	GetGeometry(d3d11::Device* device, render::Geometry const& geometry)
	{
		return GetOrCreate<d3d11::Geometry>(
			m_geometry_map, geometry.GetID(), device, geometry);
	}

	std::shared_ptr<d3d11::Sampler>
	GetSampler(d3d11::Device* device, render::Sampler const& sampler)
	{
		auto id = render::detail::HashCombine(sampler);
		return GetOrCreate<d3d11::Sampler>(
			m_sampler_map, id, device, sampler);
	}

	std::shared_ptr<d3d11::Texture>
	GetTexture(d3d11::Device* device, render::Texture const& texture)
	{
		return GetOrCreate<d3d11::Texture>(
			m_texture_map, texture.GetID(), device, texture);
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
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d11::Program>>		m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d11::Geometry>>	m_geometry_map;
	std::unordered_map<std::size_t,        std::shared_ptr<d3d11::Sampler>>		m_sampler_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<d3d11::Texture>>		m_texture_map;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_RESOURCE_MAP_HPP
