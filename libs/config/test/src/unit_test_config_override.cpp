/**
 *	@file	unit_test_config_override.cpp
 *
 *	@brief	HAMON_OVERRIDE のテスト
 */

#include <hamon/config.hpp>

namespace hamon_config_override_test
{

class base
{
	virtual void final_func() HAMON_FINAL;
	
	virtual void virtual_func();

	virtual void virtual_func2();

	void non_virtual_func();
};

class derived : public base
{
	// NG, finalとして宣言されている関数をオーバーライドすることはできない
	//void final_func() HAMON_OVERRIDE;
	
	// OK
	void virtual_func() HAMON_OVERRIDE;

	// NG, 基底クラスの関数と引数が違っており、オーバーライドできていない
	//void virtual_func2(int) HAMON_OVERRIDE;

	// NG, 基底クラスの関数ではないので、オーバーライドできていない
	//void func() HAMON_OVERRIDE;

	// NG, 基底クラスの関数は仮想ではないので、オーバーライドできていない
	//void non_virtual_func() HAMON_OVERRIDE;
};

}	// namespace hamon_config_override_test
