/**
 *	@file	unit_test_config_alignas.cpp
 *
 *	@brief	HAMON_ALIGNAS のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4324)	// __declspec(align()) のために構造体がパッドされました。

namespace hamon_config_alignas_test
{

struct HAMON_ALIGNAS(  1) AlignedType1 {};
struct HAMON_ALIGNAS(  2) AlignedType2 {};
struct HAMON_ALIGNAS(  4) AlignedType4 {};
struct HAMON_ALIGNAS(  8) AlignedType8 {};
struct HAMON_ALIGNAS( 16) AlignedType16 {};
struct HAMON_ALIGNAS( 32) AlignedType32 {};
struct HAMON_ALIGNAS( 64) AlignedType64 {};
struct HAMON_ALIGNAS(128) AlignedType128 {};
//struct HAMON_ALIGNAS(256) AlignedType256 {};

struct Foo
{
	HAMON_ALIGNAS(  1) char m1;
	HAMON_ALIGNAS(  2) char m2;
	HAMON_ALIGNAS(  4) char m4;
	HAMON_ALIGNAS(  8) char m8;
	HAMON_ALIGNAS( 16) char m16;
	HAMON_ALIGNAS( 32) char m32;
	HAMON_ALIGNAS( 64) char m64;
	HAMON_ALIGNAS(128) char m128;
//	HAMON_ALIGNAS(256) char m256;
};

bool is_align_of(void* p, int alignment)
{
	return (reinterpret_cast<std::intptr_t>(p) % alignment) == 0;
}

GTEST_TEST(ConfigTest, AlignasTest)
{
	{
		HAMON_ALIGNAS(  1) static char i1;
		HAMON_ALIGNAS(  2) static char i2;
		HAMON_ALIGNAS(  4) static char i4;
		HAMON_ALIGNAS(  8) static char i8;
		HAMON_ALIGNAS( 16) static char i16;
		HAMON_ALIGNAS( 32) static char i32;
		HAMON_ALIGNAS( 64) static char i64;
		HAMON_ALIGNAS(128) static char i128;
//		HAMON_ALIGNAS(256) static char i256;

		EXPECT_TRUE(is_align_of(&i1,   1));
		EXPECT_TRUE(is_align_of(&i2,   2));
		EXPECT_TRUE(is_align_of(&i4,   4));
		EXPECT_TRUE(is_align_of(&i8,   8));
		EXPECT_TRUE(is_align_of(&i16,  16));
		EXPECT_TRUE(is_align_of(&i32,  32));
		EXPECT_TRUE(is_align_of(&i64,  64));
		EXPECT_TRUE(is_align_of(&i128, 128));
//		EXPECT_TRUE(is_align_of(&i256, 256));
	}
	{
		AlignedType1   t1;
		AlignedType2   t2;
		AlignedType4   t4;
		AlignedType8   t8;
		AlignedType16  t16;
		AlignedType32  t32;
		AlignedType64  t64;
		AlignedType128 t128;
//		AlignedType256 t256;

		EXPECT_TRUE(is_align_of(&t1,   1));
		EXPECT_TRUE(is_align_of(&t2,   2));
		EXPECT_TRUE(is_align_of(&t4,   4));
		EXPECT_TRUE(is_align_of(&t8,   8));
		EXPECT_TRUE(is_align_of(&t16,  16));
		EXPECT_TRUE(is_align_of(&t32,  32));
		EXPECT_TRUE(is_align_of(&t64,  64));
		EXPECT_TRUE(is_align_of(&t128, 128));
//		EXPECT_TRUE(is_align_of(&t256, 256));
	}
	{
		Foo t;
		EXPECT_TRUE(is_align_of(&t.m1,   1));
		EXPECT_TRUE(is_align_of(&t.m2,   2));
		EXPECT_TRUE(is_align_of(&t.m4,   4));
		EXPECT_TRUE(is_align_of(&t.m8,   8));
		EXPECT_TRUE(is_align_of(&t.m16,  16));
		EXPECT_TRUE(is_align_of(&t.m32,  32));
		EXPECT_TRUE(is_align_of(&t.m64,  64));
		EXPECT_TRUE(is_align_of(&t.m128, 128));
//		EXPECT_TRUE(is_align_of(&t.m256, 256));
	}
	{
		HAMON_ALIGNAS_TYPE(AlignedType1  ) static char i1;
		HAMON_ALIGNAS_TYPE(AlignedType2  ) static char i2;
		HAMON_ALIGNAS_TYPE(AlignedType4  ) static char i4;
		HAMON_ALIGNAS_TYPE(AlignedType8  ) static char i8;
		HAMON_ALIGNAS_TYPE(AlignedType16 ) static char i16;
		HAMON_ALIGNAS_TYPE(AlignedType32 ) static char i32;
		HAMON_ALIGNAS_TYPE(AlignedType64 ) static char i64;
		HAMON_ALIGNAS_TYPE(AlignedType128) static char i128;
//		HAMON_ALIGNAS_TYPE(AlignedType256) static char i256;

		EXPECT_TRUE(is_align_of(&i1,   1));
		EXPECT_TRUE(is_align_of(&i2,   2));
		EXPECT_TRUE(is_align_of(&i4,   4));
		EXPECT_TRUE(is_align_of(&i8,   8));
		EXPECT_TRUE(is_align_of(&i16,  16));
		EXPECT_TRUE(is_align_of(&i32,  32));
		EXPECT_TRUE(is_align_of(&i64,  64));
		EXPECT_TRUE(is_align_of(&i128, 128));
//		EXPECT_TRUE(is_align_of(&i256, 256));
	}
}

}	// namespace hamon_config_alignas_test

HAMON_WARNING_POP()
