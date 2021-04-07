#pragma once
#include <afxwin.h>
#include"jBase.h"
#include"check.h"
#include"DlgDynamicInputNeeds.h"
#include<iostream>
#include<fstream>
#include <string>
#include <functional>
/// <summary>
/// �Զ���
/// </summary>
class C2018112559_Lullaby :
	public CClientDC
{
private:
	const static COLORREF static_CPen;
public:
	/// <summary>
	/// ������
	/// </summary>
	class LineFormat {
	public :
		const std::vector<std::string> formatMatrix;
		mutable int cnt = 0;
		LineFormat() = default;
		LineFormat (const decltype(formatMatrix) f) :formatMatrix(f) {};
		size_t getLineWidth()const { 
			return formatMatrix.size(); 
		}
		const void moveNextWidth()const { if (++cnt == formatMatrix[0].size())cnt = 0; }
	};
	/// <summary>
	/// �򵥵�������
	/// </summary>
	class LineFormatSimple {
	public :
		const std::string lineType;
		const int lineWidth;
		LineFormatSimple() = default;
		LineFormatSimple(const std::string& l, const int& w) :lineType(l), lineWidth(w) {}
		LineFormat getLineFormat() { return LineFormat(std::vector<std::string>(lineWidth, lineType)); }
		~LineFormatSimple() = default;
	};

	//override 
	inline COLORREF SetPixel(int x, int y, COLORREF crColor) 
	{ ASSERT(m_hDC != NULL); return ::SetPixel(m_hDC, x, y, crColor); }
	// global setPixel COORREF(HDC,int,int,COLORREF)

	static inline COLORREF SetPixelWithLineFormat(HDC dc, int x, int y, COLORREF crColor, const LineFormat& lf);

	Class_func_Call  C2018112559_Lullaby(CWnd* pWnd);
	/// <summary>
	/// �����ߣ�x���߻���y����
	/// </summary>
	/// <param name="start">��ʼ��</param>
	/// <param name="end">��β��</param>
	/// <param name="pen">��ɫ</param>
	void Class_func_Call DrawCoordinateAxis(const CPoint& start, const CPoint& end,
		COLORREF pen = static_CPen);
	void Class_func_Call DrawCoordinateAxisWithLineFormat(const CPoint& start, const CPoint& end,
		COLORREF pen , const LineFormat& lf);
	void  Class_func_Call  DemoLine(const CPoint& start, const CPoint& end,
		COLORREF pen = static_CPen);
	void  Class_func_Call  DDALine(const CPoint& start, const CPoint& end,
		COLORREF pen = static_CPen);
	/// <summary>
	/// �е㻭��
	/// �ο�https://blog.csdn.net/qq_41883085/article/details/102730878
	/// </summary>
	/// <param name="start">��ʼ��</param>
	/// <param name="end">��β��</param>
	/// <param name="pen">��ɫ</param>
	void  Class_func_Call  MIDLine(const CPoint& start,
		const CPoint& end, COLORREF pen);
	
	void Class_func_Call MIDLineInBaseX(const CPoint& start,
		const CPoint& end, COLORREF pen, std::function<COLORREF(HDC, int, int, COLORREF)>setPixelWhile=std::bind(&::SetPixel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
	void Class_func_Call MIDLineInBaseY(const CPoint& start,
		const CPoint& end, COLORREF pen, std::function<COLORREF(HDC, int, int, COLORREF)>setPixelWhile=std::bind(&::SetPixel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
	void  Class_func_Call  BreshenHamLine(const CPoint& start,
		const CPoint& end, COLORREF pen);
	//Բ 
	void Class_func_Call MidCircle(
		const CPoint& center, const size_t radius);
	void Class_func_Call BreshenhamCircle(
		const CPoint& center, const size_t radius);
	void Class_func_Call MidEllipsolid(
		const CRect& center);
	//��
	void Class_func_Call MidCircleArc(
		const CPoint& center, const size_t radius, const double& arcS, const double& arcE);
	void Class_func_Call MidEllipsolidArc(
		const CRect& center, const double& arcS, const double& arcE);
	//�߿�����
	void Class_func_Call MidLineWithLineFormat(const CPoint& start,
		const CPoint& end, COLORREF pen, const LineFormat& lf);
	void Class_func_Call MIDLineInBaseXWithLineFormat(const CPoint& start,
		const CPoint& end, COLORREF pen, const LineFormat& lf);
	void Class_func_Call MIDLineInBaseYWithLineFormat(const CPoint& start,
		const CPoint& end, COLORREF pen, const LineFormat& lf);

private:
	/// <summary>
	/// ��Բʱ����ĳһ��λ�û��Գư˵�,Լ��������������ϵ��һ����
	/// </summary>
	/// <param name="cx">Բ��x</param>
	/// <param name="cy">Բ��y</param>
	/// <param name="x">���Բ�ĵ�x����</param>
	/// <param name="y">���Բ�ĵ�y����</param>
	inline void Class_func_Call circlePlot(
		const int cx, const int cy, const  int x, const int y);
	inline void Class_func_Call ellipPlot(
		const int cx, const int cy, const  int x, const int y);
	/// <summary>
	/// if t(x-cx,y-cy)==true then setPixel in each corresponding spot
	/// </summary>
	/// <typeparam name="test"></typeparam>
	template<class test>
	inline std::enable_if_t<std::is_same< decltype( std::declval<test>()(int(1),int(2))),bool>::value,void> Class_func_Call circlePlot_in_range(
		const int cx, const int cy, const  int x, const int y, test& t);
	template<class test>
	inline std::enable_if_t<std::is_same< decltype(std::declval<test>()(int(1),int(2))), bool>::value, void> Class_func_Call ellipPlot_in_range(const int cx, const int cy, const int x, const int y, test& t);
	/// <summary>if t(x,y)==true then setPixel    </summary>
	/// <typeparam name="test">ͨ����lambda����</typeparam>
	template<class test>
	inline void setPixel_in_range(const int x, const int y, test& t);

	inline double static Line2K2Arc(const int x0,const int  y0, const int x1,const int  y1);

	static const double PAI;
};

template<class test>
inline std::enable_if_t<std::is_same< decltype( std::declval<test>()(int(1),int(2))),bool>::value,void> Class_func_Call C2018112559_Lullaby::circlePlot_in_range(const int cx, const int cy, const int x, const int y, test& t)
{
	setPixel_in_range<decltype(t)>(cx + x, cy + y, t);
	setPixel_in_range(cx + x, cy - y, t);
	setPixel_in_range(cx - x, cy + y, t);
	setPixel_in_range(cx - x, cy - y, t);

	setPixel_in_range(cx + y, cy + x, t);
	setPixel_in_range(cx + y, cy - x, t);
	setPixel_in_range(cx - y, cy + x, t);
	setPixel_in_range(cx - y, cy - x, t);

	return;
}

template<class test>
inline std::enable_if_t<std::is_same< decltype( std::declval<test>()(int(1),int(2))),bool>::value,void> Class_func_Call C2018112559_Lullaby::ellipPlot_in_range(const int cx, const int cy, const int x, const int y, test &t)
{
	setPixel_in_range(cx + x, cy + y, t);
	setPixel_in_range(cx + x, cy - y, t);
	setPixel_in_range(cx - x, cy + y, t);
	setPixel_in_range(cx - x, cy - y, t);
	return;
}

template<class test>
inline void C2018112559_Lullaby::setPixel_in_range(const int x, const int y, test& t)
{
	if (t(x, y))
		SetPixel(x, y, 0);
}
