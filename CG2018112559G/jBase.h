#pragma once
#ifndef JBase_H
#define JBase_H
//#include"Jalgo.h"
//#include"pack.h"
#include<vector>
#include<memory>
#include<tuple>
#pragma warning(disable:26451)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
using std::vector;
using std::pair;
using std::tuple;
using std::tuple_element;
using std::tuple_element_t;
using ll = long long;

#define noDelete(claNa,para) std::shared_ptr<claNa>(new claNa para).get()
//类成员函数调用方式
#define Class_func_Call  __stdcall
//控制台debug
#define DTRACE(format,para) TRACE(#para":%"#format"\n",para) 

#endif