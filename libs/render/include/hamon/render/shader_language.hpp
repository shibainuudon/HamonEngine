/**
 *	@file	shader_language.hpp
 *
 *	@brief	ShaderLanguage
 */

#ifndef HAMON_RENDER_SHADER_LANGUAGE_HPP
#define HAMON_RENDER_SHADER_LANGUAGE_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

enum class ShaderLanguage : std::uint32_t
{
	GLSL,
	HLSL,
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_SHADER_LANGUAGE_HPP
