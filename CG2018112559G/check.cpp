#include "pch.h"
#include "check.h"
void test2_1(CWnd* pDC)
{
	//类成员函数指针类型
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//待测试的函数，他们都有一样的签名参数
	vector<funcPointer> funcs =
	{ &C2018112559_Lullaby::DemoLine,&C2018112559_Lullaby::MIDLine };
	//测试对象咯
	C2018112559_Lullaby obj(pDC);
	//整个客户区区域
	CRect area;
	pDC->GetClientRect(&area);
	//把客户区平分三份，1 * 3
	auto ret = J::avgCRect(area, 1, 3);
	//换vector比较好，因为操作不需要.get()啦
	auto& gridss = (*ret.get());
	int dX = gridss[0][0].Width();
	int dY = gridss[0][0].Height();
	//因为有些地方是要偏移一点的，不然相邻区域的边缘线条就接一起了，这是偏移量
	int offset = 10;
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
