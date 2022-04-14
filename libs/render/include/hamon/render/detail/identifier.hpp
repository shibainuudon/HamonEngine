/**
 *	@file	identifier.hpp
 *
 *	@brief	Identifier
 */

#ifndef HAMON_RENDER_DETAIL_IDENTIFIER_HPP
#define HAMON_RENDER_DETAIL_IDENTIFIER_HPP

#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace detail
{

class Identifier
{
public:
	using ValueType = std::uint64_t;

public:
	Identifier()
		: m_value(Generator::GetInstance().GetValue())
	{
	}

	ValueType GetValue(void) const { return m_value; }

private:
	class Generator
	{
	public:
		static Generator& GetInstance(void)
		{
			static Generator instance;
			return instance;
		}

		ValueType GetValue(void)
		{
			return m_value++;
		}

	private:
		ValueType	m_value{0};
	};

private:
	ValueType	m_value;
};

inline bool operator==(Identifier const& lhs, Identifier const& rhs)
{
	return lhs.GetValue() == rhs.GetValue();
}

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#include <functional>

namespace std
{

template <>
struct hash<hamon::render::detail::Identifier>
{
	std::size_t operator()(hamon::render::detail::Identifier const& arg) const
	{
		using type = hamon::render::detail::Identifier::ValueType;
		return std::hash<type>{}(arg.GetValue());
	}
};

}	// namespace std

#endif // HAMON_RENDER_DETAIL_IDENTIFIER_HPP
