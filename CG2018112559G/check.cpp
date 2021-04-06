#include "pch.h"
#include<string>
#include "check.h"
#include"Jalgo.h"
void test2_1(CWnd* pDC)
{
	//类成员函数指针类型
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//待测试的函数，他们都有一样的签名参数
	vector<funcPointer> funcs =
	{
		&C2018112559_Lullaby::DemoLine,
		&C2018112559_Lullaby::MIDLine,
		&C2018112559_Lullaby::BreshenHamLine
	};
	//测试对象咯
	C2018112559_Lullaby obj(pDC);
	//整个客户区区域
	CRect area;
	pDC->GetClientRect(&area);
	//把客户区平分三份，1 * 3
	auto ret = J::avgCRect(area, 1, funcs.size());
	//引用一下比较好，因为操作不需要.get()啦
	auto& gridss = (*ret.get());
	int dX = gridss[0][0].Width();
	int dY = gridss[0][0].Height();
	//因为有些地方是要偏移一点的，不然相邻区域的边缘线条就接一起了，这是偏移量
	int offset = 40;
	//这是单个测试函数所属的区域上的点们的位置，是个 4*2 的集合
	vector<vector<CPoint> >ps = {
		{{offset,offset},{dX - offset,offset}},
		{{offset,dY / 3},{dX - offset,dY / 3}},
		{{offset,2 * dY / 3},{dX - offset,2 * dY / 3}},
		{{offset,dY - offset},{dX - offset,dY - offset}},
	};
	//这是线条们，测试了轴线和正负高低的斜线
	vector<pair<CPoint, CPoint>> testExamples = {
		{ps[0][0],ps[3][0]},{ps[0][1],ps[3][1]},//y轴线
		{ps[0][0],ps[0][1]},{ps[3][0],ps[3][1]},//x轴线
		{ps[0][0],ps[1][1]},{ps[0][0],ps[2][1]},{ps[0][0],ps[3][1]},//下划线
		{ps[1][0],ps[0][1]},{ps[2][0],ps[0][1]},{ps[3][0],ps[0][1]}//上划线
	};
	for (auto& pps : testExamples) {
		for (int i = 0; i < funcs.size(); ++i) {
			//偏移修正
			auto& modify = gridss[0][i].TopLeft();
			//数据测试
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
	//类成员函数指针类型
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//待测试的函数，他们都有一样的签名参数
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