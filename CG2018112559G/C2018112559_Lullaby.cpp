#include "pch.h"
#include "C2018112559_Lullaby.h"
#include<memory>
#include<functional>

const COLORREF C2018112559_Lullaby::static_CPen(RGB(0, 0, 0));
const double C2018112559_Lullaby::PAI = 3.1415926;

inline COLORREF C2018112559_Lullaby::SetPixelWithLineFormat(HDC dc, int x, int y, COLORREF crColor, const LineFormat& lf)
{
	const int lw = lf.getLineWidth() / 2;
	for (int i = 0; i < lf.getLineWidth(); ++i)
		if (lf.formatMatrix[i][lf.cnt] == '0')continue;
		else
			::SetPixel(dc, x  , y+ lw - i, crColor);//take -y-  as grow basement
	lf.moveNextWidth();
	return crColor;
}
C2018112559_Lullaby::C2018112559_Lullaby(CWnd* pWnd) :
	CClientDC(pWnd)
{
}

void Class_func_Call C2018112559_Lullaby::DrawCoordinateAxis(const CPoint& s,
	const CPoint& e, COLORREF pen)
{
	if (s.x == e.x)
		for (size_t i = min(s.y, e.y); i <= max(s.y, e.y); ++i)
			SetPixel(s.x, i, pen);
	else
		for (size_t i = min(s.x, e.x); i <= max(s.x, e.x); ++i)
			SetPixel(i, s.y, pen);
}

void Class_func_Call C2018112559_Lullaby::DrawCoordinateAxisWithLineFormat(const CPoint& s, const CPoint& e, COLORREF pen, const LineFormat& lf)
{
	if (s.x == e.x)
		for (size_t i = min(s.y, e.y); i <= max(s.y, e.y); ++i)
			SetPixelWithLineFormat(m_hDC, s.x, i, pen,lf);
	else
		for (size_t i = min(s.x, e.x); i <= max(s.x, e.x); ++i)
			SetPixelWithLineFormat(m_hDC, i, s.y, pen,lf);
}

void Class_func_Call C2018112559_Lullaby::DemoLine(const CPoint& start,
	const CPoint& end, COLORREF pen)
{
	auto oldPen = SelectObject(noDelete(CPen, (1, 1, pen)));
	MoveTo(start);
	LineTo(end);
	SelectObject(oldPen);

}

void Class_func_Call C2018112559_Lullaby::DDALine(const CPoint& s, const CPoint& e, COLORREF pen)
{
	size_t pixelCount = max(abs(e.x - s.x), abs(e.y - s.y));
	float increX = float(e.x - s.x) / pixelCount;
	float increY = float(e.y - s.y) / pixelCount;
	if (e.x == s.x)increX = 0.0;
	if (e.y == s.y)increY = 0.0;
	float curX = s.x, curY = s.y;
	do
	{
		SetPixel(curX += increX, curY += increY, pen);
	} while (pixelCount--);
}

void Class_func_Call  C2018112559_Lullaby::MIDLine(const CPoint& s, const CPoint& e,
	COLORREF pen = static_CPen)
{
	//后边有求斜率值，所以索性分开处理特殊情况
	if (s.x == e.x || s.y == e.y)
		return DrawCoordinateAxis(s, e, pen);
	//x:x画点的起始点的x值，y:前之对应y值，xEnd：x末值
	if (abs(s.x - e.x) >= abs(s.y - e.y))
		MIDLineInBaseX(s, e, pen);
	else
		MIDLineInBaseY(s, e, pen);
}

void Class_func_Call C2018112559_Lullaby::MIDLineInBaseX(const CPoint& s, const CPoint& e,
	COLORREF pen, std::function<COLORREF(HDC, int, int, COLORREF)>setPixelWhile)
{
	int x, y, xEnd;
	if (s.x <= e.x)
	{
		x = s.x;
		y = s.y;
		xEnd = e.x;
	}
	else
	{
		x = e.x;
		y = e.y;
		xEnd = s.x;
	}
	// 一次函数表达直线    f(x,y)= a * x + b * y +c 
	int a = s.y - e.y;
	int finalB = e.x - s.x;
	//int c = s.x * e.y - e.x * s.y;
	//斜率本值
	double whole_K = double(-a) / finalB;
	//将斜率修正为 kInteger+ kFraction,其中 kFraction是 -a/b,a和b是修正后的值 
	//修正后我们相当于是在另一个相对坐标系中作图，坐标系s'之于原坐标系s为
	//s'.x=s.x ;  s'.y=s.y + kInteger * delta(x,0)
	const int kInteger = floor(whole_K);
	//a += kInteger * b;
	const int finalA = a + kInteger * finalB;
	//这个式子比较有意思
	// 2* (  f(x+1,y+1/2) - f(x0,y0) ) 括号内后者为0，...
	int p = 2 * finalA + finalB;
	const int plusIncre = 2 * finalA;
	const int negIncre = 2 * (finalA + finalB);
	do
	{
		setPixelWhile(m_hDC, x, y, pen);
		x++;
		if (p > 0)
		{
			y += kInteger;//修正后的y增量
			p += plusIncre;
		}
		else
		{
			y += kInteger + 1;//修正后的y增量
			p += negIncre;
		}
	} while (x < xEnd);
}

void Class_func_Call C2018112559_Lullaby::MIDLineInBaseY(const CPoint& s, const CPoint& e,
	COLORREF pen, std::function<COLORREF(HDC, int, int, COLORREF)>setPixelWhile)
{
	int x, y, yEnd;
	if (s.y <= e.y)
	{
		x = s.x;
		y = s.y;
		yEnd = e.y;
	}
	else
	{
		x = e.x;
		y = e.y;
		yEnd = s.y;
	}
	// 一次函数表达直线    f(x,y)= a * x + b * y +c 
	int a = s.x - e.x;
	int finalB = e.y - s.y;
	if (finalB > 0)
		finalB *= -1, a *= -1;
	int c = e.x * s.y - s.x * e.y;
	//斜率本值
	double whole_K = double(-a) / finalB;
	const int kInteger = floor(whole_K);
	//a += kInteger * b;
	const int finalA = a + kInteger * finalB;
	int p = 2 * finalA + finalB;
	const int plusIncre = 2 * finalA;
	const int negIncre = 2 * (finalA + finalB);
	do
	{
		setPixelWhile(m_hDC, x, y, pen);
		y++;
		if (p >= 0)
		{
			x += kInteger + 1;//修正后的y增量
			p += negIncre;
		}
		else
		{
			x += kInteger;//修正后的y增量
			p += plusIncre;
		}
	} while (y < yEnd);
};
void Class_func_Call C2018112559_Lullaby::BreshenHamLine(const CPoint& start, const CPoint& end, COLORREF pen)
{
	return void();
}

void Class_func_Call C2018112559_Lullaby::MidCircle(
	const CPoint& center, const size_t radius)
{
	int cx = center.x, cy = center.y;
	int x = 0, y = radius;
	double d = 1.25 - y;
	circlePlot(cx, cy, x, y);
	CF_t< C2018112559_Lullaby, void, int, int, int, int> cf;
	CMF2CF<C2018112559_Lullaby, void, int, int, int, int>
		(&C2018112559_Lullaby::circlePlot, cf);
	auto circlePlotX = std::bind(cf, dynamic_cast<void*>(this),
		cx, cy, std::placeholders::_1, std::placeholders::_2);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		circlePlotX(x, y);
	}
	return;
}

void Class_func_Call C2018112559_Lullaby::BreshenhamCircle(
	const CPoint& center, const size_t radius)
{
	int cx = center.x, cy = center.y;
	int x = 0, y = radius;
	int d = 3 - 2 * y;
	circlePlot(cx, cy, x, y);
	CF_t< C2018112559_Lullaby, void, int, int, int, int> cf = NULL;
	CMF2CF<C2018112559_Lullaby, void, int, int, int, int>
		(&C2018112559_Lullaby::circlePlot, cf);
	auto circlePlotX = std::bind(cf, dynamic_cast<void*>(this),
		cx, cy, std::placeholders::_1, std::placeholders::_2);
	while (x < y)
	{
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
		circlePlotX(x, y);
	}
	return;
}

