/**
 *	@file	program.hpp
 *
 *	@brief	Program
 */

#ifndef HAMON_RENDER_D3D12_PROGRAM_HPP
#define HAMON_RENDER_D3D12_PROGRAM_HPP

#include <hamon/render/program.hpp>
#include <hamon/render/d3d12/shader.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Program
{
public:
	explicit Program(render::Program const& program)
	{
		for (auto const& shader : program.GetShaders())
		{
			m_shaders.emplace_back(shader);
		}
	}

	std::vector<d3d12::Shader> const&
	GetShaders(void) const
	{
		return m_shaders;
	}

private:
	std::vector<d3d12::Shader>	m_shaders;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_PROGRAM_HPP
