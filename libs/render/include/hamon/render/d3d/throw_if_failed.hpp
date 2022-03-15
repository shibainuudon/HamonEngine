/**
 *	@file	throw_if_failed.hpp
 *
 *	@brief	ThrowIfFailed関数
 */

#ifndef HAMON_RENDER_D3D_THROW_IF_FAILED_HPP
#define HAMON_RENDER_D3D_THROW_IF_FAILED_HPP

#include <string>
#include <stdexcept>

namespace hamon
{

inline namespace render
{


class HResultException : public std::runtime_error
{
public:
	explicit HResultException(::HRESULT res)
		: std::runtime_error(ToString(res))
	{}

private:
	static std::string ToString(::HRESULT res)
	{
		return std::to_string(static_cast<std::uint32_t>(res));
	}
};

inline ::HRESULT ThrowIfFailed(::HRESULT res)
{
	if (FAILED(res))
	{
		throw HResultException(res);
	}
	return res;
}

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D_THROW_IF_FAILED_HPP
