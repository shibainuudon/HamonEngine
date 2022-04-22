/**
 *	@file	uniforms.hpp
 *
 *	@brief	Uniforms
 */

#ifndef HAMON_RENDER_UNIFORMS_HPP
#define HAMON_RENDER_UNIFORMS_HPP

#include <map>
#include <memory>
#include <string>

namespace hamon
{

inline namespace render
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

class Uniforms
{
public:
	UniformProxy operator[](std::string const& key)
	{
		return UniformProxy{m_map[key]};
	}

	UniformBase const* operator[](std::string const& key) const
	{
		auto it = m_map.find(key);
		if (it != m_map.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

private:
	std::map<std::string, std::shared_ptr<UniformBase>>	m_map;
};

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_UNIFORMS_HPP
