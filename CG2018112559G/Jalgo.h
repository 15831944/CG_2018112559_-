//自定义函数如下
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
#include<vector>
#include<memory>
using pii = std::pair<int, int>;
using ll = long long int;
using std::vector;
//画线函数
 void DrawLine(CDC* pDC, const COLORREF& penColor, const COLORREF& backColor, 
	const pii& startPoint, const pii& endPoint);
//块染色函数

//中点函数 
const CPoint& avrPos(const vector<CPoint>& PS);
//
namespace J {
	//时间处理
	ll systemtime2ms_sameDay(const SYSTEMTIME& st);
	void showLine(CDC* pDC, const CPoint leftTop, const CString& content);
	void showLine(CDC* pDC, const CPoint leftTop, const vector<CString>& content);
}
namespace J {
	std::shared_ptr<vector<vector<CRect>>> avgCRect(const CRect& area, size_t rowCount, size_t colCount);
}
#endif

