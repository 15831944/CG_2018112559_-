#pragma once
#include"pch.h"
#include"j1.2.h"
#include<vector>
#include<utility>
#include<memory>
using  std::vector;
const double PAI = 3.1415926;
void J::DrawFivePointStar(const CRect& area, CDC* pDC, size_t PointCount, size_t saa)
{
	//��ͼ��������ĵ��Լ�������İ뾶
	const CPoint center((area.left + area.right) / 2, (area.top + area.bottom) / 2);
	const size_t outlineCircleRadius = min(area.Width(), area.Height()) / 2;
	//����ǻ�����,�ɱ����
	const double eachAngle = 360.0 / PointCount;
	const double halfEachAngle = eachAngle / 2;
	//���㼯��
	vector<CPoint> allVertex;
	for (int i = 0; i < PointCount; ++i) {
		//��Χ��
		double offX = cos((i * eachAngle + saa) * PAI / 180) * outlineCircleRadius;
		double offY = -sin((i * eachAngle + saa) * PAI / 180) * outlineCircleRadius;
		//��Χ��
		double offXP = cos((i * eachAngle + saa + halfEachAngle) * PAI / 180) * outlineCircleRadius / 2;
		double offYP = -sin((i * eachAngle + saa + halfEachAngle) * PAI / 180) * outlineCircleRadius / 2;
		allVertex.emplace_back(offX + center.x, offY + center.y);
		allVertex.emplace_back(offXP + center.x, offYP + center.y);
	}
	//���򼯺�
	vector<CRgn> allRegion(2 * PointCount);
	//ָ�봫���lpArg������������ͷ�ʱ�������԰�������vectir�ֱ��pdc fill֮�����Զ��ͷ�
	vector<vector<CPoint>> lpArgs(2 * PointCount);
	auto ModI = [&](const size_t i)->size_t {return (i) % (2 * PointCount); };
	for (size_t i = 0; i < PointCount; ++i) {
		//��һ������
		lpArgs[i << 1].assign({ allVertex[i << 1],center,allVertex[(i << 1) + 1] });
		allRegion[i << 1].CreatePolygonRgn(lpArgs[i << 1].data(), 3, 1);//3��lpargָ��ָ�������ĳ���,�������ԭ��
		//�ڶ�������    nextIʹ�õ�i=PointCountʱ����allVertex�ķ��ʲ�Խ��
		lpArgs[(i << 1) + 1].assign({ allVertex[(i << 1) + 1],center,allVertex[ModI((i + 1) << 1)] });
		allRegion[(i << 1) + 1].CreatePolygonRgn(lpArgs[(i << 1) + 1].data(), 3, 1);
	}
	//Ⱦɫ
	//��Χ�߿�
	CPen pen(PS_SOLID, 5, RGB(255, 255, 0));//�������ʶ���
	CBrush CoRgn0, CoRgn1;
	CoRgn0.CreateSolidBrush(RGB(240, 30, 30));
	CoRgn1.CreateSolidBrush(RGB(240, 120, 30));
	pDC->SelectObject(pen);
	for (int i = 0; i < 2 * PointCount; ++i)
	{
		pDC->MoveTo(allVertex[i]);
		pDC->LineTo(allVertex[(i + 1) % (2 * PointCount)]);
		pDC->LineTo(center);
	}
	//��Χɫ��
	for (int i = 0; i < PointCount; ++i) {
		pDC->FillRgn(&allRegion[i << 1], &CoRgn0);
		pDC->FillRgn(&allRegion[(i << 1) + 1], &CoRgn1);
	}
}

