/**
 *	@file	unit_test_config_likely.cpp
 *
 *	@brief	HAMON_LIKELY のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ConfigTest, LikelyTest)
{
	bool f1 = true;
	bool f2 = false;

	if (HAMON_LIKELY(f1))
	{
		EXPECT_TRUE(f1);
	}
	else
	{
		EXPECT_FALSE(f1);
	}

	if (HAMON_UNLIKELY(f1))
	{
		EXPECT_TRUE(f1);
	}
	else
	{
		EXPECT_FALSE(f1);
	}

	if (HAMON_LIKELY(f2))
	{
		EXPECT_TRUE(f2);
	}
	else
	{
		EXPECT_FALSE(f2);
	}

	if (HAMON_UNLIKELY(f2))
	{
		EXPECT_TRUE(f2);
	}
	else
	{
		EXPECT_FALSE(f2);
	}
}
