/**
 *	@file	shader_visibility.hpp
 *
 *	@brief	ShaderVisibility
 */

#ifndef HAMON_RENDER_D3D12_SHADER_VISIBILITY_HPP
#define HAMON_RENDER_D3D12_SHADER_VISIBILITY_HPP

#include <hamon/render/shader_stage.hpp>
#include <hamon/render/d3d/d3d12.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

inline ::D3D12_SHADER_VISIBILITY
ShaderVisibility(render::ShaderStage stage)
{
	switch (stage)
	{
	case render::ShaderStage::Vertex:	return D3D12_SHADER_VISIBILITY_VERTEX;
	case render::ShaderStage::Hull:		return D3D12_SHADER_VISIBILITY_HULL;
	case render::ShaderStage::Domain:	return D3D12_SHADER_VISIBILITY_DOMAIN;
	case render::ShaderStage::Geometry:	return D3D12_SHADER_VISIBILITY_GEOMETRY;
	case render::ShaderStage::Pixel:	return D3D12_SHADER_VISIBILITY_PIXEL;
	default:	return D3D12_SHADER_VISIBILITY_ALL;
	}
}

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_SHADER_VISIBILITY_HPP
