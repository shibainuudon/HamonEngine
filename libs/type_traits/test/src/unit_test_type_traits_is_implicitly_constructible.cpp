/**
 *	@file	unit_test_type_traits_is_implicitly_constructible.cpp
 *
 *	@brief	is_implicitly_constructible のテスト
 */

#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_implicitly_constructible_v<__VA_ARGS__>      == b, #__VA_ARGS__);	\
	static_assert(hamon::is_implicitly_constructible<__VA_ARGS__>::value == b, #__VA_ARGS__);	\
	static_assert(hamon::is_implicitly_constructible<__VA_ARGS__>()      == b, #__VA_ARGS__)

#else

#define HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_implicitly_constructible<__VA_ARGS__>::value == b, #__VA_ARGS__);	\
	static_assert(hamon::is_implicitly_constructible<__VA_ARGS__>()      == b, #__VA_ARGS__)

#endif

namespace hamon_type_traits_test
{

namespace is_implicitly_constructible_test
{

// defaultコンストラクタを持たない
struct S1
{
	S1() = delete;
};

// トリビアルなdefaultコンストラクタを持つ
struct S2
{
	int n;
};

// defaultコンストラクタを持つ
struct S3
{
	S3();
};

// explicitなdefaultコンストラクタを持つ
struct S4
{
	explicit S4();
};

// 引数を1つ取るコンストラクタを持つ
struct S5
{
	S5(int);
};

// explicitな引数を1つ取るコンストラクタを持つ
struct S6
{
	explicit S6(int);
};

// 引数を2つ取るコンストラクタを持つ
struct S7
{
	S7(int, float);
};

// explicitな引数を2つ取るコンストラクタを持つ
struct S8
{
	explicit S8(int, float);
};

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S2);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S3);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int);
#if defined(HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT)
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S2, int);
#else
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int);
#endif
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S5, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, float);
#if defined(HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT)
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S2, float);
#else
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int);
#endif
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, float);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S7, int, float);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int, float);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, int, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int, int);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  const int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  volatile int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int*, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int*, int const*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const*, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const*, int const*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int*, int*, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int*, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int*, int&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int&, int&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&, int const&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&, int&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const&, int&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const&, int const&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int&&, int);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&&, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&&, int&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int&&, int&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&&, int const&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const&&, int&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int const&&, int const&&);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&)[2]);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&)[]);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&&)[]);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, void);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, const void);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, volatile void);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  void*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  void*, void*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, void*, void const*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  void*, int*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int*,  void*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  std::nullptr_t);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  std::nullptr_t, std::nullptr_t);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, std::nullptr_t, void*);
HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, std::nullptr_t, int);

}	// namespace is_implicitly_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_IMPLICITLY_CONSTRUCTIBLE_TEST
