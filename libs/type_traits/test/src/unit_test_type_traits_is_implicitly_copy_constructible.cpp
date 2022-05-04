/**
 *	@file	unit_test_type_traits_is_implicitly_copy_constructible.cpp
 *
 *	@brief	is_implicitly_copy_constructible のテスト
 */

#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_copy_constructible_v<T>      == b, #T ", " #b);	\
	static_assert(hamon::is_implicitly_copy_constructible<T>::value == b, #T ", " #b);	\
	static_assert(hamon::is_implicitly_copy_constructible<T>()      == b, #T ", " #b)

#else

#define HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_copy_constructible<T>::value == b, #T ", " #b);	\
	static_assert(hamon::is_implicitly_copy_constructible<T>()      == b, #T ", " #b)

#endif

namespace hamon_type_traits_test
{

namespace is_implicitly_copy_constructible_test
{

// トリビアルな copy コンストラクタを持つ
struct Trivial
{
	int n;
};

// implicit な copy コンストラクタを持つ
struct Implicit
{
	Implicit(const Implicit&);
};

// implicit な copy コンストラクタを持つクラスをメンバに持つ
struct ImplicitMember
{
	Implicit	member;
};

// explicit な copy コンストラクタを持つ
struct Explicit
{
	explicit Explicit(const Explicit&);
};

// explicit な copy コンストラクタを持つクラスをメンバに持つ
struct ExplicitMember
{
	Explicit	member;
};

// copyコンストラクタを持たない
struct NonCopyable
{
	NonCopyable(const NonCopyable&) = delete;
};

// copyコンストラクタを持たないクラスをメンバに持つ
struct NonCopyableMember
{
	NonCopyable	member;
};

HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Trivial);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  ImplicitMember);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  ExplicitMember);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, NonCopyable);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, NonCopyableMember);

HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	               int);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	const          int);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	      volatile int);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	const volatile int);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int*);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int&&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[]);

HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,                void);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const          void);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile void);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,                 Implicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  const          Implicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile Implicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile Implicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit*);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit&&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit(&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit(&)[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit(&&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit(&&)[]);

HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,                Explicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const          Explicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile Explicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile Explicit);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit*);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit&&);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit(&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit(&)[]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit(&&)[2]);
HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit(&&)[]);

}	// namespace is_implicitly_copy_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST
