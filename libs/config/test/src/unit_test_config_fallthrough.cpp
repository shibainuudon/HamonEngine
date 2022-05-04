/**
 *	@file	unit_test_config_fallthrough.cpp
 *
 *	@brief	HAMON_FALLTHROUGH のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wmissing-declarations")

namespace hamon_config_fallthrough_test
{

void f() {}

void fallthrough_test(int n)
{
	switch (n)
	{
	case 1:
	case 2:
		f();
		HAMON_FALLTHROUGH();
	case 3:
		if (n < 2)
		{
			f();
		}
		else
		{
			return;
		}
		HAMON_FALLTHROUGH();
	case 4:
		f();
	}
}

GTEST_TEST(ConfigTest, FallthroughTest)
{
	fallthrough_test(1);
	fallthrough_test(2);
	fallthrough_test(3);
	fallthrough_test(4);
}

}	// namespace hamon_config_fallthrough_test

HAMON_WARNING_POP()
