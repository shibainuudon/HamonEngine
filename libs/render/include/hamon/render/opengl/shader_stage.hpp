/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage
 */

#ifndef HAMON_RENDER_OPENGL_SHADER_STAGE_HPP
#define HAMON_RENDER_OPENGL_SHADER_STAGE_HPP

#include <hamon/render/shader_stage.hpp>
#include <hamon/render/opengl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

inline ::GLenum ShaderStage(render::ShaderStage stage)
{
	switch (stage)
	{
	case render::ShaderStage::Compute:					return GL_COMPUTE_SHADER;
	case render::ShaderStage::Vertex:					return GL_VERTEX_SHADER;
	case render::ShaderStage::TessellationControl:		return GL_TESS_CONTROL_SHADER;
	case render::ShaderStage::TessellationEvaluation:	return GL_TESS_EVALUATION_SHADER;
	case render::ShaderStage::Geometry:					return GL_GEOMETRY_SHADER;
	case render::ShaderStage::Fragment:					return GL_FRAGMENT_SHADER;
	}
	return GL_VERTEX_SHADER;
}

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_OPENGL_SHADER_STAGE_HPP
