//�Զ��庯������
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
#include<vector>
#include<memory>
using pii = std::pair<int, int>;
using ll = long long int;
using std::vector;
//���ߺ���
 void DrawLine(CDC* pDC, const COLORREF& penColor, const COLORREF& backColor, 
	const pii& startPoint, const pii& endPoint);
//��Ⱦɫ����

//�е㺯�� 
const CPoint& avrPos(const vector<CPoint>& PS);
//
namespace J {
	//ʱ�䴦��
	ll systemtime2ms_sameDay(const SYSTEMTIME& st);
	void showLine(CDC* pDC, const CPoint leftTop, const CString& content);
	void showLine(CDC* pDC, const CPoint leftTop, const vector<CString>& content);
}
namespace J {
	std::shared_ptr<vector<vector<CRect>>> avgCRect(const CRect& area, size_t rowCount, size_t colCount);
}
#endif

