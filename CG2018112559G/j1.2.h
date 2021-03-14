#pragma once
#ifndef J1_2_H
#define J1_2_H
//画图自定义函数专有命名空间，防止与全局或其他函数名字冲突
#include"jBase.h"
namespace J {
	/// <summary>
	/// 画规则多角星，色块不可自定义
	/// </summary>
	/// <param name="area">图形位置</param>
	/// <param name="pDC">图形设备上下文</param>
	/// <param name="PointCount">多角星角数</param>
	/// <param name="saa">symmetric axle angle，对称轴角度</param>
	void DrawFivePointStar(const CRect& area, CDC* pDC, size_t PointCount=5, size_t saa=90 );
	/// <summary>
	/// 画静态太极图
	/// </summary>
	/// <param name="area">图形位置</param>
	/// <param name="pDC">图形设备上下文</param>
	/// <param name="saa">symmetric axle angle，对称轴角度</param>
	void DrawTaiChiCircle(const CRect& area, CDC* pDC,size_t saa=90);

	void DrawRandomLineAndPrintOverhead(const CRect& area, CDC* pDC, vector<size_t> testArgs);
}
#endif