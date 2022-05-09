/**
 *	@file	uniform.hpp
 *
 *	@brief	Uniform
 */

#ifndef HAMON_RENDER_DETAIL_UNIFORM_HPP
#define HAMON_RENDER_DETAIL_UNIFORM_HPP

#include <algorithm>	// ranges::copy
#include <concepts>		// copy_constructible
#include <ranges>		// ranges::data, ranges::range
#include <memory>		// addressof, shared_ptr

namespace hamon
{

inline namespace render
{

namespace detail
{

class UniformBase
{
public:
	virtual ~UniformBase(){}

	virtual void const* GetData(void) const = 0;
};

template <typename T>
class Uniform : public UniformBase
{
public:
	explicit Uniform(T const& value)
		requires std::copy_constructible<T>
		: m_value{value}
	{}

	explicit Uniform(T const& value)
	{
		std::ranges::copy(value, std::ranges::data(m_value));
	}

	void const* GetData(void) const override
	{
		return GetDataImpl();
	}

private:
	void const* GetDataImpl(void) const
		requires std::ranges::range<T>
	{
		return std::ranges::data(m_value);
	}

	void const* GetDataImpl(void) const
	{
		return std::addressof(m_value);
	}

private:
	T	m_value;
};

class UniformProxy
{
public:
	explicit UniformProxy(std::shared_ptr<UniformBase>& ref)
		: m_ref(ref)
	{}

	template <typename T>
	UniformProxy& operator=(T const& value)
	{
		m_ref = std::make_shared<Uniform<T>>(value);
		return *this;
	}

private:
	std::shared_ptr<UniformBase>&	m_ref;
};


}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_UNIFORM_HPP
