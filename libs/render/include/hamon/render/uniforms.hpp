/**
 *	@file	uniforms.hpp
 *
 *	@brief	Uniforms
 */

#ifndef HAMON_RENDER_UNIFORMS_HPP
#define HAMON_RENDER_UNIFORMS_HPP

#include <hamon/render/detail/uniform.hpp>
#include <map>
#include <memory>
#include <string>

namespace hamon
{

inline namespace render
{

class Uniforms
{
public:
	detail::UniformProxy operator[](std::string const& key)
	{
		return detail::UniformProxy{m_map[key]};
	}

	detail::UniformBase const* operator[](std::string const& key) const
	{
		auto it = m_map.find(key);
		if (it != m_map.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

private:
	std::map<std::string, std::shared_ptr<detail::UniformBase>>	m_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_UNIFORMS_HPP
