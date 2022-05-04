/**
 *	@file	unit_test_config_cxx11.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4101)	// ローカル変数は 1 度も使われていません。
HAMON_WARNING_DISABLE_MSVC(4189)	// ローカル変数が初期化されましたが、参照されていません
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
HAMON_WARNING_DISABLE_GCC("-Wunused-variable")

namespace hamon_config_cxx11_test
{

namespace alignas_test
{

#if defined(HAMON_HAS_CXX11_ALIGNAS)

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4324)	// アラインメント指定子のために構造体がパッドされました

struct test
{
	//alignas(1) int i1;
	//alignas(2) int i2;
	//alignas(4) int i4;
	alignas(8) int i8;
	alignas(16) int i16;
	alignas(32) int i32;
};

struct alignas(32) hoge
{};

HAMON_WARNING_POP()

#endif	// defined(HAMON_HAS_CXX11_ALIGNAS)

}	// namespace alignas_test

namespace alignof_test
{

#if defined(HAMON_HAS_CXX11_ALIGNOF)

struct hoge
{
	char c[63];
	short s;
	double i;
};

struct empty
{};

static const std::size_t a1 = alignof(char);
static const std::size_t a2 = alignof(int);
static const std::size_t a3 = alignof(hoge);
static const std::size_t a4 = alignof(empty);
static const std::size_t a5 = alignof(void*);

#endif	// defined(HAMON_HAS_CXX11_ALIGNOF)

}	// namespace alignof_test

namespace auto_test
{

#if defined(HAMON_HAS_CXX11_AUTO_DECLARATIONS)

auto s_i = 0;
const auto s_l = 0L;
auto& s_r = s_i;
const auto& s_cr = s_i;
auto* s_p = &s_l;
const auto* s_cp = &s_l;

struct test
{
	static const auto sm_i = 0;
};

void func()
{
	auto i = 0;
	const auto f = 0.0f;
	auto& r = i;
	const auto& cr = f;
	auto* p = &f;
	const auto* cp = &i;

	int* dp = new auto(i);
	delete dp;

	std::vector<int> v(10);
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (auto x = *it)
		{
			std::cout << x;
		}
	}
}

#endif	// defined(HAMON_HAS_CXX11_AUTO_DECLARATIONS)

}	// namespace auto_test

namespace decltype_test
{

#if defined(HAMON_HAS_CXX11_DECLTYPE)

template <typename T, typename U>
auto add(const T& lhs, const U& rhs)
->decltype(lhs + rhs)
{
	return lhs + rhs;
}

void func()
{
	int i = 10;
	decltype(i) j = i;
	decltype((i)) k = i;
}

#endif	// defined(HAMON_HAS_CXX11_DECLTYPE)

}	// namespace decltype_test

namespace variadic_macros_test
{

int f0() { return 10; }
int f1(int) { return 20; }
int f2(int, int) { return 30; }
int f3(int, int, int) { return 40; }

GTEST_TEST(ConfigTest, Cxx11VariadicMacrosTest)
{
#if defined(HAMON_HAS_CXX11_VARIADIC_MACROS)

	#define FORWARD_ARGS(...) __VA_ARGS__

	EXPECT_EQ(10, f0(FORWARD_ARGS()));
	EXPECT_EQ(20, f1(FORWARD_ARGS(1)));
	EXPECT_EQ(30, f2(FORWARD_ARGS(2, 3)));
	EXPECT_EQ(40, f3(FORWARD_ARGS(4, 5, 6)));

#endif
}

}	// namespace variadic_macros_test

#if defined(HAMON_HAS_CXX11_CONSTEXPR)
namespace constexpr_test
{
	constexpr int square(int x)
	{
		return x * x;
	}

	class Integer
	{
		int m_value;

	public:
		constexpr Integer(int value)
			: m_value(value)
		{}

		constexpr int get() const
		{
			return m_value;
		}
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11ConstexprTest)
{
#if defined(HAMON_HAS_CXX11_CONSTEXPR)
	using namespace constexpr_test;

	constexpr int compile_time_result = square(3);
#if defined(HAMON_HAS_CXX11_STATIC_ASSERT)
	static_assert(compile_time_result == 9, "result must be 9");
#endif
	EXPECT_EQ(9, compile_time_result);
	{
		int a[compile_time_result];
	}

	int runtime_result = square(3);
	EXPECT_EQ(9, runtime_result);

	constexpr Integer x = 3;
#if defined(HAMON_HAS_CXX11_STATIC_ASSERT)
	static_assert(x.get() == 3, "x value must be 3");
#endif
	EXPECT_EQ(3, x.get());
	{
		int a[x.get()];
	}

#endif
}

namespace defaulted_functions_test
{

#if defined(HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS)

class X
{
public:
	virtual ~X() = default;
	inline X(const X&) = default;
};

#endif	// defined(HAMON_HAS_CXX11_DEFAULTED_FUNCTIONS)

}	// namespace defaulted_functions_test

namespace deleted_functions_test
{

#if defined(HAMON_HAS_CXX11_DELETED_FUNCTIONS)

class X
{
public:
	X(const X&) = delete;
	X& operator=(const X&) = delete;
};

#endif	// defined(HAMON_HAS_CXX11_DELETED_FUNCTIONS)

}	// namespace deleted_functions_test

#if defined(HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS)
namespace delegating_constructors_test
{
	struct X
	{
		int i_;

		X(int i) : i_(i) {}
		X() : X(42) {}
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11DelegatingConstructorsTest)
{
#if defined(HAMON_HAS_CXX11_DELEGATING_CONSTRUCTORS)
	using namespace delegating_constructors_test;

	X x;
	EXPECT_EQ(42, x.i_);
#endif
}

namespace explicit_conversion_operators_test
{

#if defined(HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS)

struct X
{
	explicit operator bool() const
	{
		return true;
	}
};

void test()
{
	X x{};

//	bool b1 = x;
	bool b2 = (bool)x;
	bool b3 = static_cast<bool>(x);
	bool b4 = bool(x);
//	bool b5 = x == true;
	bool b6 = !x;
	bool b7 = !!x;
	bool b8 = x && true;

	if (x) {}

	bool b9 = x ? true : false;
}

#endif	// defined(HAMON_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS)

}	// namespace explicit_conversion_operators_test

namespace extended_friend_declarations_test
{

#if defined(HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS)

template <typename Derived>
class base
{
	friend Derived;

	base() {}
};

class derived : public base<derived>
{
public:
	derived() {}
};

#endif	// defined(HAMON_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS)

}	// namespace extended_friend_declarations_test


#if defined(HAMON_HAS_CXX11_EXTENDED_SIZEOF)
namespace extended_sizeof_test
{
	struct hoge
	{
		int id;
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11ExtendedSizeofTest)
{
#if defined(HAMON_HAS_CXX11_EXTENDED_SIZEOF)
	EXPECT_EQ(sizeof(int), sizeof(extended_sizeof_test::hoge::id));
#endif
}

#if defined(HAMON_HAS_CXX11_EXTERN_TEMPLATE)
namespace extern_template_test
{
	template <typename T>
	class Foo {};

	template <typename T>
	void func() {}

	extern template class Foo<int>;
	extern template void func<int>();
}
#endif	// defined(HAMON_HAS_CXX11_EXTERN_TEMPLATE)

#if defined(HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS)
namespace inheriting_constructors_test
{
	struct Base1
	{
		Base1() : i(0) {}
		Base1(int n) : i(n) {}

		int i;
	};

	struct Base2
	{
		Base2() : s() {}
		Base2(const std::string& x) : s(x) {}

		std::string s;
	};

	struct Derived : Base1, Base2
	{
		using Base1::Base1;
		using Base2::Base2;
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11InheritingConstructorsTest)
{
#if defined(HAMON_HAS_CXX11_INHERITING_CONSTRUCTORS)
	using namespace inheriting_constructors_test;

	Derived d0;
	Derived d1(3);
	Derived d2("hello");

	EXPECT_EQ(0,  d0.i);
	EXPECT_EQ("", d0.s);
	EXPECT_EQ(3,  d1.i);
	EXPECT_EQ("", d1.s);
	EXPECT_EQ(0,       d2.i);
	EXPECT_EQ("hello", d2.s);
#endif
}

GTEST_TEST(ConfigTest, Cxx11LambdasTest)
{
#if defined(HAMON_HAS_CXX11_LAMBDAS)
	{
		auto plus = [](int a, int b) { return a + b; };
		int result = plus(2, 3);
		EXPECT_EQ(5, result);
	}
	{
		int x = 3;
		auto f = [&] { x = 1; };
		f();
		EXPECT_EQ(1, x);
	}
	{
		int x = 3;
		auto f = [=] { return x + 1; };
		int result = f();
		EXPECT_EQ(4, result);
		EXPECT_EQ(3, x);
	}
#endif
}

namespace local_type_template_args_test
{

template <typename T>
int to_int(T x) { return static_cast<int>(x); }

GTEST_TEST(ConfigTest, Cxx11LocalTypeTemplateArgsTest)
{
#if defined(HAMON_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS)

	enum { E1, E2 };

	int value1 = to_int(E1);
	int value2 = to_int(E2);

	EXPECT_EQ(0, value1);
	EXPECT_EQ(1, value2);
#endif
}

}	// namespace local_type_template_args_test

GTEST_TEST(ConfigTest, Cxx11LongLongTest)
{
#if defined(HAMON_HAS_CXX11_LONG_LONG)
	long long x = 123LL;
	EXPECT_EQ(123, x);
#endif
}

#if defined(HAMON_HAS_CXX11_INLINE_NAMESPACES)
namespace inline_namespaces_test
{
	inline namespace features
	{
		void f() {}
	}
}
#endif

GTEST_TEST(ConfigTest, Cxx11InlineNamespacesTest)
{
#if defined(HAMON_HAS_CXX11_INLINE_NAMESPACES)
	inline_namespaces_test::features::f();
	inline_namespaces_test::f();
#endif
}

GTEST_TEST(ConfigTest, Cxx11Char16TTest)
{
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	char16_t s[] = u"あいうえお";
#endif
}

GTEST_TEST(ConfigTest, Cxx11Char32TTest)
{
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	char32_t s[] = U"あいうえお";
#endif
}

GTEST_TEST(ConfigTest, Cxx11UnicodeLiteralsTest)
{
#if defined(HAMON_HAS_CXX11_UNICODE_LITERALS)
	auto s = u8"あいうえお";
#endif
}

GTEST_TEST(ConfigTest, Cxx11UniversalCharacterNameTest)
{
#if defined(HAMON_HAS_CXX11_UNIVERSAL_CHARACTER_NAME)
	{
		char16_t s[] = u"\U00020BB7野家"; // 吉野家
	}
	{
		char32_t s[] = U"\U00020BB7野家"; // 吉野家
	}
#endif
}

GTEST_TEST(ConfigTest, Cxx11RawStringsTest)
{
#if defined(HAMON_HAS_CXX11_RAW_STRINGS)
	{
		const char s[] = R"({"user_id": 123, "name": "Alice"})";
		EXPECT_STREQ("{\"user_id\": 123, \"name\": \"Alice\"}", s);
	}
	{
		const char s[] = R"*(ab)c)*";
		EXPECT_STREQ("ab)c", s);
	}
	{
		const char s[] = R"(a\b\\c\\\d)";
		EXPECT_STREQ("a\\b\\\\c\\\\\\d", s);
	}
#endif
}

#if defined(HAMON_HAS_CXX11_USER_DEFINED_LITERALS)

namespace user_defined_literals_test
{

int operator"" _ki(unsigned long long)
{
	return 1;
}

int operator"" _kj(const char*)
{
	return 2;
}

template <char... S>
int operator"" _kk()
{
	return 3;
}

float operator"" _kf(long double)
{
	return 4.0f;
}

float operator"" _kg(const char*)
{
	return 5.0f;
}

template <char... S>
float operator"" _kh()
{
	return 6.0f;
}

}	// namespace user_defined_literals_test

#endif	// defined(HAMON_HAS_CXX11_USER_DEFINED_LITERALS)

GTEST_TEST(ConfigTest, Cxx11UserDefinedLiteralsTest)
{
#if defined(HAMON_HAS_CXX11_USER_DEFINED_LITERALS)
	using namespace user_defined_literals_test;

	int   x1 = 123_ki;
	int   x2 = 456_kj;
	int   x3 = 789_kk;
	float x4 = 123.0_kf;
	float x5 = 456.0_kg;
	float x6 = 789.0_kh;

	EXPECT_EQ(1, x1);
	EXPECT_EQ(2, x2);
	EXPECT_EQ(3, x3);
	EXPECT_EQ(4, x4);
	EXPECT_EQ(5, x5);
	EXPECT_EQ(6, x6);
#endif
}

namespace trailing_return_type_test
{

#if defined(HAMON_HAS_CXX11_TRAILING_RETURN_TYPE)

auto f() -> int
{
	return 42;
}

auto g(int a, int b) -> decltype(a + b)
{
	return a + b;
}

#endif

GTEST_TEST(ConfigTest, Cxx11TrailingReturnTypeTest)
{
#if defined(HAMON_HAS_CXX11_TRAILING_RETURN_TYPE)
	EXPECT_EQ(42, f());
	EXPECT_EQ(5, g(2, 3));
#endif
}

}	// namespace trailing_return_type_test

GTEST_TEST(ConfigTest, Cxx11NullptrTest)
{
#if defined(HAMON_HAS_CXX11_NULLPTR)
	int* p = nullptr;
	EXPECT_TRUE(p == 0);
#endif
}

GTEST_TEST(ConfigTest, Cxx11RightAngleBracketsTest)
{
#if defined(HAMON_HAS_CXX11_RIGHT_ANGLE_BRACKETS)
	std::vector<std::vector<int>> v;
#endif
}

namespace rvalue_references_test
{

struct Foo
{
	Foo() {}

	Foo(const Foo&) = delete;
	Foo& operator=(const Foo&) = delete;

#if defined(HAMON_HAS_CXX11_RVALUE_REFERENCES)
	Foo(Foo&&) noexcept {}
	Foo& operator=(Foo&&) noexcept {return *this;}
#endif
};

GTEST_TEST(ConfigTest, Cxx11RvalueReferencesTest)
{
#if defined(HAMON_HAS_CXX11_RVALUE_REFERENCES)
	int x = 0;

	// lvalue reference
	int& lvalue_ref_1 = x;
//	int& lvalue_ref_2 = 0;

	// rvalue reference
//	int&& rvalue_ref_1 = x;
	int&& rvalue_ref_2 = 0;

	// const lvalue refere
	const int& const_lvalue_ref_1 = x;
	const int& const_lvalue_ref_2 = 0;

	Foo f1;
//	Foo f2(f1);
	Foo f3(std::move(f1));

	Foo f4;
//	f4 = f3;
	f4 = std::move(f3);
#endif
}

}	// namespace rvalue_references_test

#if defined(HAMON_HAS_CXX11_STATIC_ASSERT)

static_assert(true, "");
//static_assert(false, "");

#endif

namespace scoped_enums_test
{

#if defined(HAMON_HAS_CXX11_SCOPED_ENUMS)

enum class Color;
enum class CharColor : char;

enum class Color { Red, Green, Blue };
enum class CharColor : char { Red, Green, Blue };

//enum Enum1;
enum Enum2 : int;

enum Enum1 {A, B, C};
enum Enum2 : int {D, E};

#endif	// defined(HAMON_HAS_CXX11_SCOPED_ENUMS)

}	// namespace scoped_enums_test

namespace alias_templates_test
{

#if defined(HAMON_HAS_CXX11_ALIAS_TEMPLATES)

template <typename T>
using Vec = std::vector<T>;

using Integer = int;

#endif	// defined(HAMON_HAS_CXX11_ALIAS_TEMPLATES)

}	// namespace alias_templates_test

namespace unrestricted_unions_test
{

#if defined(HAMON_HAS_CXX11_UNRESTRICTED_UNIONS)

union X
{
	int m1;
	std::string m2;

	X() : m1(0) {}
	~X() {}
};

#endif	// defined(HAMON_HAS_CXX11_UNRESTRICTED_UNIONS)

}	// namespace unrestricted_unions_test

namespace variadic_templates_test
{

#if defined(HAMON_HAS_CXX11_VARIADIC_TEMPLATES)

template <typename... Args>
struct X;

template <typename... Args>
void f(Args... args);

#endif	// defined(HAMON_HAS_CXX11_VARIADIC_TEMPLATES)

}	// namespace variadic_templates_test

GTEST_TEST(ConfigTest, Cxx11RangeBasedForTest)
{
#if defined(HAMON_HAS_CXX11_RANGE_BASED_FOR)
	std::vector<int> v;

	for (auto e : v)
	{
		std::cout << e << std::endl;
	}

	for (const auto& e : v)
	{
		std::cout << e << std::endl;
	}

	for (auto& e : v)
	{
		std::cout << e << std::endl;
	}
#endif
}

namespace override_test
{

#if defined(HAMON_HAS_CXX11_OVERRIDE)

class base
{
	virtual void func_virt();
	virtual void func_virt_int(int a);
	void func_non_virt();
};

class derived : public base
{
	void func_virt() override;
//	void func_virt_int(short a) override;
//	void func_non_virt() override;
};

#endif	// defined(HAMON_HAS_CXX11_OVERRIDE)

}	// namespace override_test

namespace final_test
{

#if defined(HAMON_HAS_CXX11_FINAL)

class base
{
	virtual void func_final() final;
	virtual void func_virt();
};

class derived : public base
{
//	void func_final();
	void func_virt() override;
};

class base_f final
{
	virtual void func_virt();
};

//class derived_f : public base_f {};

#endif	// defined(HAMON_HAS_CXX11_FINAL)

}	// namespace final_test

namespace noreturn_test
{

#if defined(HAMON_HAS_CXX11_NORETURN)

[[noreturn]] void report_error()
{
	throw std::runtime_error("");
}

#endif	// defined(HAMON_HAS_CXX11_NORETURN)

}	// namespace noreturn_test

namespace carries_dependency_test
{

#if defined(HAMON_HAS_CXX11_CARRIES_DEPENDENCY)

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4648)	// 標準属性 'carries_dependency' は無視されます

[[carries_dependency]] void f()
{
}

void g(int* r[[carries_dependency]])
{
	(void)r;
}

HAMON_WARNING_POP()

#endif	// defined(HAMON_HAS_CXX11_CARRIES_DEPENDENCY)

}	// namespace carries_dependency_test

namespace ref_qualifiers_test
{

#if defined(HAMON_HAS_CXX11_REF_QUALIFIERS)
struct X
{
	X() {}
	
	int f() &
	{
		return 1;
	}

	int f() const&
	{
		return 2;
	}

	int f() &&
	{
		return 3;
	}
};
#endif

GTEST_TEST(ConfigTest, Cxx11RefQualifiersTest)
{
#if defined(HAMON_HAS_CXX11_REF_QUALIFIERS)
	X x;
	const X cx;

	EXPECT_EQ(1, x.f());
	EXPECT_EQ(2, cx.f());
	EXPECT_EQ(3, X().f());
#endif
}

}	// namespace ref_qualifiers_test

#if defined(HAMON_HAS_CXX11_NSDMI)
namespace nsdmi_test
{
	struct Person
	{
		int id = 3;
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11NsdmiTest)
{
#if defined(HAMON_HAS_CXX11_NSDMI)
	nsdmi_test::Person p;
	EXPECT_EQ(3, p.id);
#endif
}


#if defined(HAMON_HAS_CXX11_INITIALIZER_LISTS)
namespace initializer_lists_test
{
	template <typename T>
	class MyVector1
	{
		std::vector<T> data_;
	public:
		MyVector1(std::initializer_list<T> init)
			: data_(init.begin(), init.end()) {}
	};

	template <typename T>
	class MyVector2
	{
		std::vector<T> data_;
	public:
		explicit MyVector2(std::initializer_list<T> init)
			: data_(init.begin(), init.end()) {}
	};
}
#endif

GTEST_TEST(ConfigTest, Cxx11InitializerListsTest)
{
#if defined(HAMON_HAS_CXX11_INITIALIZER_LISTS)
	using namespace initializer_lists_test;
	{
		std::vector<int> v1 = {1, 2, 3};
		std::vector<int> v2 {1, 2, 3};
		v2 = {4, 5, 6};
	}
	{
		MyVector1<int> v1 = {1, 2, 3};
		MyVector1<int> v2 {1, 2, 3};
		v2 = {4, 5, 6};
	}
	{
//		MyVector2<int> v1 = {1, 2, 3};
		MyVector2<int> v2 {1, 2, 3};
//		v2 = {4, 5, 6};
	}
#endif
}


#if defined(HAMON_HAS_CXX11_UNIFORM_INITIALIZATION)
namespace uniform_initialization_test
{
	struct X
	{
		X() {}
		X(int) {}
	};

	struct Y
	{
		Y(int, double, std::string) {}
	};

	Y createY()
	{
		return {1, 3.14, "hello"};
	}
}
#endif

GTEST_TEST(ConfigTest, Cxx11UniformInitializationTest)
{
#if defined(HAMON_HAS_CXX11_UNIFORM_INITIALIZATION)
	using namespace uniform_initialization_test;

	X x1(0);
	X x2 = 0;
	X x3{0};
	X x4 = {0};
	X x5 {};

	Y y = createY();

	(void)x1;
	(void)x2;
	(void)x3;
	(void)x4;
	(void)x5;
	(void)y;
#endif
}


#if defined(HAMON_HAS_CXX11_NOEXCEPT)
namespace noexcept_test
{
	struct X
	{
		int func1() noexcept;
		int func2();
		int func3() noexcept(true);
		int func4() noexcept(false);
	};
}
#endif

void test()
{
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
	using namespace noexcept_test;

	X x;

#if defined(HAMON_HAS_CXX11_STATIC_ASSERT)
	static_assert( noexcept(x.func1()), "");
	static_assert(!noexcept(x.func2()), "");
	static_assert( noexcept(x.func3()), "");
	static_assert(!noexcept(x.func4()), "");
#endif

	EXPECT_TRUE (noexcept(x.func1()));
	EXPECT_FALSE(noexcept(x.func2()));
	EXPECT_TRUE (noexcept(x.func3()));
	EXPECT_FALSE(noexcept(x.func4()));
#endif
}

namespace sfinae_expr_test
{

#if 1//defined(HAMON_HAS_CXX11_SFINAE_EXPR)

typedef char yes;
struct no { char m[2]; };

template <typename T1, typename T2>
auto is_addable(T1 a, T2 b) -> decltype(a + b, yes())
{
	return yes{};
}

auto is_addable(...) -> no
{
	return no{};
}

struct X {};

void test()
{
	static_assert(sizeof(is_addable(3, 2))   == 1, "");
	static_assert(sizeof(is_addable(3, X())) == 2, "");
}

#endif	// defined(HAMON_HAS_CXX11_SFINAE_EXPR)

}	// namespace sfinae_expr_test

namespace thread_local_test
{

#if defined(HAMON_HAS_CXX11_THREAD_LOCAL)

int func()
{
	thread_local int x = 0;
	return x++;
}

#endif	// defined(HAMON_HAS_CXX11_THREAD_LOCAL)

}	// namespace thread_local_test

}	// namespace hamon_config_cxx11_test

HAMON_WARNING_POP()
