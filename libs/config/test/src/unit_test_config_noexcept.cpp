/**
 *	@file	unit_test_config_noexcept.cpp
 *
 *	@brief
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_noexcept_test
{

void f1();
void f2() HAMON_NOEXCEPT;
void f3() HAMON_NOEXCEPT_OR_NOTHROW;
void f4() HAMON_NOEXCEPT_IF(true);
void f5() HAMON_NOEXCEPT_IF(false);
void f6() HAMON_NOEXCEPT_IF(HAMON_NOEXCEPT_EXPR(f1()));
void f7() HAMON_NOEXCEPT_IF(HAMON_NOEXCEPT_EXPR(f2()));
void f8() HAMON_NOEXCEPT_IF_EXPR(f1());
void f9() HAMON_NOEXCEPT_IF_EXPR(f2());

GTEST_TEST(ConfigTest, NoexceptTest)
{
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
	static_assert(!HAMON_NOEXCEPT_EXPR(f1()), "");
	static_assert( HAMON_NOEXCEPT_EXPR(f2()), "");
	static_assert( HAMON_NOEXCEPT_EXPR(f3()), "");
	static_assert( HAMON_NOEXCEPT_EXPR(f4()), "");
	static_assert(!HAMON_NOEXCEPT_EXPR(f5()), "");
	static_assert(!HAMON_NOEXCEPT_EXPR(f6()), "");
	static_assert( HAMON_NOEXCEPT_EXPR(f7()), "");
	static_assert(!HAMON_NOEXCEPT_EXPR(f8()), "");
	static_assert( HAMON_NOEXCEPT_EXPR(f9()), "");
#endif
}

}	// namespace hamon_config_noexcept_test
