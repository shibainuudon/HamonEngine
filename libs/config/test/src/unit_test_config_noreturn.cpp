/**
 *	@file	unit_test_config_noreturn.cpp
 *
 *	@brief	HAMON_NORETURN のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace hamon_config_noreturn_test
{

HAMON_NORETURN void report_error()
{
	throw std::runtime_error("");
}

int func(int x)
{
	if (x > 0)
	{
		return x;
	}

	report_error();
}

GTEST_TEST(ConfigTest, NoReturnTest)
{
	func(1);
}

}	// namespace hamon_config_noreturn_test
