/**
 *	@file	resource_map.hpp
 *
 *	@brief	ResourceMap
 */

#ifndef HAMON_RENDER_GL_RESOURCE_MAP_HPP
#define HAMON_RENDER_GL_RESOURCE_MAP_HPP

//#include <hamon/render/gl/program.hpp>
#include <hamon/render/gl/geometry.hpp>
#include <hamon/render/gl/sampler.hpp>
#include <hamon/render/gl/texture.hpp>
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

namespace gl
{

class Program;

class ResourceMap
{
public:
	std::shared_ptr<gl::Program> GetProgram(render::Program const& program)
	{
		return GetOrCreate<gl::Program>(
			m_program_map, program.GetID(), program);
	}
	
	std::shared_ptr<gl::Geometry> GetGeometry(render::Geometry const& geometry)
	{
		return GetOrCreate<gl::Geometry>(
			m_geometry_map, geometry.GetID(), geometry);
	}

	std::shared_ptr<gl::Sampler> GetSampler(render::Sampler const& sampler)
	{
		auto id = render::detail::HashCombine(sampler);
		return GetOrCreate<gl::Sampler>(
			m_sampler_map, id, sampler);
	}

	std::shared_ptr<gl::Texture> GetTexture(render::Texture const& texture)
	{
		return GetOrCreate<gl::Texture>(
			m_texture_map, texture.GetID(), texture);
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
	std::unordered_map<detail::Identifier, std::shared_ptr<gl::Program>>	m_program_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<gl::Geometry>>	m_geometry_map;
	std::unordered_map<std::size_t,        std::shared_ptr<gl::Sampler>>	m_sampler_map;
	std::unordered_map<detail::Identifier, std::shared_ptr<gl::Texture>>	m_texture_map;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_RESOURCE_MAP_HPP
