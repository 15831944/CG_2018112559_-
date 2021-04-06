#include "pch.h"
#include<string>
#include "check.h"
#include"Jalgo.h"
void test2_1(CWnd* pDC)
{
	//���Ա����ָ������
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//�����Եĺ��������Ƕ���һ����ǩ������
	vector<funcPointer> funcs =
	{
		&C2018112559_Lullaby::DemoLine,
		&C2018112559_Lullaby::MIDLine,
		&C2018112559_Lullaby::BreshenHamLine
	};
	//���Զ���
	C2018112559_Lullaby obj(pDC);
	//�����ͻ�������
	CRect area;
	pDC->GetClientRect(&area);
	//�ѿͻ���ƽ�����ݣ�1 * 3
	auto ret = J::avgCRect(area, 1, funcs.size());
	//����һ�±ȽϺã���Ϊ��������Ҫ.get()��
	auto& gridss = (*ret.get());
	int dX = gridss[0][0].Width();
	int dY = gridss[0][0].Height();
	//��Ϊ��Щ�ط���Ҫƫ��һ��ģ���Ȼ��������ı�Ե�����ͽ�һ���ˣ�����ƫ����
	int offset = 40;
	//���ǵ������Ժ��������������ϵĵ��ǵ�λ�ã��Ǹ� 4*2 �ļ���
	vector<vector<CPoint> >ps = {
		{{offset,offset},{dX - offset,offset}},
		{{offset,dY / 3},{dX - offset,dY / 3}},
		{{offset,2 * dY / 3},{dX - offset,2 * dY / 3}},
		{{offset,dY - offset},{dX - offset,dY - offset}},
	};
	//���������ǣ����������ߺ������ߵ͵�б��
	vector<pair<CPoint, CPoint>> testExamples = {
		{ps[0][0],ps[3][0]},{ps[0][1],ps[3][1]},//y����
		{ps[0][0],ps[0][1]},{ps[3][0],ps[3][1]},//x����
		{ps[0][0],ps[1][1]},{ps[0][0],ps[2][1]},{ps[0][0],ps[3][1]},//�»���
		{ps[1][0],ps[0][1]},{ps[2][0],ps[0][1]},{ps[3][0],ps[0][1]}//�ϻ���
	};
	for (auto& pps : testExamples) {
		for (int i = 0; i < funcs.size(); ++i) {
			//ƫ������
			auto& modify = gridss[0][i].TopLeft();
			//���ݲ���
			(obj.*funcs[i])({ pps.first.x + modify.x,pps.first.y + modify.y },
				{ pps.second.x + modify.x ,pps.second.y + modify.y },
				RGB(0, 0, 0));
		}
	}
}

void test_2_1_efficiency(CWnd* pDC)
{
	C2018112559_Lullaby lull(pDC);
	vector<pair<CPoint, CPoint>> testData(1000);
	for (int i = 0; i < testData.size(); ++i) {
		testData[i].first.x = abs(rand() )% 1000;
		testData[i].first.y = abs(rand()) % 1000;
		testData[i].second.x = abs(rand()) % 1000;
		testData[i].second.y = abs(rand()) % 1000;
	}
	//���Ա����ָ������
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//�����Եĺ��������Ƕ���һ����ǩ������
	vector<funcPointer> funcs =
	{
		&C2018112559_Lullaby::DemoLine,
		&C2018112559_Lullaby::DDALine,
		&C2018112559_Lullaby::MIDLine,
		&C2018112559_Lullaby::BreshenHamLine
	};
	vector<CF_t<C2018112559_Lullaby, void, const CPoint&, const CPoint&, COLORREF>> cfPointers;
	for (auto cmf : funcs) {
		cfPointers.push_back(NULL);
		CMF2CF<C2018112559_Lullaby, void, const CPoint&, const CPoint&, COLORREF>(
			cmf, cfPointers.back()
			);
	}
	void* thisPointer = dynamic_cast<void*>(&lull);
	vector<CString> testResult(cfPointers.size());
	for (int i = 0; i < cfPointers.size(); ++i) {
		SYSTEMTIME s0, s1;
		GetLocalTime(&s0);
		for (int j = 0; j < testData.size(); ++j)
			cfPointers[i](thisPointer, testData[j].first, testData[j].second, 0);
		GetLocalTime(&s1);
		ll msOverhead = J::systemtime2ms_sameDay(s1) - J::systemtime2ms_sameDay(s0);
		testResult[i].Format(L"%s:%lld", CString(typeid(*(cfPointers[i])).name()).GetBuffer(),
			msOverhead);
	}
	for (int i = 0; i < cfPointers.size(); ++i)
		J::showLine(pDC->GetDC(), { 40,40 + 30 * i }, testResult[i]);
}

void test_2_1_efficiency_directive_msvcCall(CWnd* pDC) {
	C2018112559_Lullaby lull(pDC);
	vector<pair<CPoint, CPoint>> testData(1000000);
	for (int i = 0; i < testData.size(); ++i) {
		testData[i].first.x = rand() % 1000;
		testData[i].first.y = rand() % 1000;
		testData[i].second.x = rand() % 1000;
		testData[i].second.y = rand() % 1000;
	}
	vector<ll> ohs(4);
	{
		SYSTEMTIME s0, s1;
		GetLocalTime(&s0);
		for (int i = 0; i < testData.size(); ++i)
			lull.DemoLine(testData[i].first, testData[i].second,0);
		GetLocalTime(&s1);
		ll msOverhead = J::systemtime2ms_sameDay(s1) - J::systemtime2ms_sameDay(s0);
		ohs[0] = msOverhead;
	}
	{
		SYSTEMTIME s0, s1;
		GetLocalTime(&s0);
		for (int i = 0; i < testData.size(); ++i)
			lull.DDALine(testData[i].first, testData[i].second,0);
		GetLocalTime(&s1);
		ll msOverhead = J::systemtime2ms_sameDay(s1) - J::systemtime2ms_sameDay(s0);
		ohs[1] = msOverhead;
	}
	{
		SYSTEMTIME s0, s1;
		GetLocalTime(&s0);
		for (int i = 0; i < testData.size(); ++i)
			lull.MIDLine(testData[i].first, testData[i].second,0);
		GetLocalTime(&s1);
		ll msOverhead = J::systemtime2ms_sameDay(s1) - J::systemtime2ms_sameDay(s0);
		ohs[2] = msOverhead;
	}
	{
		SYSTEMTIME s0, s1;
		GetLocalTime(&s0);
		for (int i = 0; i < testData.size(); ++i)
			lull.BreshenHamLine(testData[i].first, testData[i].second,0);
		GetLocalTime(&s1);
		ll msOverhead = J::systemtime2ms_sameDay(s1) - J::systemtime2ms_sameDay(s0);
		ohs[3] = msOverhead;
	}
	vector<CString> outString;
	for (auto oh : ohs)
		outString.push_back(CString() + CString(std::to_string(oh).c_str()));
	J::showLine(pDC->GetDC(), { 10,10 }, outString);
}