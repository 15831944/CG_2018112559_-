#include "pch.h"
#include "C2018112559_Lullaby.h"
#include<memory>

const COLORREF C2018112559_Lullaby::static_CPen(RGB(0, 0, 0));

C2018112559_Lullaby::C2018112559_Lullaby(CWnd* pWnd) :
	CClientDC(pWnd)
{
}

void C2018112559_Lullaby::DrawCoordinateAxis(const CPoint& s, 
	const CPoint& e, const COLORREF& pen)
{
	int fx, fy;
	if (s.x == e.x)
		for (size_t i = min(s.y, e.y); i <= max(s.y, e.y); ++i)
			SetPixel(s.x, i, pen);
	else
		for (size_t i = min(s.x, e.x); i <= max(s.x, e.x); ++i)
			SetPixel(i, s.y, pen);
}

void C2018112559_Lullaby::DemoLine(const CPoint& start,
	const CPoint& end, const COLORREF& pen)
{
	auto oldPen = SelectObject(noDelete(CPen, (1, 1, pen)));
	MoveTo(start);
	LineTo(end);
	SelectObject(oldPen);
}

void C2018112559_Lullaby::DDALine(const CPoint& s, const CPoint& e, const COLORREF& pen)
{
	size_t pixelCount = max(abs(e.x - s.x), abs(e.y - s.y));
	float increX = float(e.x - s.x) / pixelCount;
	float increY = float(e.y - s.y) / pixelCount;
	if (e.x == s.x)increX = 0.0;
	if (e.y == s.y)increY = 0.0;
	float curX = s.x, curY = s.y;
	do {
		SetPixel(curX += increX, curY += increY, pen);
	} while (pixelCount--);
}

void C2018112559_Lullaby::MIDLine(const CPoint& s, const CPoint& e, const COLORREF& pen)
{
	//后边有求斜率值，所以索性分开处理特殊情况
	if (s.x == e.x || s.y == e.y)
		return DrawCoordinateAxis(s, e, pen);
	//x:x画点的起始点的x值，y:前之对应y值，xEnd：x末值
	int x, y, xEnd;
	if (s.x <= e.x)
	{
		x = s.x;
		y = s.y;
		xEnd = e.x;
	}
	else {
		x = e.x;
		y = e.y;
		xEnd = s.x;
	}
	// 一次函数表达直线    f(x,y)= a * x + b * y +c 
	int a = s.y - e.y;
	int b = e.x - s.x;
	//int c = s.x * e.y - e.x * s.y;
	//斜率本值
	double whole_K = double(-a) / b;
	//将斜率修正为 kInteger+ kFraction,其中 kFraction是 -a/b,a和b是修正后的值 
	//修正后我们相当于是在另一个相对坐标系中作图，坐标系s'之于原坐标系s为
	//s'.x=s.x ;  s'.y=s.y + kInteger * delta(x,0)
 	int kInteger = floor(whole_K);
	a += kInteger * b;
	//这个式子比较有意思
	// 2* (  f(x+1,y+1/2) - f(x0,y0) ) 括号内后者为0，...
	int p = 2 * a + b;
	do {
		SetPixel(x, y, pen);
		x++;
		if (p > 0) {
			y += kInteger;//修正后的y增量
			p += 2 * a;
		}
		else {
			y += kInteger + 1;//修正后的y增量
			p += 2 * (a + b);
		}
	} while (x < xEnd);

}

