/**
 *	@file	unit_test_type_traits_is_implicitly_move_constructible.cpp
 *
 *	@brief	is_implicitly_move_constructible のテスト
 */

#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_move_constructible_v<T> == b, #T);	\
	static_assert(hamon::is_implicitly_move_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_implicitly_move_constructible<T>()      == b, #T)

#else

#define HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_implicitly_move_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_implicitly_move_constructible<T>()      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_implicitly_move_constructible_test
{

// トリビアルな move コンストラクタを持つ
struct Trivial
{
	int n;
};

// implicit な move コンストラクタを持つ
struct Implicit
{
	Implicit(Implicit&&);
};

// implicit な move コンストラクタを持つクラスをメンバに持つ
struct ImplicitMember
{
	Implicit	member;
};

// explicit な move コンストラクタを持つ
struct Explicit
{
	explicit Explicit(Explicit&&);
};

// explicit な move コンストラクタを持つクラスをメンバに持つ
struct ExplicitMember
{
	Explicit	member;
};

// move コンストラクタを持たない
struct NonMovable
{
	NonMovable(NonMovable&&) = delete;
};

// move コンストラクタを持たないクラスをメンバに持つ
struct NonMovableMember
{
	NonMovable	member;
};

HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Trivial);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  ImplicitMember);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Explicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  ExplicitMember);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, NonMovable);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, NonMovableMember);

HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,                 int);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  const          int);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,        volatile int);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[]);

HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,                void);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          void);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile void);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,                 Implicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          Implicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile Implicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile Implicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit*);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit&&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Implicit[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Implicit[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&)[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&&)[]);

HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,                Explicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          Explicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile Explicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile Explicit);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit*);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit&&);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Explicit[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Explicit[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&)[]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&&)[2]);
HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&&)[]);

}	// namespace is_implicitly_move_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST
