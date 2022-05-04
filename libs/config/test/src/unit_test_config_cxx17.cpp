/**
 *	@file	unit_test_config_cxx17.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <new>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace hamon_config_cxx17_test
{

GTEST_TEST(ConfigTest, Cxx17HexFloatTest)
{
#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
	float f = 0xABCp-3f;
	double d = 0x1.0p-2;
	long double ld = 0x2.5P3l;

	EXPECT_EQ(343.5f, f);
	EXPECT_EQ(0.25, d);
	EXPECT_EQ(18.5, ld);
#endif
}

GTEST_TEST(ConfigTest, Cxx17U8CharacterLiteralsTest)
{
#if defined(HAMON_HAS_CXX17_U8_CHARACTER_LITERALS)
	char c = u8'A';
	EXPECT_EQ('A', c);
#endif
}

namespace inline_variables_test
{

#if defined(HAMON_HAS_CXX17_INLINE_VARIABLES)

inline int inline_var = 30;

struct A { static inline int inline_var = 100; };

#endif	// defined(HAMON_HAS_CXX17_INLINE_VARIABLES)

}	// namespace inline_variables_test

GTEST_TEST(ConfigTest, Cxx17AlignedNewTest)
{
#if defined(HAMON_HAS_CXX17_ALIGNED_NEW)
	std::align_val_t align = static_cast<std::align_val_t>(32);
	(void)align;
	//{
	//	auto* p = new(align) int;
	//	delete p;
	//}
	//{
	//	auto* p = new(align) int[10];
	//	delete[] p;
	//}
#endif	// defined(HAMON_HAS_CXX17_ALIGNED_NEW)
}

namespace guaranteed_copy_elision_test
{

#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)

struct Foo
{
	Foo() = default;
	Foo(const Foo&) = delete;
	Foo(Foo&&) = delete;
};

Foo foo()
{
	return Foo();
}

void test()
{
	Foo y = foo();
	(void)y;
}

#endif	// defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)

}	// namespace guaranteed_copy_elision_test

namespace noexcept_function_type_test
{

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using f = void(*)() noexcept;

#endif	// defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

}	// namespace noexcept_function_type_test


GTEST_TEST(ConfigTest, Cxx17ExpressionEvaluationOrderTest)
{
#if defined(HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER)
	std::map<int, std::size_t> m;
	m[0] = m.size();
	EXPECT_EQ(0u, m[0]);
#endif	// defined(HAMON_HAS_CXX17_EXPRESSION_EVALUATION_ORDER)
}

namespace fold_expressions_test
{

#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS)

template <typename... Args> auto sum(Args... args)
{
	return (args + ...);
}

template <typename... Args> auto sum0(Args... args)
{
	return (args + ... + 0);
}

template <typename... Args> bool all(Args... args)
{
	return (... && args);
}

template <typename... Args> void print_all(std::ostream& os, Args... args)
{
	(os << ... << args);
}

#endif

GTEST_TEST(ConfigTest, Cxx17FoldExpressionsTest)
{
#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS)
	EXPECT_EQ(15, sum(1, 2, 3, 4, 5));
	EXPECT_EQ(5, sum(5));
	EXPECT_EQ(10, sum0(1, 2, 3, 4));
	EXPECT_EQ(0, sum0());
	EXPECT_EQ(true, all(true));
	EXPECT_EQ(false, all(false, true, true));
	EXPECT_EQ(true, all());

	std::stringstream ss;
	print_all(ss, 1, 2, 3, 'A');
	EXPECT_EQ("123A", ss.str());
#endif
}

}	// namespace fold_expressions_test

namespace capture_star_this_test
{

#if defined(HAMON_HAS_CXX17_CAPTURE_STAR_THIS)

struct S
{
	S(int value) : m_value(value) {}

	void f(std::function<int(void)>& func)
	{
		auto proc = [*this]() mutable
		{
			increament();

			return m_value;
		};

		func = proc;
	}

	void increament()
	{
		m_value++;
	}

	int m_value;
};

#endif

GTEST_TEST(ConfigTest, Cxx17CaptureStarThisTest)
{
#if defined(HAMON_HAS_CXX17_CAPTURE_STAR_THIS)
	std::function<int(void)> func;

	{
		S s(42);
		s.f(func);
		s.m_value = 0;
	}

	EXPECT_EQ(43, func());
#endif
}

}	// namespace capture_star_this_test

GTEST_TEST(ConfigTest, Cxx17ConstexprLambdaTest)
{
#if defined(HAMON_HAS_CXX17_CONSTEXPR_LAMBDA)
	auto f = []{ return 42; };
	constexpr int value = f();
	static_assert(value == 42, "");
#endif
}

GTEST_TEST(ConfigTest, Cxx17IfConstexprTest)
{
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (sizeof(int) >= sizeof(char))
	{
		//GTEST_SUCCEED();
	}
	else
	{
		GTEST_FAIL();
	}
#endif
}

GTEST_TEST(ConfigTest, Cxx17SelectionWithInitTest)
{
#if defined(HAMON_HAS_CXX17_SELECTION_WITH_INIT)
	if (int x = 1; x != 0)
	{
		//GTEST_SUCCEED();
	}
	else
	{
		GTEST_FAIL();
	}

	switch (int x = 1; x)
	{
	case 1:
		//GTEST_SUCCEED();
		break;
	default:
		GTEST_FAIL();
		break;
	}
#endif
}

namespace range_based_for_test
{

template <char delimiter>
struct EndOfDelimitedString
{
	bool operator()(std::string::iterator it)
	{
		return *it != delimiter && *it != '\0';
	}
};

template <char delimiter>
struct DelimitedString
{
	std::string str;

	DelimitedString(std::string const& s) : str(s) {}
	std::string::iterator begin() { return str.begin(); }
	EndOfDelimitedString<delimiter> end() const { return EndOfDelimitedString<delimiter>(); }
};

template <char delimiter>
bool operator!=(std::string::iterator it, EndOfDelimitedString<delimiter> e)
{
	return e(it);
}

GTEST_TEST(ConfigTest, Cxx17RangeBasedForTest)
{
#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	std::string str{"ABCDE, abcde|12345"};
	{
		std::stringstream ss;
		for (auto c : str)
		{
			ss << c;
		}
		EXPECT_EQ("ABCDE, abcde|12345", ss.str());
	}
	{
		std::stringstream ss;
		for (auto c : DelimitedString<','>{str})
		{
			ss << c;
		}
		EXPECT_EQ("ABCDE", ss.str());
	}
	{
		std::stringstream ss;
		for (auto c : DelimitedString<'|'>{str})
		{
			ss << c;
		}
		EXPECT_EQ("ABCDE, abcde", ss.str());
	}
#endif
}

}	// namespace range_based_for_test

namespace static_assert_test
{

#if defined(HAMON_HAS_CXX17_STATIC_ASSERT)

static_assert(true);
//static_assert(false);

#endif	// defined(HAMON_HAS_CXX17_STATIC_ASSERT)

}	// namespace static_assert_test

HAMON_WARNING_PUSH()
#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 30600) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wfuture-compat")
#endif

GTEST_TEST(ConfigTest, Cxx17AutoDeductionBracedInitListTest)
{
	auto assign_brace_single = {0};      // std::initializer_list<int>
	auto assign_brace_multi  = {0, 1};   // std::initializer_list<int>
	auto brace_init_single{0};           // C++14 までは std::initializer_list<int>, C++17 からは int
	//auto brace_init_multi{0, 1};       // C++14 までは std::initializer_list<int>, C++17 からは 不適格
	(void)brace_init_single;

	static_assert(std::is_same<decltype(assign_brace_single), std::initializer_list<int>>::value, "");
	static_assert(std::is_same<decltype(assign_brace_multi), std::initializer_list<int>>::value, "");
#if defined(HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST)
	static_assert(std::is_same<decltype(brace_init_single), int>::value, "");
#else
	static_assert(std::is_same<decltype(brace_init_single), std::initializer_list<int>>::value, "");
#endif	// defined(HAMON_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST)
}

HAMON_WARNING_POP()

GTEST_TEST(ConfigTest, Cxx17DeductionGuidesTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	std::vector v = {1, 2, 3};
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(3, v[2]);
#endif
}

namespace nontype_template_parameter_auto_test
{

#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)

template <auto x>
struct X {};

void f() {}

#endif

GTEST_TEST(ConfigTest, Cxx17NontypeTemplateParameterAutoTest)
{
#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)
	X<0> x1;
	X<0l> x2;
	X<&f> x3;
	(void)x1;
	(void)x2;
	(void)x3;
#endif
}

}	// namespace nontype_template_parameter_auto_test

namespace namespace_attributes_test
{

#if defined(HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES)

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wattributes")

namespace[[deprecated]] bar
{
	int var_a;
}

HAMON_WARNING_POP()

#endif	// defined(HAMON_HAS_CXX17_NAMESPACE_ATTRIBUTES)

}	// namespace namespace_attributes_test

namespace enumerator_attributes_test
{

#if defined(HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES)

enum FOO
{
	FOO_A,
	FOO_B[[deprecated]],
	FOO_C,
};

#endif	// defined(HAMON_HAS_CXX17_ENUMERATOR_ATTRIBUTES)

}	// namespace enumerator_attributes_test

namespace nested_namespace_definitions_test
{

#if defined(HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS)

namespace aaa::bbb::ccc
{
	void f() {}
}

#endif	// defined(HAMON_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS)

}	// namespace nested_namespace_definitions_test

namespace inheriting_constructors_test
{
#if defined(HAMON_HAS_CXX17_INHERITING_CONSTRUCTORS)

// TODO

#endif
}

namespace variadic_using_test
{

#if defined(HAMON_HAS_CXX17_VARIADIC_USING)
template <typename... Types>
struct S : Types...
{
	using Types::operator()...;
	int operator () (long) { return 0; }
};
#else
template <typename T1, typename T2>
struct S : T1, T2
{
	using T1::operator();
	using T2::operator();
	int operator () (long) { return 0; }
};
#endif

struct A
{
	int operator () (int) { return 1; }
};

struct B
{
	int operator () (double) { return 2; }
};

GTEST_TEST(ConfigTest, Cxx17VariadicUsingTest)
{
	S<A, B> s;
	EXPECT_EQ(1, s(0));
	EXPECT_EQ(0, s(0L));
	EXPECT_EQ(2, s(0.0));
}

}	// namespace variadic_using_test

GTEST_TEST(ConfigTest, Cxx17FallthroughTest)
{
#if defined(HAMON_HAS_CXX17_FALLTHROUGH)
	int n = 2;
	int count = 0;
	switch (n)
	{
	case 1:
	case 2:
		count++;
		[[fallthrough]];
	case 3:
		count++;
		break;
	}
	EXPECT_EQ(2, count);
#endif
}

namespace nodiscard_test
{

#if defined(HAMON_HAS_CXX17_NODISCARD)

struct [[nodiscard]] error_info {};

error_info f() { return error_info{}; }

[[nodiscard]] int g() { return 0; }

#endif

GTEST_TEST(ConfigTest, Cxx17NodiscardTest)
{
#if defined(HAMON_HAS_CXX17_NODISCARD)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4834)	// 'nodiscard' 属性を持つ関数の戻り値を破棄しています
HAMON_WARNING_DISABLE_CLANG("-Wunused-result")
HAMON_WARNING_DISABLE_GCC("-Wunused-result")

	f();
	g();

HAMON_WARNING_POP()
#endif
}

}	// namespace nodiscard_test

namespace maybe_unused_test
{

#if defined(HAMON_HAS_CXX17_MAYBE_UNUSED)

void f(bool flag1, [[maybe_unused]] bool flag2)
{
	[[maybe_unused]]bool b2 = flag1;
}

#endif

GTEST_TEST(ConfigTest, Cxx17MaybeUnusedTestTest)
{
#if defined(HAMON_HAS_CXX17_MAYBE_UNUSED)
	f(true, true);
#endif
}

}	// namespace maybe_unused_test

#if defined(HAMON_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES)

// TODO

#endif

namespace ignoring_unrecognized_attributes_test
{

#if defined(HAMON_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES)

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wattributes")
HAMON_WARNING_DISABLE_CLANG("-Wunknown-attributes")
HAMON_WARNING_DISABLE_MSVC(5030)	// 属性 '...' は認識されません

[[UNKNOWN::unknown_attribute]] void f() {}

HAMON_WARNING_POP()

#endif

}

GTEST_TEST(ConfigTest, Cxx17StructuredBindingsTest)
{
#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)
	auto [id, message] = std::make_pair(3, std::string("hoge"));
	EXPECT_EQ(3, id);
	EXPECT_EQ("hoge", message);

	auto [x, y, z] = std::make_tuple(0.5f, std::string("foo"), 42);
	EXPECT_EQ(0.5f, x);
	EXPECT_EQ("foo", y);
	EXPECT_EQ(42, z);

	int a[] = {3, 1, 4};
	auto [a0, a1, a2] = a;
	EXPECT_EQ(3, a0);
	EXPECT_EQ(1, a1);
	EXPECT_EQ(4, a2);
#endif
}

namespace aggregate_bases_test
{

struct base
{
	int i;
};

struct derived : base
{
};

HAMON_WARNING_PUSH()
#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 30700) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wbraced-scalar-init")
#endif

GTEST_TEST(ConfigTest, Cxx17AggregateBasesTest)
{
	base b{42};
	EXPECT_EQ(42, b.i);
#if defined(HAMON_HAS_CXX17_AGGREGATE_BASES)
	derived d{{42}};
	EXPECT_EQ(42, d.i);
#endif
}

HAMON_WARNING_POP()

}

namespace init_enum_class_test
{

enum class Handle : unsigned { Invalid = 0 };

GTEST_TEST(ConfigTest, Cxx17InitEnumClassTest)
{
#if defined(HAMON_HAS_CXX17_INIT_ENUM_CLASS)
	Handle h { 42 };
	EXPECT_EQ((unsigned)42, (unsigned)h);
#endif
}

}	// namespace init_enum_class_test

namespace template_template_typename_test
{

#if defined(HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME)

template <template <typename> class X> struct S1;
template <template <typename> typename X> struct S2;

#endif	// defined(HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME)

}	// namespace template_template_typename_test

#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_ARGS)
namespace nontype_template_args_test
{

template <const int* pci> struct X {};
int ai[10];
X<ai> xi;  // ok: array to pointer conversion and cv-qualification conversion
 
struct Y {};
template <const Y& b> struct Z {};
Y y;
Z<y> z;  // ok: no conversion
 
template <int (&pa)[5]> struct W {};
int b[5];
W<b> w; // ok: no conversion
 
void f(char) {}
void f(int) {}
template <void (*pf)(int)> struct A {};
A<&f> a; // ok: overload resolution selects f(int)

template <typename T, const char* p> class X2 {};
//X2<int, "Studebaker"> x1; // error: string literal as template-argument
 
template <int* p> class X3 {};
int ar[10];
struct S
{
    int m;
    static int s;
} s;
int S::s = 0;
//X3<&ar[2]> x3;  // error: address of array element
//X3<&s.m> x4;   // error: address of non-static member
X3<&s.s> x5;   // ok: address of static member
X3<&S::s> x6;  // ok: address of static member
 
template <const int& CRI> struct B {};
//B<1> b2;     // error: temporary would be required for template argument
int c = 1;
B<c> b1;     // ok

}
#endif

namespace exception_specifications_test
{

#if defined(HAMON_HAS_CXX17_EXCEPTION_SPECIFICATIONS)
void f() noexcept(false);
#else
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4290)	// C++ の例外の指定は無視されます。
HAMON_WARNING_DISABLE_GCC("-Wdeprecated")

void f() throw(std::runtime_error);

HAMON_WARNING_POP()
#endif

}

#if defined(HAMON_HAS_CXX17_HAS_INCLUDE)

#if __has_include(<hoge>)
#endif

#endif

#if defined(HAMON_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS)

namespace template_template_args_test
{

template <typename T> class A {};
template <typename T, typename U = T> class B {};
template <typename ... Types> class C {};
#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)
template <auto n> class D {};
#endif
template <template <typename> class P> class X {};
template <template <typename ...> class Q> class Y {};
template <template <int> class R> class Z {};
X<A> xa;
X<B> xb;
X<C> xc;
Y<A> ya;
Y<B> yb;
Y<C> yc;
#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)
Z<D> zd;
#endif

}

#endif

}	// namespace hamon_config_cxx17_test
