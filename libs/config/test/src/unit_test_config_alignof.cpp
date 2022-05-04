/**
 *	@file	unit_test_config_alignof.cpp
 *
 *	@brief	HAMON_ALIGNOF のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>

namespace hamon_config_alignof_test
{

struct empty{};

static_assert(1u == HAMON_ALIGNOF(std::int8_t), "");
static_assert(2u == HAMON_ALIGNOF(std::int16_t), "");
static_assert(4u == HAMON_ALIGNOF(std::int32_t), "");
static_assert(8u == HAMON_ALIGNOF(std::int64_t), "");
static_assert(1u == HAMON_ALIGNOF(empty), "");
static_assert(HAMON_ALIGNOF(int*) == HAMON_ALIGNOF(void*), "");

}	// namespace hamon_config_alignof_test
