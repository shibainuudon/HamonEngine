/**
 *	@file	unit_test_config_cxx20.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <new>			// destroying_delete_t
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#if HAMON_HAS_INCLUDE(<coroutine>) && (HAMON_CXX_STANDARD >= 20) && defined(HAMON_HAS_CXX20_COROUTINES)
#include <coroutine>
#endif
#if HAMON_HAS_INCLUDE(<compare>) && (HAMON_CXX_STANDARD >= 20)
#include <compare>
#endif
#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

namespace hamon_config_cxx20_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
namespace constexpr_union_test
{

union Value
{
	float f;
	std::uint32_t i;
};

constexpr Value GetFloat(float x)
{
	return Value{x}; // value.f がアクティブメンバ
}

constexpr Value GetUint(std::uint32_t x)
{
	Value value = GetFloat(0.0f); // value.f がアクティブメンバ
	value.i = x; // value.i がアクティブメンバに
	return value;
}

GTEST_TEST(ConfigTest, Cxx20ConstexprUnionTest)
{
	static_assert(GetUint(123).i == 123, "");
}

}	// namespace constexpr_union_test
#endif

#if defined(HAMON_HAS_CXX20_INITIALIZER_LIST_CTAD)
GTEST_TEST(ConfigTest, Cxx20InitializerListCTADTest)
{
	std::vector v1{1, 2};
	std::vector v2{v1};
	static_assert(std::is_same<decltype(v2), std::vector<int>>::value, "");
}
#endif

#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS) &&	\
	defined(HAMON_HAS_CXX20_RELAXING_STRUCTURED_BINDINGS)

namespace relaxing_structured_bindings_test
{

struct X : public std::shared_ptr<int>
{
	std::string fun_payload = "hoge";
};

template<int N>
std::string& get(X& x)
{
	if constexpr (N == 0)
	{
		return x.fun_payload;
	}
}

}	// namespace relaxing_structured_bindings_test
}	// namespace hamon_config_cxx20_test

namespace std
{

template<>
struct tuple_size<hamon_config_cxx20_test::relaxing_structured_bindings_test::X>
	: public std::integral_constant<int, 1> {};

template<>
struct tuple_element<0, hamon_config_cxx20_test::relaxing_structured_bindings_test::X>
{
	using type = std::string;
};

}	// namespace std

namespace hamon_config_cxx20_test
{

namespace relaxing_structured_bindings_test
{

GTEST_TEST(ConfigTest, Cxx20RelaxingStructuredBindingsTest)
{
	X x;
	auto& [y] = x;
	EXPECT_TRUE(y == "hoge");
}

}	// namespace relaxing_structured_bindings_test
#endif

namespace structured_bindings_to_accessible_members_test
{

#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS) &&	\
	defined(HAMON_HAS_CXX20_STRUCTURED_BINDINGS_TO_ACCESSIBLE_MEMBERS)

struct A
{
	friend void foo();
private:
	int i;
};

void foo()
{
	A a{};
	auto x = a.i; // OK
	auto [y] = a; // Ill-formed
	(void)x;
	(void)y;
}

#endif

}	// namespace structured_bindings_to_accessible_members_test

namespace synthesizing_three_way_comparison_test
{

#if defined(HAMON_HAS_CXX20_SYNTHESIZING_THREE_WAY_COMPARISON)

struct Legacy
{
	bool operator==(Legacy const&) const;
	bool operator<(Legacy const&) const;
};

struct Aggr
{
	int i;
	char c;
	Legacy q;

	std::strong_ordering operator<=>(Aggr const&) const = default;
};

struct X
{
	std::weak_ordering operator<=>(X const&) const;
};

#if !defined(HAMON_MSVC)	// TODO
struct Y
{
	X x;
	Legacy q;

	std::strong_ordering operator<=>(Y const&) const = default;
};
#endif

struct Q
{
	bool operator==(Q const&) const;
	bool operator<(Q const&) const;
};

struct Z
{
	X x;
	Q q;

	std::weak_ordering operator<=>(Z const&) const = default;
};

#endif

}	// namespace synthesizing_three_way_comparison_test

namespace nodiscard_ctor_test
{

#if defined(HAMON_HAS_CXX20_NODISCARD_CTOR)
struct X
{
	[[nodiscard]] X() {}
};
#endif

}	// namespace nodiscard_ctor_test

namespace implicit_move_test
{

struct Widget
{
	Widget(Widget&&) noexcept {}
};

struct RRefTaker
{
	RRefTaker(Widget&&) noexcept {}
};

Widget one(Widget w)
{
	return w;  // OK、C++11以降
}

RRefTaker two(Widget w)
{
	return w;  // OK、C++11以降（CWG1579解決後）
}

#if defined(HAMON_HAS_CXX20_IMPLICIT_MOVE)
RRefTaker three(Widget&& w)
{
	return w;  // OK、C++20以降（P0527による）
}
#endif

}	// namespace implicit_move_test

namespace defaulting_comparison_by_value_test
{

#if defined(HAMON_HAS_CXX20_DEFAULTING_COMPARISON_BY_VALUE)

struct A
{
	friend bool operator==(A, A) = default;
};

#endif

}	// namespace defaulting_comparison_by_value_test

namespace relaxing_range_for_test
{

#if defined(HAMON_HAS_CXX20_RELAXING_RANGE_FOR)

struct X
{
	int a[10];

	int* begin() { return a; }
};

inline int* begin(X& x) { return x.a; }
inline int* end(X& x) { return &x.a[9];}

GTEST_TEST(ConfigTest, Cxx20RelaxingRangeForTest)
{
	X x{};
	for (int i : x)
	{
		EXPECT_EQ(i, 0);
	}
}

#endif

}	// namespace relaxing_range_for_test

namespace constexpr_trivial_default_init_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_TRIVIAL_DEFAULT_INIT)

struct NontrivialType
{
	bool val = false;
};

struct TrivialType
{
	bool val;
};

template <typename T>
constexpr T f(const T& other)
{
	T t; // default initialization
	t = other;
	return t;
}

GTEST_TEST(ConfigTest, Cxx20ConstexprTrivialDefaultInitTest)
{
	auto nontrivial_rt = f(NontrivialType{});
	auto trivial_rt    = f(TrivialType{});
	constexpr auto nontrivial_ct = f(NontrivialType{});
	constexpr auto trivial_ct    = f(TrivialType{});
	(void)nontrivial_rt;
	(void)trivial_rt;
	(void)nontrivial_ct;
	(void)trivial_ct;
}

#endif

}	// namespace constexpr_trivial_default_init_test

namespace ctad_alias_template_test
{

#if defined(HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE)

template <class T, class U>
struct C {
	C(T, U){}   // #1
};
template <class T, class U>
C(T, U)->C<T, std::type_identity_t<U>>; // #2

template <class V>
using A = C<V*, V*>;
template <std::integral W>
using B = A<W>;

GTEST_TEST(ConfigTest, Cxx20CTADAliasTemplateTest)
{
	int i{};
//	double d{};
	A a1(&i, &i); // Deduces A<int>
//	A a2(i, i);   // Ill-formed: cannot deduce V * from i
//	A a3(&i, &d); // Ill-formed: #1: Cannot deduce (V*, V*) from (int *, double *) 
				  //             #2: Cannot deduce A<V> from C<int *, double *>
#if 0	// TODO:	MSVCでエラー
	B b1(&i, &i); // Deduces B<int>
#endif
//	B b2(&d, &d); // Ill-formed: cannot deduce B<W> from C<double *, double *>
}

#endif

}	// namespace ctad_alias_template_test

namespace ctad_aggregate_test
{

template <typename T>
struct Point
{
	T x;
	T y;
};

GTEST_TEST(ConfigTest, Cxx20CTADAggregateTest)
{
#if defined(HAMON_HAS_CXX20_CTAD_AGGREGATE)	\
	 && !defined(HAMON_MSVC)	// TODO: MSVC で Internal compiler error になる
	Point p1{3, 4};
#else
	Point<int> p1{3, 4};
#endif
	static_assert(std::is_same<decltype(p1), Point<int>>::value, "");
	EXPECT_TRUE(p1.x == 3);
	EXPECT_TRUE(p1.y == 4);
}

}	// namespace ctad_aggregate_test

namespace deprecate_volatile_test
{

#if !defined(HAMON_HAS_CXX20_DEPRECATE_VOLATILE)

// volatile-qualified parameter type is deprecated
void f(volatile int n);

// volatile-qualified return type is deprecated
//volatile int g(int n);

GTEST_TEST(ConfigTest, Cxx20DeprecateVolatileTest)
{
	volatile int i = 0;

	// increment of object of volatile-qualified type is deprecated
	++i;
	i++;

	// decrement of object of volatile-qualified type is deprecated
	--i;
	i--;

	// compound assignment to object of volatile-qualified type is deprecated
	i+=2;
	i-=2;
	i*=3;
	i/=3;

	volatile int j;

	// use of result of assignment to object of volatile-qualified type is deprecated
	i = j = 1;
}

#endif

}	// namespace deprecate_volatile_test

namespace pointer_to_bool_converting_test
{

struct X { bool b; };
void f(X) {}

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4130);	// '!=': logical operation on address of string constant

GTEST_TEST(ConfigTest, Cxx20PointerToBoolConvertingTest)
{
	int X::* p = nullptr;
#if defined(HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING)
	f(X { "whoops?" != nullptr });
	f(X { p != nullptr });
#else
	f(X { "whoops?" });
	f(X { p });
#endif
}

HAMON_WARNING_POP();

}	// namespace pointer_to_bool_converting_test

#if defined(HAMON_HAS_CXX20_CONSTEXPR_VIRTUAL_FUNCTION)
GTEST_TEST(ConfigTest, Cxx20ConstexprVirtualFunctionTest)
{
	struct X
	{
		virtual int f() const = 0;
	};

	struct Y : public X
	{
		constexpr int f() const override { return 1; }
	};

	static constexpr Y y{};
	constexpr X const& x = y;
	static_assert(x.f() == 1, "");
}
#endif

namespace constexpr_asm_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_ASM)

constexpr void func()
{
	if (std::is_constant_evaluated())
	{
	}
	else
	{
#if defined(HAMON_MSVC)
#  if defined(_M_IX86)
		__asm {};
#  endif
#else
		asm("");
#endif
	}
}

#endif

}	// namespace constexpr_asm_test

namespace abbreviated_function_template_test
{
#if defined(HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE) &&	\
	defined(__cpp_lib_concepts)

// function template parameter, unconstrained
void func1(auto x);

// function template parameter, constrained
void func2(std::integral auto x);

// function return type, unconstrained
auto func3();

// function return type, constrained
std::integral auto func4();

// generic lambda, unconstrained
auto f1 = [](auto x){return x;};

// generic lambda, constrained
auto f2 = [](std::integral auto x){return x;};

// variable, unconstrained
auto x1 = f1(0);

// variable, constrained
std::integral auto x2 = f2(0);

#endif
}	// namespace abbreviated_function_template_test

#if defined(HAMON_HAS_CXX20_EXCEPTION_SPEC_DEFAULTED_FUNCTION)
GTEST_TEST(ConfigTest, Cxx20ExceptionSpecDefaultedFunctionTest)
{
	struct T
	{
		T() {}
		T(T&&) noexcept(false) {}
	};

	struct U
	{
		T t;
		U() {}
		U(U&&) noexcept = default;
	};

	U u1;
	U u2 = static_cast<U&&>(u1);
	(void)u2;
}
#endif

#if defined(HAMON_HAS_CXX20_TWOS_COMPLEMENT_SIGNED_INTEGERS)
GTEST_TEST(ConfigTest, Cxx20TwosComplementSignedIntegersTest)
{
	{
		std::int8_t x = 11;
		std::int8_t y = -x;
		EXPECT_TRUE(y == (~x + 1)); // 負数は、ビット反転して+1した値
	}
}
#endif

#if defined(HAMON_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER)
GTEST_TEST(ConfigTest, Cxx20BitfieldDefaultMemberInitializerTest)
{
	struct X
	{
		int a : 6 = 8;
		int b : 2 {1};
	};

	X x;
	EXPECT_EQ(8, x.a);
	EXPECT_EQ(1, x.b);
}
#endif

GTEST_TEST(ConfigTest, Cxx20ConstQualifiedPointersToMembersTest)
{
	struct X { void foo() const& {} };

	X{}.foo();
#if defined(HAMON_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS)
	(X{}.*&X::foo)();
#endif
}

#if defined(HAMON_HAS_CXX20_CAPTURE_COPY_THIS)
GTEST_TEST(ConfigTest, Cxx20CaptureCopyThisTest)
{
	struct X
	{
		void f()
		{
			int value = 3;
			auto x = [=, this] { // [=]キャプチャと等価
				return value + g();
			};
			EXPECT_EQ(5, x());
		}

		int g() const
		{
			return 2;
		}
	};
	X().f();
}
#endif

#if defined(HAMON_HAS_CXX20_DESIGNATED_INITIALIZERS)
GTEST_TEST(ConfigTest, Cxx20DesignatedInitializersTest)
{
	struct A { int x; int y; int z; };

	A a{.x = 1, .y = 2, .z = 3};
	EXPECT_EQ(1, a.x);
	EXPECT_EQ(2, a.y);
	EXPECT_EQ(3, a.z);

	A b{.x = 1, .z = 2};
	EXPECT_EQ(1, b.x);
	EXPECT_EQ(0, b.y);
	EXPECT_EQ(2, b.z);

	A c{.y = 1};
	EXPECT_EQ(0, c.x);
	EXPECT_EQ(1, c.y);
	EXPECT_EQ(0, c.z);

	union U { int a; const char* b; };

	U d ={.a = 42};
	EXPECT_EQ(42, d.a);

	U e ={.b = "asdf"};
	EXPECT_STREQ("asdf", e.b);
}
#endif

#if defined(HAMON_HAS_CXX20_GENERIC_LAMBDAS)
GTEST_TEST(ConfigTest, Cxx20GenericLambdasTest)
{
	auto f =[]<class T>(const std::vector<T>& v)
	{
		if (v.empty())
		{
			return T();
		}
		else
		{
			return v.front();
		}
	};

	std::vector<int> v = {1, 2, 3};
	std::vector<std::string> w;

	EXPECT_EQ(1,  f(v)); // Tの型はint
	EXPECT_EQ("", f(w)); // Tの型はstd::string
}
#endif

#if defined(HAMON_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER)
GTEST_TEST(ConfigTest, Cxx20RangeBasedForInitializerTest)
{
	std::vector<int> v {10, 20, 30};
	for (int i = 0; auto& x : v)
	{
		x += i;
		i++;
	}

	EXPECT_EQ(10, v[0]);
	EXPECT_EQ(21, v[1]);
	EXPECT_EQ(32, v[2]);
}
#endif

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && HAMON_HAS_INCLUDE(<compare>)
GTEST_TEST(ConfigTest, Cxx20ThreeWayComparisonTest)
{
	struct X
	{
		int x;
		int y;
		auto operator<=>(const X&) const = default;
	};

	X x1 = {10, 20};
	X x2 = {10, 20};
	X x3 = {11, 20};
	X x4 = {10, 19};

	EXPECT_TRUE ((x1 <=> x2) == 0);
	EXPECT_FALSE((x1 <=> x2) >  0);
	EXPECT_FALSE((x1 <=> x2) <  0);
	EXPECT_FALSE((x1 <=> x3) == 0);
	EXPECT_FALSE((x1 <=> x3) >  0);
	EXPECT_TRUE ((x1 <=> x3) <  0);
	EXPECT_FALSE((x1 <=> x4) == 0);
	EXPECT_TRUE ((x1 <=> x4) >  0);
	EXPECT_FALSE((x1 <=> x4) <  0);

	EXPECT_TRUE (x1 == x2);
	EXPECT_FALSE(x1 != x2);
	EXPECT_FALSE(x1 <  x2);
	EXPECT_FALSE(x1 >  x2);
	EXPECT_TRUE (x1 <= x2);
	EXPECT_TRUE (x1 >= x2);

	EXPECT_FALSE(x1 == x3);
	EXPECT_TRUE (x1 != x3);
	EXPECT_TRUE (x1 <  x3);
	EXPECT_FALSE(x1 >  x3);
	EXPECT_TRUE (x1 <= x3);
	EXPECT_FALSE(x1 >= x3);

	EXPECT_FALSE(x1 == x4);
	EXPECT_TRUE (x1 != x4);
	EXPECT_FALSE(x1 <  x4);
	EXPECT_TRUE (x1 >  x4);
	EXPECT_FALSE(x1 <= x4);
	EXPECT_TRUE (x1 >= x4);
}
#endif

#if defined(HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS)
GTEST_TEST(ConfigTest, Cxx20DefaultConstructibleAndAssignableStatelessLambdasTest)
{
	auto greater = [](auto x, auto y) { return x > y; };
	decltype(greater) f;
	f = greater;
}
#endif

namespace conditional_explicit_test
{

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
template <bool B>
struct S
{
	explicit(B) S() {}
	explicit(B) operator bool() const { return true; }
};

GTEST_TEST(ConfigTest, Cxx20ConditionalExplicitTest)
{
	static_assert( std::is_default_constructible<S<true>>::value, "");
	static_assert( std::is_default_constructible<S<false>>::value, "");

//	static_assert(!hamon::is_implicitly_default_constructible<S<true>>::value, "");
//	static_assert( hamon::is_implicitly_default_constructible<S<false>>::value, "");

	S<true> x1;
	S<false> x2;
//	bool b1 = x1;
	bool b2 = x2;
	bool b3 = static_cast<bool>(x1);
	bool b4 = static_cast<bool>(x2);

	(void)b2;
	(void)b3;
	(void)b4;
}
#endif

}	// namespace conditional_explicit_test

namespace char8_t_test
{

#if defined(HAMON_HAS_CXX20_CHAR8_T)
template <typename> struct S { static const bool value = false; };
template <> struct S<char8_t> { static const bool value = true; };

GTEST_TEST(ConfigTest, Cxx20Char8TTest)
{
	{
		const char8_t* s = u8"hoge";
		const char8_t c = u8'c';
		(void)s;
		(void)c;
	}
	{
		const auto* s = u8"hoge";
		const auto c = u8'c';
		static_assert(std::is_same<const char8_t*, decltype(s)>::value, "");
		static_assert(std::is_same<const char8_t, decltype(c)>::value, "");
	}

	static_assert(sizeof(char8_t) == sizeof(unsigned char), "");
	static_assert(!std::is_same<char8_t, char>::value, "");
	static_assert(!std::is_same<char8_t, unsigned char>::value, "");

	static_assert(S<char8_t>::value, "");
	static_assert(!S<char>::value, "");
	static_assert(!S<unsigned char>::value, "");
}
#endif

}	// namespace char8_t_test

namespace constexpr_try_catch_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_TRY_CATCH)
constexpr int f(int x)
{
	try
	{
		return x + 1;
	}
	catch (...)
	{
		return 0;
	}
}

GTEST_TEST(ConfigTest, Cxx20ConstexprTryCatchTest)
{
	static_assert(f(1) == 2, "");
	static_assert(f(2) == 3, "");
}
#endif

}	// namespace constexpr_try_catch_test

namespace concepts_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept ConvertibleTo =
	std::is_convertible<From, To>::value &&
	requires(std::add_rvalue_reference_t<From> (&f)())
	{
		static_cast<To>(f());
	};

template <typename T>
concept Integral = std::is_integral<T>::value;

template <typename T>
concept FloatingPoint = std::is_floating_point<T>::value;

template <typename T, typename U>
concept EqualityComparable =
	requires (T a, U b)
	{
		{a == b} -> ConvertibleTo<bool>;
	};

template <typename T>
concept SequenceContainer =
	requires (T c)
	{
		typename T::size_type; // 型Tがメンバ型としてsize_typeを持っていること
		{c.size()} -> ConvertibleTo<typename T::size_type>;     // 型Tのオブジェクトに対して特定のメンバ関数が呼び出せることを要求
		{std::size(c)} -> ConvertibleTo<typename T::size_type>; // 非メンバ関数の呼び出しも要求できる

		typename T::value_type;
		c.push_back(std::declval<typename T::value_type>());
	};

static_assert( Integral<int>, "");
static_assert(!Integral<float>, "");
static_assert(!Integral<std::string>, "");
static_assert(!FloatingPoint<int>, "");
static_assert( FloatingPoint<float>, "");
static_assert(!FloatingPoint<std::string>, "");
static_assert( EqualityComparable<int, int>, "");
static_assert( EqualityComparable<int, float>, "");
static_assert(!EqualityComparable<int, std::string>, "");
static_assert( SequenceContainer<std::vector<int>>, "");
static_assert( SequenceContainer<std::string>, "");
static_assert(!SequenceContainer<int>, "");

template <Integral T>
constexpr int func(T)
{
  return 1;
}

template <FloatingPoint T>
constexpr int func(T)
{
  return 2;
}

static_assert(func(0) == 1, "");
static_assert(func(0.0f) == 2, "");

template <typename T>
requires Integral<T> || FloatingPoint<T>
constexpr bool func2(T)
{
	return true;
}

template <typename T>
requires (!Integral<T>) && (!FloatingPoint<T>)
constexpr bool func2(T)
{
	return false;
}

static_assert( func2(0), "");
static_assert( func2(0.0f), "");
static_assert(!func2("0"), "");

#endif

}	// namespace concepts_test

namespace va_opt_test
{

#if defined(HAMON_HAS_CXX20_VA_OPT)
template <typename... Args>
constexpr int func(Args... args)
{
	return sizeof...(args);
}

GTEST_TEST(ConfigTest, Cxx20VaOptTest)
{
#define F(X, ...) func(X __VA_OPT__(,) __VA_ARGS__)
	static_assert(F(3) == 1, "");
	static_assert(F(3, "Hello") == 2, "");
	static_assert(F(3, "Hello", 'A') == 3, "");
#undef F

#define F(name, ...) std::vector<int> name __VA_OPT__(= { __VA_ARGS__ })
	F(v1);
	F(v2, 1, 2, 3);

	EXPECT_TRUE(v1.size() == 0);
	EXPECT_TRUE(v2.size() == 3);
#undef F
}
#endif

}	// namespace va_opt_test

namespace nodiscard_with_message_test
{

#if defined(HAMON_HAS_CXX20_NODISCARD_WITH_MESSAGE)

struct [[nodiscard("with reason 1")]]  error_info {};

error_info f() { return error_info{}; }

[[nodiscard("with reason 2")]]  int g() { return 0; }

GTEST_TEST(ConfigTest, Cxx20NodiscardWithMessageTest)
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4858)	// 戻り値 "..." を破棄しています 
HAMON_WARNING_DISABLE_CLANG("-Wunused-result")
HAMON_WARNING_DISABLE_GCC("-Wunused-result")

	f();
	g();

HAMON_WARNING_POP()
}
#endif

}	// namespace nodiscard_with_message_test

namespace likely_unlikely_test
{

#if defined(HAMON_HAS_CXX20_LIKELY) && defined(HAMON_HAS_CXX20_UNLIKELY)
GTEST_TEST(ConfigTest, Cxx20LikelyUnlikelyTest)
{
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000))
	bool f1 = true;
	bool f2 = false;

	if (f1) [[likely]]
	{
		EXPECT_TRUE(f1);
	}
	if (f2) [[unlikely]]
	{
		EXPECT_TRUE(f1);
	}
#endif

	int n = 10;
	switch (n)
	{
	case 0:
		break;
	[[unlikely]] case 1:
		break;
	[[likely]] default:
		break;
	}
}
#endif

}	// namespace likely_unlikely_test

namespace nontype_template_parameter_class_test
{

#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)

struct A
{
	friend bool operator==(const A&, const A&)
	{
		return true;
	}
};

template <A a> bool f()
{
	const A& ra = a, & rb = a;
	return &ra == &rb;
}

#endif

//GTEST_TEST(ConfigTest, Cxx20NontypeTemplateParameterClassTest)
//{
//	constexpr A a;
//	EXPECT_TRUE(f<a>());
//}

}	// namespace nontype_template_parameter_class_test

#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT)
namespace nontype_template_parameter_float_test
{

template <float f>
constexpr float func()
{
	return f * 2;
}

static_assert(func<1.0f>() == 2.0f, "");
static_assert(func<1.5f>() == 3.0f, "");

}	// namespace nontype_template_parameter_float_test
#endif

#if defined(HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS)
namespace no_unique_address_test
{

struct Empty{};
struct NotEmpty{int i;};

struct A
{
	Empty e;
	NotEmpty ne;
	char c;
};
struct B
{
	[[no_unique_address]] Empty e;
	[[no_unique_address]] NotEmpty ne;
	char c;
};

static_assert(sizeof(A) >= sizeof(B), "");

}	// namespace no_unique_address_test
#endif

#if defined(HAMON_HAS_CXX20_INIT_CAPTURES)
namespace init_captures_test
{

template <typename... Args>
auto f(Args... args)
{
	[...args = std::move(args)]	// 初期化キャプチャでのパック展開
	{
		g(args...); // ラムダ式内で、パックを使う例
	};
}

}	// namespace init_captures_test
#endif

#if defined(HAMON_HAS_CXX20_CAPTURE_COPY_THIS)
GTEST_TEST(ConfigTest, Cxx20DeprecateImplicitCaptureCopyThisTest)
{
	struct X
	{
		void f()
		{
			int value = 3;
#if defined(HAMON_HAS_CXX20_DEPRECATE_IMPLICIT_CAPTURE_COPY_THIS)
			auto x = [=, this] {
				return value + g();
			};
#else
			auto x = [=] {
				return value + g();
			};
#endif
			EXPECT_EQ(5, x());
		}

		int g() const
		{
			return 2;
		}
	};
	X().f();
}
#endif

#if defined(HAMON_HAS_CXX20_STRUCTURED_BINDING_EXTENSIONS)
namespace structured_binding_extensions_test
{

//static指定構造化束縛宣言
static auto [a_static, b_static] = std::make_tuple(1.0, 2.0);

//thread_local指定構造化束縛宣言
thread_local auto [a_tls, b_tls] = std::make_tuple(1.0, 2.0);

GTEST_TEST(ConfigTest, Cxx20StructuredBindingExtensionsTest)
{
	EXPECT_TRUE(a_static == 1.0);
	EXPECT_TRUE(b_static == 2.0);
	
	auto tuple = std::make_tuple(1.0, 2.0, 3.0);
	auto& [a, b, c] = tuple;

	// 構造化束縛宣言に指定した変数名をそのままラムダ式でキャプチャすることもできる

	//コピーキャプチャ
	auto f_copy = [a, b, c]() {return a + b + c; };

	//参照キャプチャ
	auto f_ref  = [&a, &b, &c]() {return a + b + c; };

	EXPECT_TRUE(f_copy() == 6);
	EXPECT_TRUE(f_ref()  == 6);

	a = 4.0;

	EXPECT_TRUE(f_copy() == 6);
	EXPECT_TRUE(f_ref()  == 9);
}

}	// namespace structured_binding_extensions_test
#endif

#if defined(HAMON_HAS_CXX20_USING_ENUM)
namespace using_enum_test
{

enum class Enum1
{
	Value1
};

struct Enum2
{
	enum Enum
	{
		Value2
	};
};

enum class Enum3
{
	Value3,
	Value4
};

struct Type
{
	using enum Enum3;
};

constexpr int Value1 = 1;

GTEST_TEST(ConfigTest, Cxx20UsingEnumTest)
{
	using enum Enum1;
	using enum Enum2::Enum;
	using Enum3::Value3;
	EXPECT_TRUE((int)Value1        == 0);
	EXPECT_TRUE((int)using_enum_test::Value1 == 1);
	EXPECT_TRUE((int)Value2        == 0);
	EXPECT_TRUE((int)Value3        == 0);
	EXPECT_TRUE((int)Enum3::Value4 == 1);
	EXPECT_TRUE((int)Type::Value4  == 1);
	EXPECT_TRUE((int)Type().Value4 == 1);
}

}	// namespace using_enum_test
#endif

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
namespace is_constant_evaluated_test
{

constexpr int f()
{
	if (std::is_constant_evaluated())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

GTEST_TEST(ConfigTest, Cxx20IsConstantEvaluatedTest)
{
	static_assert(f() == 0, "");
	EXPECT_TRUE(f() == 1);
}

}	// namespace is_constant_evaluated_test
#endif


GTEST_TEST(ConfigTest, Cxx20DeprecateCommaInSubscriptingExpressionsTest)
{
	int a[] = {1,2,3,4,5};
	int index = 0;

#if !defined(HAMON_HAS_CXX20_DEPRECATE_COMMA_IN_SUBSCRIPTING_EXPRESSIONS)

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4709);	// comma operator within array index expression
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-comma-subscript");

	auto x = a[++index, 0];		// C++17 まで OK, C++20 から deprecated

HAMON_WARNING_POP();

#else

	auto x = a[(++index, 0)];	// C++20 でもOK

#endif

	EXPECT_TRUE(x == 1);
}

// TODO
#if 0//defined(HAMON_HAS_CXX20_ACCESS_CHECKING_ON_SPECIALIZATIONS)
namespace access_checking_on_specializations_test
{

template <typename T>
struct trait;

class class_
{
	template <typename U>
	struct impl;
};

// Not allowed in standard C++ (impl is private)
// Not allowed in clang, icc
// Allowed in gcc, msvc
template <typename U>
struct trait<class_::impl<U>>;

}	// namespace access_checking_on_specializations_test
#endif

GTEST_TEST(ConfigTest, Cxx20ArraySizeDeductionNewTest)
{
#if defined(HAMON_HAS_CXX20_ARRAY_SIZE_DEDUCTION_NEW)
	int* p = new int[]{1,2,3};
#else
	int* p = new int[3]{1,2,3};
#endif

	EXPECT_TRUE(p[0] == 1);
	EXPECT_TRUE(p[1] == 2);
	EXPECT_TRUE(p[2] == 3);

	delete[] p;
}

#if defined(HAMON_HAS_CXX20_DESTROYING_DELETE)
namespace destroying_delete_test
{

static int s_dtor_count   = 0;
static int s_delete_count = 0;

struct Object
{
	~Object()
	{
		++s_dtor_count;
	}

	static void operator delete(Object* p, std::destroying_delete_t)
	{
		++s_delete_count;
		p->~Object();
		::operator delete(p);
	}
};

GTEST_TEST(ConfigTest, Cxx20DestroyingDeleteTest)
{
	EXPECT_TRUE(s_dtor_count   == 0);
	EXPECT_TRUE(s_delete_count == 0);

	Object* p = new Object;
	delete p;

	EXPECT_TRUE(s_dtor_count   == 1);
	EXPECT_TRUE(s_delete_count == 1);
}

}	// namespace destroying_delete_test
#endif

#if defined(HAMON_HAS_CXX20_NESTED_INLINE_NAMESPACES)
namespace nested_inline_namespaces_test
{

namespace ns1::inline ns2::ns3 {
	class X;
}

}	// namespace nested_inline_namespaces_test
#endif

#if defined(HAMON_HAS_CXX20_CONVERSIONS_TO_UNBOUNDED_ARRAY)
GTEST_TEST(ConfigTest, Cxx20ConversionsToUnboundedArrayTest)
{
	int a[2] {1,2};
	int (&r)[] = a;
	(void)r;
}
#endif

#if defined(HAMON_HAS_CXX20_MODULES)
// TODO
//export module mylib;
#endif

#if defined(HAMON_HAS_CXX20_COROUTINES)
namespace coroutines_test
{

struct generator
{
	struct promise_type;
	using handle = std::coroutine_handle<promise_type>;
	struct promise_type
	{
		int current_value;
		static auto get_return_object_on_allocation_failure() { return generator{nullptr}; }
		auto get_return_object() { return generator{handle::from_promise(*this)}; }
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { std::terminate(); }
		void return_void() {}
		auto yield_value(int value)
		{
			current_value = value;
			return std::suspend_always{};
		}
	};
	bool move_next() { return coro ? (coro.resume(), !coro.done()) : false; }
	int current_value() { return coro.promise().current_value; }
	generator(generator const&) = delete;
	generator(generator&& rhs) : coro(rhs.coro) { rhs.coro = nullptr; }
	~generator() { if (coro) coro.destroy(); }
private:
	generator(handle h) : coro(h) {}
	handle coro;
};

generator f() { co_yield 1; co_yield 2; }

GTEST_TEST(ConfigTest, Cxx20CoroutinesTest)
{
	auto g = f();
//	EXPECT_EQ(0, g.current_value());
	g.move_next();
	EXPECT_EQ(1, g.current_value());
	g.move_next();
	EXPECT_EQ(2, g.current_value());
	g.move_next();
	EXPECT_EQ(2, g.current_value());
}

}	// namespace coroutines_test
#endif

#if defined(HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS)
namespace lambdas_in_unevaluated_contexts_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
// conceptの定義内
template <typename T>
concept C = requires { []{}; };

// requires節の中
template <typename T>
void f() requires(requires{ []{}; });
#endif

// decltypeのオペランド
using lambda_t = decltype([]{});

// noexcept式のオペランド
void g() noexcept(noexcept([]{}));

// sizeofのオペランド
auto s = sizeof([]{});

// typeidのオペランド
auto& t = typeid([]{});

}	// namespace lambdas_in_unevaluated_contexts_test
#endif

#if defined(HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT)
namespace aggregate_paren_init_test
{

struct A
{
	int x, y;
};

GTEST_TEST(ConfigTest, Cxx20AggregateParenInitTest)
{
	A a(1, 2);
	EXPECT_EQ(1, a.x);
	EXPECT_EQ(2, a.y);

	int n[](1, 2, 3, 4, 5);
	EXPECT_EQ(1, n[0]);
	EXPECT_EQ(5, n[4]);

	int m[3](42);
	EXPECT_EQ(42, m[0]);
	EXPECT_EQ( 0, m[1]);
	EXPECT_EQ( 0, m[2]);
}

}	// namespace aggregate_paren_init_test
#endif

#if defined(HAMON_HAS_CXX20_CONDITIONALLY_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS)
namespace conditionally_trivial_special_member_functions_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T>
concept trivially_copy_constructible = std::is_trivially_copy_constructible<T>::value;

template <typename T>
struct A
{
    // #1
    A(A const&)
		requires
			trivially_copy_constructible<T> &&
			std::copy_constructible<T> = default;
        
    // #2
    A(A const&)
		requires std::copy_constructible<T>
    {}
};

static_assert(std::is_trivially_copyable<A<int>>::value == true, "");
static_assert(std::is_trivially_copyable<A<std::vector<int>>>::value == false, "");
#endif

}	// namespace conditionally_trivial_special_member_functions_test
#endif

#if defined(HAMON_HAS_CXX20_ADL_AND_FUNCTION_TEMPLATES)
namespace adl_and_function_templates_test
{

int f() { return 0; }

namespace ns
{

struct A {};

template <class T>
int f(T) { return 1; }

}	// namespace ns

GTEST_TEST(ConfigTest, Cxx20AdlAndFunctionTemplatesTest)
{
	EXPECT_EQ(1, f<ns::A>(ns::A{}));
}

}	// namespace adl_and_function_templates_test
#endif

#if defined(HAMON_HAS_CXX20_CONST_MISMATCH_WITH_DEFAULTED_COPY_CONSTRUCTOR)
namespace const_mismatch_with_defaulted_copy_constructor_test
{

struct MyType
{
	MyType(){}
	MyType(MyType&){}  // no 'const'
};

template <typename T>
struct Wrapper
{
	Wrapper() = default;
	Wrapper(const Wrapper&) = default;
	T t;
};

Wrapper<MyType> var;	// C++17: fails to instantiate

}	// namespace const_mismatch_with_defaulted_copy_constructor_test
#endif

namespace prohibit_aggregates_with_user_declared_constructors_test
{
#if defined(__cpp_lib_is_aggregate) && (__cpp_lib_is_aggregate >= 201703)
struct A
{
	A() = delete;
};

struct B
{
private:
	B() = default;
};

struct C
{
	int i = 0;
	C() = default;
};

#if defined(HAMON_HAS_CXX20_PROHIBIT_AGGREGATES_WITH_USER_DECLARED_CONSTRUCTORS)
static_assert(!std::is_aggregate<A>::value, "");
static_assert(!std::is_aggregate<B>::value, "");
static_assert(!std::is_aggregate<C>::value, "");
#else
static_assert( std::is_aggregate<A>::value, "");
static_assert( std::is_aggregate<B>::value, "");
static_assert( std::is_aggregate<C>::value, "");
#endif
#endif
}	// namespace prohibit_aggregates_with_user_declared_constructors_test

#if defined(HAMON_HAS_CXX20_STRONGER_UNICODE_REQUIREMENTS)
GTEST_TEST(ConfigTest, Cxx20StrongerUnicodeRequirementsTest)
{
	{
		char16_t const* s = u"A";
		EXPECT_EQ(0x0041, s[0]);
		EXPECT_EQ(0x0000, s[1]);
	}
	{
		char16_t const* s = u"あ";
		EXPECT_EQ(0x3042, s[0]);
		EXPECT_EQ(0x0000, s[1]);
	}
	{
		char16_t const* s = u"𠮷";
		EXPECT_EQ(0xD842, s[0]);
		EXPECT_EQ(0xDFB7, s[1]);
		EXPECT_EQ(0x0000, s[2]);
	}
	{
		char32_t const* s = U"A";
		EXPECT_EQ(0x00000041u, s[0]);
		EXPECT_EQ(0x00000000u, s[1]);
	}
	{
		char32_t const* s = U"あ";
		EXPECT_EQ(0x00003042u, s[0]);
		EXPECT_EQ(0x00000000u, s[1]);
	}
	{
		char32_t const* s = U"𠮷";
		EXPECT_EQ(0x00020BB7u, s[0]);
		EXPECT_EQ(0x00000000u, s[1]);
	}
}
#endif

#if defined(HAMON_HAS_CXX20_CONSTINIT)
namespace constinit_test
{
constinit const int N = 1;
static_assert(N == 1, "");
}	// namespace constinit_test
#endif

#if defined(HAMON_HAS_CXX20_CONSTEXPR_IN_DECLTYPE)
namespace constexpr_in_decltype_test
{

// case 1:
namespace ns_case_1
{

struct duration {
	constexpr duration() {}
	constexpr operator int() const { return 0; }
};

}	// namespace ns_case_1

// case 2:
namespace ns_case_2
{

template <typename T>
int f(T x)
{
	return x.get();
}

template <typename T>
constexpr int g(T x)
{
	return x.get();
}

}	// namespace ns_case_2

template <typename T>
constexpr int f() { return T::value; }

template <bool B, typename T>
void g(decltype(B ? f<T>() : 0)){}

template <bool B, typename T>
void g(...){}

template <bool B, typename T>
void h(decltype(int{B ? f<T>() : 0})){}

template <bool B, typename T>
void h(...){}

GTEST_TEST(ConfigTest, Cxx20ConstexprInDecltypeTest)
{
	// case 1:
	{
		using namespace ns_case_1;
		int n = sizeof(short{duration(duration())});
		(void)n;
	}
	// case 2:
	{
		using namespace ns_case_2;
		decltype(f(0)) a;
		decltype(g(0)) b;
		(void)a;
		(void)b;
	}

	g<false, int>(0);  //OK
//	h<false, int>(0);  //compile error!
}

}	// namespace constexpr_in_decltype_test
#endif

#if defined(HAMON_HAS_CXX20_CONSTEVAL)
namespace consteval_test
{
consteval int sqr(int n) { return n*n; }
constexpr int r = sqr(100);
static_assert(r == 10000, "100 * 100 == 10000");
}	// namespace consteval_test
#endif

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST) && !defined(HAMON_NO_RTTI)
namespace constexpr_dynamic_cast_test
{

struct base
{
	virtual int f() const = 0;
};

struct derived1 : public base
{
	constexpr int f() const override
	{
		return 10;
	}
};

struct derived2 : public base
{
	constexpr int f() const override
	{
		return 20;
	}
};

struct base2
{
	virtual int g() const = 0;
};

struct derived3 : public base, public base2
{
	constexpr int f() const override
	{
		return 30;
	}

	constexpr int g() const override
	{
		return 30;
	}
};

constexpr auto& get_typeinfo(const base* p)
{
	// コンパイル時に動的型のtype_infoを取得する
	return typeid(*p);
}

constexpr const base2* side_cast(const base* p)
{
	// コンパイル時サイドキャスト
	return dynamic_cast<const base2*>(p);
}

GTEST_TEST(ConfigTest, Cxx20ConstexprDynamicCastTest)
{
	constexpr derived1 d1{};
	constexpr derived2 d2{};

	// typeidの例
	constexpr auto& tid1 = get_typeinfo(&d1);
	constexpr auto& tid2 = get_typeinfo(&d2);

	EXPECT_FALSE(tid1 == tid2);

	// dynamic_castの例
	constexpr static derived3 d3{};
	constexpr const base2* b2 = side_cast(&d3);

	EXPECT_TRUE(b2->g() == 30);
}

}	// namespace constexpr_dynamic_cast_test
#endif

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
namespace constexpr_dynamic_alloc_test
{

constexpr int f()
{
	// 確保と構築
	int* p = new int;

	*p = 20;
	int n = *p;

	// 破棄と解放
	delete p;

	return n;
}

static_assert(f() == 20, "");

}	// namespace constexpr_dynamic_alloc_test
#endif

#if defined(HAMON_HAS_CXX20_OPTIONAL_TYPENAME)
namespace optional_typename_test
{

// P0634R3より引用
template <typename T> T::R f();     // OK, グローバルスコープにおける関数の戻り値
//template <typename T> void f(T::R); // Ill-formed, void型の変数テンプレートの宣言

template <typename T> struct PtrTraits;

template <typename T>
struct S
{
	// クラススコープ
	using Ptr = PtrTraits<T>::Ptr;		// OK, エイリアス宣言
	T::R f(T::P p)						// OK, メンバ宣言、およびメンバ宣言における仮引数宣言
	{
		return static_cast<T::R>(p);	// OK, static_castの型名
	}
	auto g()->S<T*>::Ptr;				// OK, 後置戻り値型
};

template <typename T>
void f()
{
	// ブロックスコープ
	void (*pf)(T::X); // T::Xで初期化されるvoid*型の変数pf
//	void g(T::X);     // エラー: void型の変数宣言
}

}	// namespace optional_typename_test
#endif

}	// namespace hamon_config_cxx20_test
