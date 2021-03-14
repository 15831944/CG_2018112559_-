#include "pch.h"
#include "sd.h"

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

 const pii& avrPos(const vector<pii>& PS)
 {
     const size_t vsz = PS.size();
     ll f, s = f = 0;
     for (auto& pii : PS)
         f += pii.first, s += pii.second;
     return { f / vsz,s / vsz };
 }
