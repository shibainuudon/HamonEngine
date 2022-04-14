/**
 *	@file	identifiable.hpp
 *
 *	@brief	Identifiable
 */

#ifndef HAMON_RENDER_DETAIL_IDENTIFIABLE_HPP
#define HAMON_RENDER_DETAIL_IDENTIFIABLE_HPP

#include <hamon/render/detail/identifier.hpp>

namespace hamon
{

inline namespace render
{

namespace detail
{

class Identifiable
{
public:
	Identifiable() = default;
	
	// noncopyable
	Identifiable(Identifiable const&) = delete;
	Identifiable& operator=(Identifiable const&) = delete;
	
	// movable
	Identifiable(Identifiable &&) = default;
	Identifiable& operator=(Identifiable &&) = default;

	Identifier const& GetID(void) const { return m_id; }

private:
	Identifier		m_id;
};

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_IDENTIFIABLE_HPP
