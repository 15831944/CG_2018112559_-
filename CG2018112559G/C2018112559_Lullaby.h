#pragma once
#include <afxwin.h>
#include"jBase.h"
#include"check.h"
/// <summary>
/// 自定义
/// </summary>
class C2018112559_Lullaby :
    public CClientDC
{
private:
    const static COLORREF static_CPen;
public:
    C2018112559_Lullaby(CWnd* pWnd);
    /// <summary>
    /// 画轴线，x轴线或者y轴线
    /// </summary>
    /// <param name="start">起始点</param>
    /// <param name="end">结尾点</param>
    /// <param name="pen">颜色</param>
    void DrawCoordinateAxis(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);
    void DemoLine(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);
    void DDALine(const CPoint& start, const CPoint& end, 
        const COLORREF& pen = static_CPen);
    /// <summary>
    /// 中点画线
    /// </summary>
    /// <param name="start">起始点</param>
    /// <param name="end">结尾点</param>
    /// <param name="pen">颜色</param>
    void MIDLine(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);

};

