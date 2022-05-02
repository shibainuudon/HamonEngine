/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler
 */

#ifndef HAMON_RENDER_GL_SAMPLER_HPP
#define HAMON_RENDER_GL_SAMPLER_HPP

#include <hamon/render/sampler.hpp>
#include <hamon/render/gl/filter_mode.hpp>
#include <hamon/render/gl/sampler_address_mode.hpp>
#include <hamon/render/gl/border_color.hpp>
#include <hamon/render/gl/comparison_func.hpp>
#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

class Sampler
{
public:
	explicit Sampler(render::Sampler const& sampler)
	{
		gl::glCreateSamplers(1, &m_id);

		gl::glSamplerParameteri(m_id, GL_TEXTURE_MIN_FILTER, gl::FilterMode(sampler.min_filter, sampler.mip_filter));
		gl::glSamplerParameteri(m_id, GL_TEXTURE_MAG_FILTER, gl::FilterMode(sampler.mag_filter));
		gl::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_S, gl::SamplerAddressMode(sampler.address_mode_u));
		gl::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_T, gl::SamplerAddressMode(sampler.address_mode_v));
		gl::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_R, gl::SamplerAddressMode(sampler.address_mode_w));
		gl::glSamplerParameterf(m_id, GL_TEXTURE_MIN_LOD, sampler.min_lod);
		gl::glSamplerParameterf(m_id, GL_TEXTURE_MAX_LOD, sampler.max_lod);
		gl::glSamplerParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, gl::BorderColor(sampler.border_color).data());
		if (sampler.compare_enable)
		{
			gl::glSamplerParameteri(m_id, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		}
		else
		{
			gl::glSamplerParameteri(m_id, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		}
		gl::glSamplerParameteri(m_id, GL_TEXTURE_COMPARE_FUNC, gl::ComparisonFunc(sampler.compare_operation));

		// TODO
		//float				mip_lod_bias;
		//bool				anisotropy_enable;
		//float				max_anisotropy;
	}

	~Sampler()
	{
		gl::glDeleteSamplers(1, &m_id);
	}

	void Bind(::GLint location) const
	{
		gl::glBindSampler(location, m_id);
	}

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_SAMPLER_HPP