void Class_func_Call C2018112559_Lullaby::MidEllipsolid(
	const CRect& center)
{
	int cx = (center.left + center.right) / 2;
	int cy = (center.top + center.bottom) / 2;
	int rx = center.right - cx;
	int ry = center.bottom - cy;
	int rxp2 = rx * rx;
	int ryp2 = ry * ry;
	auto p = pow(ry, 4) / (pow(rx, 2) + pow(ry, 2));
	int slimY = sqrt(p);
	int slimX = sqrt(p) * rxp2 / ryp2;
	//对标x draw x in (0,slimX)
	int x = 0;
	int y = ry;
	int d = (8 * x + 4) * ryp2 + (-4 * y + 1) * rxp2;
	while (x < slimX)
	{
		++x;
		if (d > 0)
		{
			--y;
			d += (8 * x + 4) * ryp2 + (-8 * y) * rxp2;
		}
		else
		{
			d += (8 * x + 4) * ryp2;
		}
		ellipPlot(cx, cy, x, y);
	}
	//对标 y draw x in(slimX,rx]
	//cur (x,y) 
	d = (2 * x + 1) * (2 * x + 1) * ryp2 + (2 * y - 2) * (2 * y - 2) * rxp2 - 4 * rxp2 * ryp2;
	while (y > 0 || x < rx)
	{
		--y;
		if (d < 0)
		{
			++x;
			//气死X了，x的参数反推才对了，之前兑换参数兑错地方了
			d += (8 * x) * ryp2 + (-8 * y + 4) * rxp2;
		}
		else
		{
			d += (-8 * y + 4) * rxp2;
		}
		ellipPlot(cx, cy, x, y);
	}
	return;
}

void Class_func_Call C2018112559_Lullaby::MidCircleArc(const CPoint& center, const size_t radius, const double& arcS, const double& arcE)
{
	int cx = center.x, cy = center.y;
	int x = 0, y = radius;
	double d = 1.25 - y;
	auto rangeJudge = [&](int ax, int ay)
	{
		double arc = Line2K2Arc(cx, cy, ax, ay);
		auto ret = arcS < arc&& arc <= arcE;
		return ret;
	};
	circlePlot_in_range(cx, cy, x, y, rangeJudge);
	//CF_t< C2018112559_Lullaby, void, int, int, int, int> cf;
	//CMF2CF<C2018112559_Lullaby, void, int, int, int, int>
	//	(&C2018112559_Lullaby::circlePlot, cf);
	//auto circlePlotX = std::bind(cf, dynamic_cast<void*>(this),
	//	cx, cy, std::placeholders::_1, std::placeholders::_2);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		circlePlot_in_range(cx, cy, x, y, rangeJudge);
	}
	return;

}

