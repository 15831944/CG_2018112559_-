#include "pch.h"
#include "check.h"
void test2_1(CWnd* pDC)
{
	//���Ա����ָ������
	using  funcPointer = decltype(&C2018112559_Lullaby::MIDLine);
	//�����Եĺ��������Ƕ���һ����ǩ������
	vector<funcPointer> funcs =
	{ &C2018112559_Lullaby::DemoLine,&C2018112559_Lullaby::MIDLine };
	//���Զ���
	C2018112559_Lullaby obj(pDC);
	//�����ͻ�������
	CRect area;
	pDC->GetClientRect(&area);
	//�ѿͻ���ƽ�����ݣ�1 * 3
	auto ret = J::avgCRect(area, 1, 3);
	//��vector�ȽϺã���Ϊ��������Ҫ.get()��
	auto& gridss = (*ret.get());
	int dX = gridss[0][0].Width();
	int dY = gridss[0][0].Height();
	//��Ϊ��Щ�ط���Ҫƫ��һ��ģ���Ȼ��������ı�Ե�����ͽ�һ���ˣ�����ƫ����
	int offset = 10;
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
