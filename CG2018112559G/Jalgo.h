//自定义函数如下
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
#include<vector>
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

#endif