void Class_func_Call C2018112559_Lullaby::MidEllipsolidArc(const CRect& center, const double& arcS, const double& arcE)
{
	int cx = (center.left + center.right) / 2;
	int cy = (center.top + center.bottom) / 2;
	int rx = center.right - cx;
	int ry = center.bottom - cy;
	int rxp2 = rx * rx;
	int ryp2 = ry * ry;
	auto p = pow(ry, 4) / (pow(rx, 2) + pow(ry, 2));
	int slimY = sqrt(p);
	int slimX = sqrt(p) * rxp2 / ryp2;
	//对标x draw x in (0,slimX)
	int x = 0;
	int y = ry;
	int d = (8 * x + 4) * ryp2 + (-4 * y + 1) * rxp2;
	auto rangeJudge = [&](int ax, int ay)
	{
		double arc = Line2K2Arc(cx, cy, ax, ay);
		auto ret = arcS < arc&& arc <= arcE;
		return ret;
	};
	while (x < slimX)
	{
		++x;
		if (d > 0)
		{
			--y;
			d += (8 * x + 4) * ryp2 + (-8 * y) * rxp2;
		}
		else
		{
			d += (8 * x + 4) * ryp2;
		}
		ellipPlot_in_range(cx, cy, x, y, rangeJudge);
	}
	//对标 y draw x in(slimX,rx]
	//cur (x,y) 
	d = (2 * x + 1) * (2 * x + 1) * ryp2 + (2 * y - 2) * (2 * y - 2) * rxp2 - 4 * rxp2 * ryp2;
	while (y > 0 || x < rx)
	{
		--y;
		if (d < 0)
		{
			++x;
			//气死X了，x的参数反推才对了，之前兑换参数兑错地方了
			d += (8 * x) * ryp2 + (-8 * y + 4) * rxp2;
		}
		else
		{
			d += (-8 * y + 4) * rxp2;
		}
		ellipPlot_in_range(cx, cy, x, y, rangeJudge);
	}

	return;
}

void Class_func_Call C2018112559_Lullaby::MidLineWithLineFormat(const CPoint& s, const CPoint& e, COLORREF pen, const LineFormat& lf)
{
	//后边有求斜率值，所以索性分开处理特殊情况
	if (s.x == e.x || s.y == e.y)
		return DrawCoordinateAxisWithLineFormat(s, e, pen,lf);
	//x:x画点的起始点的x值，y:前之对应y值，xEnd：x末值
	if (abs(s.x - e.x) >= abs(s.y - e.y))
		MIDLineInBaseXWithLineFormat(s, e, pen,lf);
	else
		MIDLineInBaseYWithLineFormat(s, e, pen,lf);
}

void Class_func_Call C2018112559_Lullaby::MIDLineInBaseXWithLineFormat(const CPoint& start, const CPoint& end, COLORREF pen, const LineFormat& lf)
{
	std::function<COLORREF(HDC, int, int, COLORREF)> p=std::bind(&C2018112559_Lullaby::SetPixelWithLineFormat, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4, lf);
	MIDLineInBaseX(start, end,pen,p);
}

void Class_func_Call C2018112559_Lullaby::MIDLineInBaseYWithLineFormat(const CPoint& start, const CPoint& end, COLORREF pen, const LineFormat& lf)
{

	std::function<COLORREF(HDC, int, int, COLORREF)> p=std::bind(&C2018112559_Lullaby::SetPixelWithLineFormat, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4, lf);
	MIDLineInBaseY(start, end,pen,p);
}


inline void Class_func_Call C2018112559_Lullaby::circlePlot(const int cx, const int cy, const int x, const int y)
{
	SetPixel(cx + x, cy + y, DWORD(0));
	SetPixel(cx + x, cy - y, DWORD(0));
	SetPixel(cx - x, cy + y, DWORD(0));
	SetPixel(cx - x, cy - y, DWORD(0));

	SetPixel(cx + y, cy + x, DWORD(0));
	SetPixel(cx + y, cy - x, DWORD(0));
	SetPixel(cx - y, cy + x, DWORD(0));
	SetPixel(cx - y, cy - x, DWORD(0));
	return;
}

inline void Class_func_Call C2018112559_Lullaby::ellipPlot(const int cx, const int cy, const int x, const int y)
{
	SetPixel(cx + x, cy + y, DWORD(0));
	SetPixel(cx + x, cy - y, DWORD(0));
	SetPixel(cx - x, cy + y, DWORD(0));
	SetPixel(cx - x, cy - y, DWORD(0));
	return;
}

inline double C2018112559_Lullaby::Line2K2Arc
(const int x0, const int y0, const int x1, const int y1)
{
	if (x0 == x1)return   y1 > y0 ? PAI * 3 / 2 : PAI / 2;
	//后面的加法项比较重要
	auto ret = atan((double(y1 - y0) / (x1 - x0))) + PAI * (x1 < x0);
	return ret;
}
