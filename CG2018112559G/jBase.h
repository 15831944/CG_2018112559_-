#pragma once
#ifndef JBase_H
#define JBase_H
#include"Jalgo.h"
#include<vector>
#include<memory>
#pragma warning(disable:26451)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
using std::vector;
using std::pair;
using ll = long long;

#define noDelete(claNa,para) std::shared_ptr<claNa>(new claNa para).get()

namespace J {
	//时间处理
	ll systemtime2ms_sameDay(const SYSTEMTIME& st);
	void showLine(CDC* pDC, const CPoint leftTop, const CString& content);
}
namespace J {
	std::shared_ptr<vector<vector<CRect>>> avgCRect(const CRect& area, size_t rowCount, size_t colCount);
}

#endif