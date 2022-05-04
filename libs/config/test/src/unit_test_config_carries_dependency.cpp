/**
 *	@file	unit_test_config_carries_dependency.cpp
 *
 *	@brief	HAMON_CARRIES_DEPENDENCY のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_carries_dependency_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4648)	// 標準属性 'carries_dependency' は無視されます

HAMON_CARRIES_DEPENDENCY void f()
{
}

void g(int* r HAMON_CARRIES_DEPENDENCY)
{
	(void)r;
}

HAMON_WARNING_POP()

GTEST_TEST(ConfigTest, CarriesDependencyTest)
{
	f();
	g(nullptr);
}

}	// namespace hamon_config_carries_dependency_test
