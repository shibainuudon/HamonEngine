/**
 *	@file	index_array.hpp
 *
 *	@brief	IndexArray
 */

#ifndef HAMON_RENDER_DETAIL_INDEX_ARRAY_HPP
#define HAMON_RENDER_DETAIL_INDEX_ARRAY_HPP

#include <hamon/render/index_type.hpp>
#include <cstddef>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace detail
{

class IndexArrayBase
{
public:
	virtual ~IndexArrayBase()
	{
	}

	virtual std::size_t GetCount(void) const = 0;
	virtual std::size_t GetBytes(void) const = 0;
	virtual void const* GetData(void) const = 0;
	virtual IndexType GetType(void) const = 0;
};

template <typename T>
class IndexArray : public IndexArrayBase
{
public:
	template <typename Iterator>
	IndexArray(Iterator first, Iterator last)
		: m_value(first, last)
	{
	}

	std::size_t GetCount(void) const override
	{
		return m_value.size();
	}

	std::size_t GetBytes(void) const override
	{
		return sizeof(T) * m_value.size();
	}

	void const* GetData(void) const override
	{
		return m_value.empty() ? nullptr : m_value.data();
	}
	
	IndexType GetType(void) const override
	{
		return GetIndexType<T>::value;
	}

private:
	std::vector<T>	m_value;
};

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_INDEX_ARRAY_HPP
