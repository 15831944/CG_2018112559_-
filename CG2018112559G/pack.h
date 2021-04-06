#pragma once
#ifndef PACK_H
#define PACK_H
#include"jBase.h"//���� Class_Func_Call
template<class C, class retType, class ...paras>
using CMF_t = retType(Class_func_Call C::*)(paras...);
template<class C, class retType, class ...paras>
using CF_t = retType(Class_func_Call*)(void*, paras...);


/// <summary>
/// ���Ա����ת��Ϊ��ͨ���� 
/// class member function (pointer) to common function (pointer)
/// </summary>
/// <typeparam name="From">���Ա����������</typeparam>
/// <typeparam name="To">ת������ͨ����������</typeparam>
/// <param name="cmf">ԭ��Ա����ָ��</param>
/// <param name="cf">ת���ĺ���ָ��</param>
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