void J::DrawTaiChiCircle(const CRect& area, CDC* pDC, size_t saa)
{
	//��ͼ��������ĵ��Լ�������İ뾶
	const CPoint center((area.left + area.right) / 2, (area.top + area.bottom) / 2);
	const size_t outlineCircleRadius = min(area.Width(), area.Height()) / 2;
	//������Բ��λ�� 
	constexpr double relativePos = 0.5;
	constexpr double relativeSize = 1.0 / 9;
	const double relativeRadius = relativeSize * outlineCircleRadius;
	const CPoint leftCircleCenter(center.x + relativePos * outlineCircleRadius*cos((saa+90)*PAI/180),
		center.y- relativePos * outlineCircleRadius * sin((saa + 90) * PAI / 180));
	const CPoint rightCircleCenter(center.x + relativePos * outlineCircleRadius * cos((saa - 90) * PAI / 180),
		center.y - relativePos * outlineCircleRadius * sin((saa - 90) * PAI / 180));
	CPen outlinePen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(outlinePen);
	//��Բ
	pDC->Ellipse(center.x - outlineCircleRadius, center.y - outlineCircleRadius,
		center.x + outlineCircleRadius, center.y + outlineCircleRadius);
	//��СԲ
	pDC->Ellipse(leftCircleCenter.x - relativeRadius, leftCircleCenter.y - relativeRadius,
		leftCircleCenter.x + relativeRadius, leftCircleCenter.y + relativeRadius);
	//��СԲ
	pDC->Ellipse(rightCircleCenter.x - relativeRadius, rightCircleCenter.y - relativeRadius,
		rightCircleCenter.x + relativeRadius, rightCircleCenter.y + relativeRadius);
	//��Բ��
	//�����ͽ�����
	const CPoint arcs[3] = {
		{int(center.x + outlineCircleRadius * cos((saa + 90) * PAI / 180)),
		int(center.y - outlineCircleRadius * sin((saa + 90) * PAI / 180))},
		center,
		{int(center.x + outlineCircleRadius * cos((saa - 90) * PAI / 180)),
		int(center.y - outlineCircleRadius * sin((saa - 90) * PAI / 180))},
	};
	//��
	pDC->Arc(int(area.left), int(area.top * 3 + area.bottom) / 4,
		(area.left + area.right) / 2, (area.top + 3 * area.bottom) / 4,
		(arcs[1].x), arcs[1].y, arcs[0].x, arcs[0].y);
	//�һ�
	pDC->Arc(int(area.left + area.right) / 2, int(area.top * 3 + area.bottom) / 4,
		int(area.right), (area.top + 3 * area.bottom) / 4,
		(arcs[1].x), arcs[1].y, arcs[2].x, arcs[2].y);
	//��ɫ  --��ɫ����
	CPen nullPen(PS_NULL, 0, RGB(255, 255, 255));
	pDC->MoveTo(center.x, center.y);
	pDC->BeginPath();
	pDC->AngleArc(center.x + cos((saa + 90) * PAI / 180) * outlineCircleRadius / 2,
		center.y - sin((saa + 90) * PAI / 2) * outlineCircleRadius / 2,
		outlineCircleRadius / 2,
		(saa - 90), 180);
	pDC->AngleArc(center.x, center.y, outlineCircleRadius, (saa + 90), 180);
	pDC->AngleArc(center.x + cos((saa - 90) * PAI / 180) * outlineCircleRadius / 2,
		center.y - sin((saa - 90) * PAI / 2) * outlineCircleRadius / 2,
		outlineCircleRadius / 2,
		(saa - 90), -180);
	pDC->EndPath();
	//brush of balck and white
	CBrush blackFishBrush; blackFishBrush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush whiteFishBrush; whiteFishBrush.CreateSolidBrush(RGB(255,255,255));
	CRgn leftFishRgn;
	leftFishRgn.CreateFromPath(pDC);
	pDC->InvertRgn(&leftFishRgn);
	pDC->FillRgn(&leftFishRgn, &blackFishBrush);
	// ��ɫ��ĺ���
	CRgn whiteFishBlackEye;
	whiteFishBlackEye.CreateEllipticRgn(
		rightCircleCenter.x - relativeRadius, rightCircleCenter.y - relativeRadius,
		rightCircleCenter.x + relativeRadius, rightCircleCenter.y + relativeRadius);
	pDC->InvertRgn(&whiteFishBlackEye);
	pDC->FillRgn(&whiteFishBlackEye, &blackFishBrush);
	// the white eye of the black fish
	CRgn blackFishWhiteEye;
	blackFishWhiteEye.CreateEllipticRgn(
		leftCircleCenter.x - relativeRadius, leftCircleCenter.y - relativeRadius,
		leftCircleCenter.x + relativeRadius, leftCircleCenter.y + relativeRadius);
	pDC->InvertRgn(&blackFishWhiteEye);
	pDC->FillRgn(&blackFishWhiteEye, &whiteFishBrush);
}

void J::DrawRandomLineAndPrintOverhead(const CRect& area, CDC* pDC, vector<size_t> testArgs)
{
	vector<vector<pair<pair<size_t, size_t>, pair<size_t, size_t>> > >liness(testArgs.size());
	//��������ı����� 
	vector<CString> csv(testArgs.size());

	for (int i = 0; i < testArgs.size(); ++i)
		liness[i].resize(testArgs[i]);
	auto getRandX = [&]()->size_t {
		return rand() % (area.right - area.left) + area.left; };
	auto getRandY = [&]()->size_t {
		return rand() % (area.bottom - area.top) + area.top; };
	//��������߶�
	for (auto& lines : liness)
	{
		//���������
		srand(unsigned(time(NULL)));
		for (auto& line : lines) {
			line.first = { getRandX(), getRandY() };
			line.second = { getRandX(), getRandY() };
		}
	};
	//����
	for (int i = 0; i < liness.size();++i) {
		//��ʼ��ʱ
		SYSTEMTIME t0, t1;
		GetLocalTime(&t0);
		for (auto& line : liness[i])
		{
			pDC->MoveTo(line.first.first, line.first.second);
			pDC->LineTo(line.second.first, line.second.second);
		}
		//������ʱ
		GetLocalTime(&t1);
		//������
		size_t overHead = systemtime2ms_sameDay(t1) - systemtime2ms_sameDay(t0);
		csv[i].Format(L"%8d:%d", liness[i].size(), overHead);
	}
	//�������
	size_t lineHeight = min(20, area.Height() / testArgs.size());
	for (int i = 0; i < testArgs.size(); ++i) {
		pDC->TextOutW(area.left + 5, area.top + 5 + lineHeight * i, csv[i]);
	}
}
