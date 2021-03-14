#pragma once
#ifndef JBase_H
#define JBase_H

#include<vector>
using std::vector;
using std::pair;
using ll = long long;
namespace J {
	//时间处理
	ll systemtime2ms_sameDay(const SYSTEMTIME& st);
	void showLine(CDC* pDC, const CPoint leftTop, const CString& content);
}


#endif