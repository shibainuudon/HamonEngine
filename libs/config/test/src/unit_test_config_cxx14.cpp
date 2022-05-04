/**
 *	@file	unit_test_config_cxx14.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <array>
#include <utility>
#include <vector>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4189)	// ローカル変数が初期化されましたが、参照されていません
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
HAMON_WARNING_DISABLE_CLANG("-Wmissing-braces")

namespace hamon_config_cxx14_test
{

GTEST_TEST(ConfigTest, Cxx14AlignedNewTest)
{
#if defined(HAMON_HAS_CXX14_BINARY_LITERALS)
	int x = 0b1010;
	int y = 0B1111000011001010;

	EXPECT_EQ(10, x);
	EXPECT_EQ(61642, y);
#endif
}

namespace return_type_deduction_test
{

#if defined(HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION)
auto f1()
{
	return 42;
}

decltype(auto) f2(int& r)
{
	return r;
}
#endif

GTEST_TEST(ConfigTest, Cxx14ReturnTypeDeductionTest)
{
#if defined(HAMON_HAS_CXX14_RETURN_TYPE_DEDUCTION)
	int x = f1();
	int& r = f2(x);
	EXPECT_EQ(42, x);
	r = 10;
	EXPECT_EQ(10, x);
#endif
}

}	// namespace return_type_deduction_test

namespace init_captures_test
{

int increment(int x)
{
	return x + 1;
}

GTEST_TEST(ConfigTest, Cxx14InitCapturesTest)
{
#if defined(HAMON_HAS_CXX14_INIT_CAPTURES)
	{
		auto f = [a = increment(3)](int b) { return a + b; };
		int result = f(2);
		EXPECT_EQ(6, result);
	}
	{
		std::vector<int> v;
		auto f = [x = std::move(v)]{};
	}
	{
		int a = 3;
		auto f = [b = a, &c = a] { (void)b; (void)c; };
		(void)f;
	}
#endif	// defined(HAMON_HAS_CXX14_INIT_CAPTURES)
}

}	// namespace init_captures_test

GTEST_TEST(ConfigTest, Cxx14GenericLambdasTest)
{
#if defined(HAMON_HAS_CXX14_GENERIC_LAMBDAS)
	auto plus = [](auto a, auto b) { return a + b; };

	int   result1 = plus(3, 2);
	float result2 = plus(1.5f, 2.5f);

	EXPECT_EQ(5,    result1);
	EXPECT_EQ(4.0f, result2);
#endif	// defined(HAMON_HAS_CXX14_GENERIC_LAMBDAS)
}

namespace variable_templates_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
constexpr T pi = static_cast<T>(3.14159265358979323846);

constexpr float pif = pi<float>;
constexpr double pid = pi<double>;
constexpr long double pild = pi<long double>;

#endif	// defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace variable_templates_test

namespace constexpr_test
{

#if defined(HAMON_HAS_CXX14_CONSTEXPR)
constexpr int f(int a)
{
	int x = a;

	if (x < 0)
	{
		return -x;
	}

	switch (x)
	{
	case 0: return 10;
	case 1: return 20;
	case 2: return 30;
	default: break;
	}

	for (int i = 0; i < 5; ++i)
	{
		x += i + 1;
	}

	int ar[] ={6, 7, 8};
	for (const int& i : ar)
	{
		x += i;
	}

	while (true)
	{
		x += 9;
		break;
	}

	do
	{
		x += 10;
	}
	while (false);

	return x;
}
#endif

GTEST_TEST(ConfigTest, Cxx14ConstexprTest)
{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	constexpr int x = f(10);
	EXPECT_EQ(65, x);
#endif
}

}	// namespace constexpr_test

GTEST_TEST(ConfigTest, Cxx14AggregateNsdmiTest)
{
#if defined(HAMON_HAS_CXX14_AGGREGATE_NSDMI)
	struct S
	{
		int i;
		int j;
		int k = 42;
	};

	S x = { 1, 2, 3 };
	S y = { 4, 5 };
	S a[] = { 1, 2, 3, 4, 5, 6 };
	S b[] = { {1, 2, 3}, {4, 5, 6} };

	EXPECT_EQ( 1, x.i);
	EXPECT_EQ( 2, x.j);
	EXPECT_EQ( 3, x.k);
	EXPECT_EQ( 4, y.i);
	EXPECT_EQ( 5, y.j);
	EXPECT_EQ(42, y.k);
	EXPECT_EQ( 1, a[0].i);
	EXPECT_EQ( 2, a[0].j);
	EXPECT_EQ( 3, a[0].k);
	EXPECT_EQ( 4, a[1].i);
	EXPECT_EQ( 5, a[1].j);
	EXPECT_EQ( 6, a[1].k);
	EXPECT_EQ( 1, b[0].i);
	EXPECT_EQ( 2, b[0].j);
	EXPECT_EQ( 3, b[0].k);
	EXPECT_EQ( 4, b[1].i);
	EXPECT_EQ( 5, b[1].j);
	EXPECT_EQ( 6, b[1].k);
#endif
}

#if defined(HAMON_HAS_CXX14_DEPRECATED)

namespace deprecated_test
{

[[deprecated("please use new_func() function")]]
void old_func() {}

}	// namespace deprecated_test

#endif	// defined(HAMON_HAS_CXX14_DEPRECATED)

GTEST_TEST(ConfigTest, Cxx14DigitSeparatorsTest)
{
#if defined(HAMON_HAS_CXX14_DIGIT_SEPARATORS)
	int decimal_value = 123'456'789;
	int octal_value = 012'34'56;
	int hex_value = 0x1'234'5678;
#if defined(HAMON_HAS_CXX14_BINARY_LITERALS)
	int binary_value = 0b1010'1010'0001;
#endif
	double floating_point_value = 12'345.678'901;
#endif
}

namespace sized_deallocation_test
{

#if defined(HAMON_HAS_CXX14_SIZED_DEALLOCATION)

// TODO

#endif	// defined(HAMON_HAS_CXX14_SIZED_DEALLOCATION)

}	// namespace sized_deallocation_test

}	// namespace hamon_config_cxx14_test

HAMON_WARNING_POP()
