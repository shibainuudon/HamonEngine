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

// ユニークなIDを取得できるクラスのベース
// このクラスを継承したクラスはイミュータブルにしなければいけない
// (つまりコンストラクタで値を設定し、その後変更されない)
// コピーをされる可能性はあるので、コピーされても問題ないようにしなければいけない
class Identifiable
{
public:
	Identifiable() = default;
	
	Identifier const& GetID(void) const { return m_id; }

private:
	Identifier		m_id;
};

}	// namespace detail

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_DETAIL_IDENTIFIABLE_HPP
