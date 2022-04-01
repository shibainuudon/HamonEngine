/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage
 */

#ifndef HAMON_RENDER_SHADER_STAGE_HPP
#define HAMON_RENDER_SHADER_STAGE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class ShaderStage : std::uint32_t
{
	Compute,
	Vertex,
	Hull,
	Domain,
	Geometry,
	Pixel,

	TessellationControl = Hull,
	TessellationEvaluation = Domain,
	Fragment = Pixel,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SHADER_STAGE_HPP
