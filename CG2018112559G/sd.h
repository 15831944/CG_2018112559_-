//�Զ��庯������
#pragma once
#ifndef SD_H
#define SD_H
#include <afxwin.h>
#include <utility>
using pii = std::pair<int, int>;
//���ߺ���
 void DrawLine(CDC* pDC, const COLORREF& penColor, const COLORREF& backColor, 
	const pii& startPoint, const pii& endPoint);
//��Ⱦɫ����

#endif

