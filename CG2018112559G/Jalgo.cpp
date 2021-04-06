#include "pch.h"
#include "Jalgo.h"

 void DrawLine(CDC* pDC, const COLORREF& penColor, const COLORREF& backColor,
    const pii& startPoint, const pii& endPoint){
    CPen NewPen, * p01dPen;
    NewPen.CreatePen(PS_SOLID, 1, penColor);
    p01dPen = pDC->SelectObject(&NewPen);
    CBrush NewBrush, * p01dBrush;
    NewBrush.CreateSolidBrush(backColor);
    p01dBrush = pDC->SelectObject(&NewBrush);
    pDC->MoveTo(startPoint.first, startPoint.second);
    pDC->LineTo(endPoint.first, endPoint.second);
    pDC->SelectObject(p01dPen);
    pDC->SelectObject(p01dBrush);
    NewPen.DeleteObject();
    NewBrush.DeleteObject();
    
}

 const CPoint& avrPos(const vector<CPoint>& PS)
 {
     const size_t vsz = PS.size();
     ll f, s = f = 0;
     for (auto& pii : PS)
         f += pii.x, s += pii.y;
     return { int(f / vsz),int(s / vsz )};
 }

 ll J::systemtime2ms_sameDay(const SYSTEMTIME& st)
 {
	 return (st.wHour * 3600 + st.wMinute * 60 + st.wSecond) * 1000 + st.wMilliseconds;
 }

 void J::showLine(CDC* pDC, const CPoint leftTop, const CString& content)
 {
	 pDC->TextOutW(leftTop.x, leftTop.y, content);
 }

 void J::showLine(CDC* pDC, const CPoint leftTop, const vector<CString>& content)
 {
	 for (int i = 0; i < content.size(); ++i) {
		 showLine(pDC, { leftTop.x,leftTop.y + i * 20 }, content[i]);
	 }
 }

 std::shared_ptr<vector<vector<CRect>>> J::avgCRect(const CRect& area, size_t rowCount, size_t colCount)
 {
	 std::shared_ptr<vector<vector<CRect>>> ret(new vector<vector<CRect>>
		 (rowCount, vector<CRect>(colCount)));
	 size_t x = area.left, y = area.top;
	 double increX = double(area.Width()) / colCount;
	 double increY = double(area.Height()) / rowCount;
	 for (int i = 0; i < rowCount; ++i) {
		 double cx = x;
		 for (int j = 0; j < colCount; ++j)
		 {
			 CRect& cur = (*ret.get())[i][j];
			 cur.left = cx;
			 cur.top = y;
			 cur.right = cx += increX;
			 cur.bottom = y + increY;
		 }
		 y += increY;
	 }
	 return ret;
 }
