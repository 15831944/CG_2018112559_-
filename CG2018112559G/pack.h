#pragma once
#ifndef PACK_H
#define PACK_H
#include"jBase.h"//引用 Class_Func_Call
template<class C, class retType, class ...paras>
using CMF_t = retType(Class_func_Call C::*)(paras...);
template<class C, class retType, class ...paras>
using CF_t = retType(Class_func_Call*)(void*, paras...);


/// <summary>
/// 类成员函数转换为普通函数 
/// class member function (pointer) to common function (pointer)
/// </summary>
/// <typeparam name="From">类成员函数的类型</typeparam>
/// <typeparam name="To">转化的普通函数的类型</typeparam>
/// <param name="cmf">原成员函数指针</param>
/// <param name="cf">转化的函数指针</param>
template<class C, class retType, class ...paras>
constexpr void CMF2CF(CMF_t<C, retType, paras...> cmf,
	CF_t<C, retType, paras...>& cf) {
	union {
		decltype(cmf) from;
		std::remove_reference_t<decltype(cf)> to;
	}un;
	un.from = cmf;
	cf = un.to;
};

template<class ...types>
struct pack {
	template<class Cls, class funcP>
	void call(Cls& cls_ins, funcP fp) {
		char c = transeform(1);
	}
};



#endif
