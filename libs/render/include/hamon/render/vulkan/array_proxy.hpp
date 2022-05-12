/**
 *	@file	array_proxy.hpp
 *
 *	@brief	ArrayProxy
 */

#ifndef HAMON_RENDER_VULKAN_ARRAY_PROXY_HPP
#define HAMON_RENDER_VULKAN_ARRAY_PROXY_HPP

#include <cstdint>
#include <cstddef>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

template <typename T>
class ArrayProxy
{
public:
	constexpr ArrayProxy()
		: m_ptr(nullptr)
		, m_size(0)
	{}

	constexpr ArrayProxy(std::nullptr_t)
		: m_ptr(nullptr)
		, m_size(0)
	{}

	template <std::size_t N>
	constexpr ArrayProxy(T const (&arr)[N])
		: m_ptr(arr)
		, m_size(N)
	{}

	constexpr ArrayProxy(std::vector<T> const& vec)
		: m_ptr(vec.empty() ? nullptr : vec.data())
		, m_size(static_cast<std::uint32_t>(vec.size()))
	{}

	constexpr ArrayProxy(T const& value)
		: m_ptr(&value)
		, m_size(1)
	{}

	constexpr T const* GetData(void) const
	{
		return m_ptr;
	}

	constexpr std::uint32_t GetSize(void) const
	{
		return m_size;
	}

private:
	T const*      m_ptr;
	std::uint32_t m_size;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_ARRAY_PROXY_HPP
