/**
 *	@file	unit_test_config_final.cpp
 *
 *	@brief	HAMON_FINAL のテスト
 */

#include <hamon/config.hpp>

namespace hamon_config_final_test
{

class base
{
	virtual void final_func() HAMON_FINAL;
	
	virtual void virtual_func();

	// NG, 仮想でない関数にfinal宣言することはできない
	//void non_virtual_func() HAMON_FINAL;
};

class derived : public base
{
	// NG, finalとして宣言されている関数をオーバーライドすることはできない
	//void final_func();
	
	void virtual_func();
};

class non_base HAMON_FINAL {};

// NG, finalとして宣言されているクラスを継承することはできない
//class derived2 : public non_base {};

}	// namespace hamon_config_final_test
