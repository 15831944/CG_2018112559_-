//�Զ��庯������
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
#include<vector>
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

#endif

