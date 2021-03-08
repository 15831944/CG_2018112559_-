//自定义函数如下
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
using pii = std::pair<int, int>;
//画线函数
 void DrawLine(CDC* pDC, const COLORREF& penColor, const COLORREF& backColor, 
	const pii& startPoint, const pii& endPoint);
//块染色函数

#endif

