/**
 *	@file	pixels.hpp
 *
 *	@brief	Pixels
 */

#ifndef HAMON_RENDER_DETAIL_pixels_HPP
#define HAMON_RENDER_DETAIL_pixels_HPP

#include <vector>
#include <cstddef>

namespace hamon
{

inline namespace render
{

namespace detail
{

class Pixels
{
public:
	explicit Pixels(std::size_t bytes, void const* src)
		: m_value(bytes)
	{
		std::memcpy(m_value.data(), src, bytes);
	}
	
	void const* GetData(void) const
	{
		return m_value.empty() ? nullptr : m_value.data();
	}

private:
	std::vector<std::byte>	m_value;
};

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_pixels_HPP
