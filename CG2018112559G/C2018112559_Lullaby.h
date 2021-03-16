#pragma once
#include <afxwin.h>
#include"jBase.h"
#include"check.h"
/// <summary>
/// �Զ���
/// </summary>
class C2018112559_Lullaby :
    public CClientDC
{
private:
    const static COLORREF static_CPen;
public:
    C2018112559_Lullaby(CWnd* pWnd);
    /// <summary>
    /// �����ߣ�x���߻���y����
    /// </summary>
    /// <param name="start">��ʼ��</param>
    /// <param name="end">��β��</param>
    /// <param name="pen">��ɫ</param>
    void DrawCoordinateAxis(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);
    void DemoLine(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);
    void DDALine(const CPoint& start, const CPoint& end, 
        const COLORREF& pen = static_CPen);
    /// <summary>
    /// �е㻭��
    /// </summary>
    /// <param name="start">��ʼ��</param>
    /// <param name="end">��β��</param>
    /// <param name="pen">��ɫ</param>
    void MIDLine(const CPoint& start, const CPoint& end,
        const COLORREF& pen = static_CPen);

};

