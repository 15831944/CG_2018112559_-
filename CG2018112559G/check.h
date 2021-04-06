#pragma once
#ifndef CHECK_H
#define CHECK_H

#include"jBase.h"
#include"Jhead.h"
#include"Jalgo.h"
#include"pack.h"
/// <summary>
/// 检查画图是否可行
/// </summary>
/// <typeparam name="cls"></typeparam>
/// <typeparam name="retType"></typeparam>
/// <typeparam name="...paraType"></typeparam>
void test2_1(CWnd* pDC);
void test_2_1_efficiency(CWnd* pDC);
void test_2_1_efficiency_directive_msvcCall(CWnd* pDC);
template<class cls,class retType,class ...paraType>
using funcP = retType(cls::*)(paraType...);

//信息类
struct Tuple_exist {};
struct Tuple_nex {};
//基模型
template<class Cls, class funcP,
	/*template<typename lastZipPara> class tuple,*/ class ... unzipPara>
struct test {
	inline virtual void operator()(typename Cls& cls_instance ,funcP fp,
		 typename unzipPara... uzp) {
		((cls_instance.*fp))(uzp...);
	}
};
//带单参tuple的模型
template<class Cls, class funcP,
	typename firstZipPara, class ... unzipPara>
	struct test<Tuple_exist, Cls, funcP, tuple<firstZipPara>, unzipPara...> :
	test<Cls, funcP, firstZipPara, unzipPara...>
{};

template<class Cls, class funcP,
	typename firstZipPara, class ... unzipPara>
	struct test<Tuple_nex, Cls, funcP, tuple<firstZipPara>, unzipPara...> :
		test<Cls, funcP, tuple<firstZipPara>, unzipPara...>{
};
////带多参tuple的模型
//template<class Cls, class funcP,
//	 class ... zipPara>
//struct test<Tuple_exist,Cls,funcP,tuple<zipPara...>> :
//	test<CLs, funcP, tuple<lastZipPara...>, firstZipPara, unzipPara...>
//{
//};


template<class ...Type>
struct derTuple : std::tuple<Type...>{
	using base = tuple<Type...>;
	derTuple(Type... ts):tuple(ts...) {

	}
	void p() {
		cout << __func__ << endl;
	}
};
#endif