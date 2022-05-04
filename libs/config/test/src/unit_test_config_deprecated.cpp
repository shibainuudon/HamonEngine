/**
 *	@file	unit_test_config_deprecated.cpp
 *
 *	@brief	HAMON_DEPRECATED のテスト
 */

#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4996)
HAMON_WARNING_DISABLE_GCC("-Wattributes")
HAMON_WARNING_DISABLE_GCC("-Wdeprecated-declarations")
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")

namespace hamon_config_deprecated_test
{

// 非推奨なクラス
class HAMON_DEPRECATED("please use new_class class") old_class{};

// 非推奨な型の別名
//using old_type HAMON_DEPRECATED("please use new_type type") = int;

// 非推奨な変数
HAMON_DEPRECATED("please use new_variable variable")
int old_variable;

struct X
{
	// 非推奨な非静的メンバ変数
	HAMON_DEPRECATED("please use new_member_variable")
	int old_member_variable;
};

// 非推奨な関数
HAMON_DEPRECATED("please use new_func() function")
void old_func() {}

// 非推奨な列挙型
enum class HAMON_DEPRECATED("please use new_enum") old_enum{};

template <typename T>
class class_templ;

// 非推奨なテンプレートの特殊化
template <>
class HAMON_DEPRECATED("don't use class_templ<int> specialization") class_templ<int> {};

void func()
{
#if 1
	old_class c;
	(void)c;
//	old_type t;

	old_variable = 1;

	X x;
	x.old_member_variable = 1;
	(void)x;

	old_func();

	old_enum e;
	(void)e;

	class_templ<int> ct;
	(void)ct;
#endif
}

}	// namespace hamon_config_deprecated_test

HAMON_WARNING_POP()
