/**
 *	@file	unit_test_type_traits_is_implicitly_default_constructible.cpp
 *
 *	@brief	is_implicitly_default_constructible のテスト
 */

#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_default_constructible_v<T>      == b, #T);	\
	static_assert(hamon::is_implicitly_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_implicitly_default_constructible<T>()      == b, #T)

#else

#define HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_implicitly_default_constructible<T>()      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_implicitly_default_constructible_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
HAMON_WARNING_DISABLE_MSVC(4610)	// ユーザー定義のコンストラクターが必要です。

// defaultコンストラクタを持たない
struct S1
{
	S1(int);
};

// defaultコンストラクタがdeleted
struct S2
{
	S2() = delete;
};

// トリビアルなdefaultコンストラクタを持つ
struct S3
{
	int n;
};

// defaultコンストラクタを持つ
struct S4
{
	S4();
};

// explicitなdefaultコンストラクタを持つ
struct S5
{
	explicit S5() {}
};

// defaultコンストラクタを持つ
struct S6
{
	S6() HAMON_NOEXCEPT;
};

// explicitなdefaultコンストラクタを持つ
struct S7
{
	explicit S7() HAMON_NOEXCEPT;
};

// defaultコンストラクタを持たないクラスをメンバに持つ
struct S1_1
{
	S1 member;
};

// defaultコンストラクタがdeletedクラスをメンバに持つ
struct S2_1
{
	S2 member;
};

// トリビアルなdefaultコンストラクタを持つクラスをメンバに持つ
struct S3_1
{
	S3 member;
};

// defaultコンストラクタを持つクラスをメンバに持つ
struct S4_1
{
	S4 member;
};

// explicitなdefaultコンストラクタを持つクラスをメンバに持つ
struct S5_1
{
	S5 member;
};

// defaultコンストラクタを持つクラスをメンバに持つ
struct S6_1
{
	S6 member;
};

// explicitなdefaultコンストラクタを持つクラスをメンバに持つ
struct S7_1
{
	S7 member;
};

// defaultコンストラクタを持たないクラスを継承する
struct S1_2 : S1
{
};

// defaultコンストラクタがdeletedクラスを継承する
struct S2_2 : S2
{
};

// トリビアルなdefaultコンストラクタを持つクラスを継承する
struct S3_2 : S3
{
};

// defaultコンストラクタを持つクラスを継承する
struct S4_2 : S4
{
};

// explicitなdefaultコンストラクタを持つクラスを継承する
struct S5_2 : S5
{
};

// defaultコンストラクタを持つクラスを継承する
struct S6_2 : S6
{
};

// explicitなdefaultコンストラクタを持つクラスを継承する
struct S7_2 : S7
{
};

HAMON_WARNING_POP()

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7);

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1_1);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2_1);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3_1);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4_1);
#if !(defined(_MSC_VER) && _MSC_VER <= 1930)
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5_1);
#endif
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6_1);
#if !(defined(_MSC_VER) && _MSC_VER <= 1930)
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7_1);
#endif

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1_2);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2_2);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3_2);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4_2);
#if 0
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5_2);
#endif
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6_2);
#if 0
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7_2);
#endif

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const int);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  volatile int);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[2]);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[]);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[]);

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, void);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const void);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, volatile void);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  void*);
HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  std::nullptr_t);

}	// namespace is_implicitly_default_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST
