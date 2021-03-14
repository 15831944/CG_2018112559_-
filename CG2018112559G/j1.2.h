#pragma once
#ifndef J1_2_H
#define J1_2_H
//��ͼ�Զ��庯��ר�������ռ䣬��ֹ��ȫ�ֻ������������ֳ�ͻ
#include"jBase.h"
namespace J {
	/// <summary>
	/// ���������ǣ�ɫ�鲻���Զ���
	/// </summary>
	/// <param name="area">ͼ��λ��</param>
	/// <param name="pDC">ͼ���豸������</param>
	/// <param name="PointCount">����ǽ���</param>
	/// <param name="saa">symmetric axle angle���Գ���Ƕ�</param>
	void DrawFivePointStar(const CRect& area, CDC* pDC, size_t PointCount=5, size_t saa=90 );
	/// <summary>
	/// ����̬̫��ͼ
	/// </summary>
	/// <param name="area">ͼ��λ��</param>
	/// <param name="pDC">ͼ���豸������</param>
	/// <param name="saa">symmetric axle angle���Գ���Ƕ�</param>
	void DrawTaiChiCircle(const CRect& area, CDC* pDC,size_t saa=90);

	void DrawRandomLineAndPrintOverhead(const CRect& area, CDC* pDC, vector<size_t> testArgs);
}
#endif