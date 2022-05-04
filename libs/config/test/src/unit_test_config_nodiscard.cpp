/**
 *	@file	unit_test_config_nodiscard.cpp
 *
 *	@brief	HAMON_NODISCARD のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_nodiscard_test
{

HAMON_NODISCARD int func()
{
	return 42;
}

GTEST_TEST(ConfigTest, NoDiscardTest)
{
	//func();
	int t = func();
	(void)t;
}

}	// namespace hamon_config_nodiscard_test
