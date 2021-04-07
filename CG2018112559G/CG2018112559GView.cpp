
// CG2018112559GView.cpp: CCG2018112559GView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2018112559G.h"
#endif

#include "CG2018112559GDoc.h"
#include "CG2018112559GView.h"
//添加的头文件
#pragma warning(disable:26451)
#include"Jalgo.h"
#include"Jhead.h"
#include"pack.h"
#include"threadManage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG2018112559GView

IMPLEMENT_DYNCREATE(CCG2018112559GView, CScrollView)

BEGIN_MESSAGE_MAP(CCG2018112559GView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_JOB_1_1, &CCG2018112559GView::OnJob11)
	ON_COMMAND(ID_JOB_1_2, &CCG2018112559GView::OnJob12)
	ON_COMMAND(ID_Menu_Job_2_1, &CCG2018112559GView::OnMenuJob21)
	//ON_COMMAND(ID_J_2_2, &CCG2018112559GView::OnJ22)
	//ON_COMMAND(ID_J_2_3, &CCG2018112559GView::OnJ23)
	//ON_COMMAND(ID_J_2_4, &CCG2018112559GView::OnJ24)
	ON_COMMAND(ID_J_2_1_1, &CCG2018112559GView::OnJ211)
	ON_COMMAND(ID_J_2_1_2, &CCG2018112559GView::OnJ212)
	ON_COMMAND(ID_J_2_1_3, &CCG2018112559GView::OnJ213)
	ON_COMMAND(ID_J_2_2_1, &CCG2018112559GView::OnJ221)
	ON_COMMAND(ID_J221T, &CCG2018112559GView::OnJ221t)
	ON_COMMAND(ID_J221A, &CCG2018112559GView::OnJ221a)
	ON_COMMAND(ID_J221B, &CCG2018112559GView::OnJ221b)
	ON_COMMAND(ID_J221C, &CCG2018112559GView::OnJ221c)
	ON_COMMAND(ID_J221Z, &CCG2018112559GView::OnJ221z)
	ON_COMMAND(ID_J221d, &CCG2018112559GView::OnJ221d)
	ON_COMMAND(ID_J221E, &CCG2018112559GView::OnJ221e)
	ON_COMMAND(ID_J23a, &CCG2018112559GView::OnJ23a)
	ON_COMMAND(ID_J23b, &CCG2018112559GView::OnJ23b)
END_MESSAGE_MAP()

// CCG2018112559GView 构造/析构

void CCG2018112559GView::MFCcls()
{
	CDC* pDC = GetDC();
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));
	ReleaseDC(pDC);
}

CCG2018112559GView::CCG2018112559GView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2018112559GView::~CCG2018112559GView()
{
	//等待子线程退出
	tm.JoinAllThreads();
}

BOOL CCG2018112559GView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CCG2018112559GView 绘图

void CCG2018112559GView::OnDraw(CDC* pDC)
{
	CCG2018112559GDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}

void CCG2018112559GView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CCG2018112559GView 打印

BOOL CCG2018112559GView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCG2018112559GView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCG2018112559GView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCG2018112559GView 诊断

#ifdef _DEBUG
void CCG2018112559GView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCG2018112559GView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCG2018112559GDoc* CCG2018112559GView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2018112559GDoc)));
	return (CCG2018112559GDoc*)m_pDocument;
}
#endif //_DEBUG


// CCG2018112559GView 消息处理程序


void CCG2018112559GView::OnJob11()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = AfxGetMainWnd()->GetDC();
	CRect CR; GetClientRect(&CR);
	const int& width = CR.Width(), & height = CR.Height();
	const int marginBlank = 10, FontOffset = 3;
	//行分割线
	for (int i = 0; i < 4; ++i)
		DrawLine(pDC, RGB(50, 230, 210), RGB(0, 0, 0),
			pii(marginBlank, i * height / 3),
			pii(width - marginBlank, i * height / 3));
	//列分割线
	for (int i = 0; i < 5; ++i)
		DrawLine(pDC, RGB(50, 230, 210), RGB(0, 0, 0),
			pii(i * width / 4, marginBlank),
			pii(i * width / 4, height - marginBlank));
	pDC->TextOutW(FontOffset, FontOffset, CString("直线"));
	for (int i = 0; i < 10; ++i)DrawLine(pDC, RGB(50, 230, 210), RGB(0, 0, 0),
		pii(marginBlank, 25 + height * i / 30),
		pii(width / 4, 25 + height * i / 30));
	pDC->TextOutW(FontOffset + width / 4, FontOffset, CString("圆"));
	const int radius = min(width / 4, height / 3) / 2,
		cx = 3 * width / 8, cy = height / 6;
	for (int count = 5, i = count; i >= 1; --i)
		pDC->Ellipse(cx - radius * i / count, cy - radius * i / count,
			cx + radius * i / 6, cy + radius * i / 6);
	pDC->TextOutW(FontOffset + width / 2, FontOffset, CString("椭圆"));
	for (int i = 0; i < 5; ++i)
		pDC->Ellipse(CRect(CPoint(width / 2 + (width / 4) * i / 5, height / 6 * i / 5),
			CPoint(width * 3 / 4 - (width / 4) * i / 5, height / 3 - height / 6 * i / 5)));
	pDC->TextOutW(FontOffset + width * 3 / 4, FontOffset, CString("矩形"));
	for (int count = 5, i = count; i >= 1; --i)
#define dif(xl,xr,i,all)  (xl*i/all+xr*(all-i)/all)
		pDC->Rectangle(dif(width * 3 / 4, width * 7 / 8, i, count), dif(0, height / 6, i, count),
			dif(width, width * 7 / 8, i, count), dif(height / 3, height / 6, i, count));
#undef dif
	pDC->TextOutW(FontOffset, FontOffset + height / 3, CString("多边形"));
	const int pParam = 9;//可调参数
	std::vector<CPoint> PV;//先零分配，后边push，就可以避过计数
	//填充点集
	const CPoint PolyCentre(width / 8, height / 2);//多边形中心
	const int pxr = width / 8, pyr = height / 6;
	for (int i = 0; i < pParam; ++i)
		PV.emplace_back(PolyCentre.x + pxr * cos(1.0 * i / pParam * 360),
			PolyCentre.y + pyr * sin(1.0 * i / pParam * 360));
	pDC->Polygon(&PV[0], pParam);
	pDC->TextOutW(FontOffset + width / 4, FontOffset + height / 3, CString("折线"));
	//四边形内折
	const int plParam = 40;//可变参数
	std::deque<CPoint> deq = { {width / 4,height / 3},{width / 2,height / 3},
		{width / 2,height * 2 / 3 },{width / 4,height * 2 / 3} };//某时的四个点
	std::vector<CPoint> polyDrawLP = { deq.back() };//初始化为deq的末尾元素
	CPoint plCurPos(width / 2, height / 2);
	for (int i = 0; i < plParam; ++i)
	{
		auto fir = deq.front();
		deq.pop_front();
		auto sec = deq.front();
		polyDrawLP.emplace_back((fir.x + sec.x) / 2, (fir.y + sec.y) / 2);
		deq.emplace_back(polyDrawLP.back());
	}
	//std::unique_ptr<DWORD *>lpPolyPoint(new DWORD[1])
	DWORD lpPolyPoint = plParam + 1;
	pDC->PolyPolyline(&polyDrawLP[0], &lpPolyPoint, 1);
	pDC->TextOutW(width / 2 + FontOffset, FontOffset + height / 3, CString("曲线"));
	pDC->Arc(17 * width / 32, height * 11 / 24, 19 * width / 32, height * 13 / 24,
		width / 2, height / 2, width * 3 / 4, height * 3 / 4);
	pDC->Arc(21 * width / 32, height * 11 / 24, 23 * width / 32, height * 13 / 24,
		width / 2, height / 2, width * 3 / 4, height * 3 / 4);
	pDC->Arc(17 * width / 32, height * 11 / 24, 19 * width / 32, height * 13 / 24,
		width / 2, height / 2, width * 3 / 4, height * 3 / 4);

	pDC->TextOutW(width * 3 / 4 + FontOffset, FontOffset + height / 3, CString("圆弧"));
	pDC->Arc(24 * width / 32, height * 8 / 24, 24 * width / 32 + 200, height * 8 / 24 + 200,
		width / 2, height / 2, width * 3 / 4, height * 3 / 4);
	pDC->TextOutW(FontOffset, FontOffset + height * 2 / 3, CString("椭圆弧"));
	pDC->Arc(0, height * 2 / 3, width / 4, height,
		width / 2, height / 2, width * 3 / 4, height * 3 / 4);
	pDC->TextOutW(FontOffset + width / 4, FontOffset + height * 2 / 3, CString("弦"));
	pDC->Ellipse(width / 4, height * 2 / 3, width / 4 + 200, height * 2 / 3 + 200);
	for (int cnt = 7, i = 0; i < cnt; ++i)
		DrawLine(pDC, RGB(0, 0, 255), RGB(255, 0, 0),
			pii(width / 4.0 + 100 + 100 * cos(i * 360.0 / cnt), height * 2 / 3 + 100 + (sin(i * 360.0 / cnt))),
			pii(width / 4.0 + 100 + 100 * cos((i + 3) * 360.0 / cnt), height * 2 / 3 + 100 + (sin((3 + i) * 360.0 / cnt))));

	pDC->TextOutW(FontOffset + width * 2 / 4, FontOffset + height * 2 / 3, CString("填充"));
	CBrush nBrush;
	nBrush.CreateSolidBrush(RGB(0, 255, 0));
	pDC->Ellipse(width / 2 + 50, height * 2 / 3 + 50, width / 2 + 250, height * 2 / 3 + 250);
	CRgn zoneToFill;
	zoneToFill.CreateEllipticRgn(width / 2 + 50, height * 2 / 3 + 50,
		width / 2 + 250, height * 2 / 3 + 250);
	pDC->FillRgn(&zoneToFill, &nBrush);
	pDC->TextOutW(FontOffset + width * 3 / 4, FontOffset + height * 2 / 3, CString("文字"));
	pDC->ExtTextOutW(width * 3 / 4 + 50, height * 2 / 3 + 50, NULL,
		&CRect(width * 3 / 4 + 50, height * 2 / 3 + 50, width - 50, height - 50),
		CString(CString("这一段文字需在一个矩形框内显示，**此为换行**\nthere is more")
			//+([]()->CString {CString ret; for (int i = 0; i < 100; ++i)ret += L'a'; })()
		), NULL);
}


void CCG2018112559GView::OnJob12()
{
	CDC* const pDC = AfxGetMainWnd()->GetDC();
	CRect curArea;
	GetClientRect(&curArea);
	// 五角星
	J::DrawFivePointStar(CRect(curArea.left, curArea.top, (2 * curArea.left + curArea.right) / 3,
		(curArea.top + 3 * curArea.bottom) / 4), pDC, 5, 115);
	//太极图

	J::DrawTaiChiCircle(CRect((2 * curArea.left + curArea.right) / 3, curArea.top,
		(curArea.left + 2 * curArea.right) / 3, (curArea.top + 3 * curArea.bottom) / 4),
		pDC, 90);
	J::DrawRandomLineAndPrintOverhead(
		CRect((curArea.left + 2 * curArea.right) / 3, curArea.top,
			curArea.right, (curArea.top + 3 * curArea.bottom) / 4),
		pDC, { 100u,1000u,10000u,100000u }
	);
	//pDC->BeginPath();
	//pDC->MoveTo(800, 300);
	//pDC->AngleArc(300, 300, 500, 30, 270);
	//pDC->LineTo(800, 300);
	//pDC->EndPath();
	//CBrush cb; cb.CreateSolidBrush(RGB(0, 255, 0));
	//CRgn crgn;
	//crgn.CreateFromPath(pDC);
	//pDC->InvertRgn(&crgn);
	//pDC->FillRgn(&crgn, &cb);
}



//#include<utility>
//void targetF(int i, char c, char co, float f) {};
//template<decltype(&targetF), class ...Paras>
//struct tF {
//	void operator()(Paras ...para) {
//		(*targetF)(para...);
//	}
//};
//void test_test() {
//	using tPara = tuple<CPoint, CPoint, COLORREF>;
//	tPara testExample({ 1,1 }, { 300,500 }, RGB(0, 0, 0));
//	C2018112559_Lullaby lull_ins(AfxGetMainWnd());
//	auto fp = &C2018112559_Lullaby::MIDLine;
//	///test<C2018112559_Lullaby, decltype(fp), decltype(testExample)> test_ins;
//	//基类型
//	tF<(&targetF), int, char, char, float> tfins;
//	tfins(1, 1, 1, 1.0f);
//	//基模板
//	test< C2018112559_Lullaby, decltype(&C2018112559_Lullaby::MIDLine),
//		const  CPoint&,const  CPoint&, COLORREF> test0;
//    test0(lull_ins, &C2018112559_Lullaby::MIDLine,
//		CPoint(1, 1), CPoint(200, 200), COLORREF(RGB(0, 0, 0)));
//	//单参tuple模板
//	test<Tuple_exist, C2018112559_Lullaby, decltype(&C2018112559_Lullaby::MIDLine),
//		tuple<const CPoint&>, const CPoint&, COLORREF> test1;
//	test1(lull_ins, &C2018112559_Lullaby::MIDLine,
//		/*tuple<const CPoint&>*/(CPoint(200, 200)), CPoint(400, 200), COLORREF(RGB(0, 0, 0)));
//	tuple<int, int>;
//	//paraPack<int, int, char>::Paras;
//	auto p=[]() {};
//}
//template<class ToType,class FromType>
//void GetMemberFuncAddr_VC6(ToType& addr, FromType f)
//{
//	union
//	{
//		FromType _f;
//		ToType   _t;
//	}ut;
//	ut._f = f;
//	addr = ut._t;
//}
//using fpt = decltype(&C2018112559_Lullaby::MIDLine);
//using noThisFPT = void  (Class_func_Call *)(void*, const CPoint& start, const CPoint& end,
//	COLORREF pen);

void CCG2018112559GView::OnMenuJob21()
{
	MFCcls();
	test2_1(this);

	//C2018112559_Lullaby lull(this);
	//lull.MIDLineInBaseY({ 200,200 }, {300,500 },RGB(0,0,0));
	//auto pDC = AfxGetMainWnd()->GetDC();
	//auto oldPen = pDC->SelectObject(noDelete(CPen, (1, 1, RGB(255, 0, 0))));
	//pDC->MoveTo(200, 200);
	//pDC->LineTo(300, 300);
	//auto newPen = pDC->SelectObject(oldPen);
	////test2_1(AfxGetMainWnd());
	//void* p;
	//fpt fp = &C2018112559_Lullaby::MIDLine;
	//GetMemberFuncAddr_VC6<void*, fpt>(p, fp);
	//noThisFPT nfp;
	//GetMemberFuncAddr_VC6<noThisFPT, void*>(nfp, p);
	//C2018112559_Lullaby lull(AfxGetMainWnd());
	//const CPoint l(1, 1), r(800, 400);
	//COLORREF col = RGB(0, 0, 0);
	//lull.MIDLine(l,r,col);
	//(*nfp)(dynamic_cast<void*>( &lull),l,r,col);
	////using derPack = derTuple<int, char, float>;
	////using pack = tuple<int, char, float>;
	////derPack x(1, char(57), 1.0);
	////pack px = x;
	////DTRACE(d,px._Myfirst._Val);
	////DTRACE(c, px._Get_rest()._Myfirst._Val);
	////DTRACE(f, px._Get_rest()._Get_rest()._Myfirst._Val);
	////tuple_element<0, pack>::type;
	////tuple_element<0, derPack::base>::type;
	////tuple_element_t<0, pack>;
	//noThisFPT CFmidLine=nullptr;
	//CMF2CF<C2018112559_Lullaby, void, const CPoint&, const CPoint&,
	//	COLORREF>(&C2018112559_Lullaby::MIDLine, CFmidLine);
	//(*CFmidLine)(dynamic_cast<void*>(&lull), { 200,200 }, { 600,200 }, RGB(0, 0, 0));
	//test_test();
}


void CCG2018112559GView::OnJ211()
{
	MFCcls();
	test2_1(this);
	// TODO: 在此添加命令处理程序代码
}


void CCG2018112559GView::OnJ212()
{
	MFCcls();
	test_2_1_efficiency(this);
	// TODO: 在此添加命令处理程序代码
}


void CCG2018112559GView::OnJ213()
{
	MFCcls();
	test_2_1_efficiency_directive_msvcCall(this);
}


void CCG2018112559GView::OnJ221()
{
	MFCcls();

	// TODO: 在此添加命令处理程序代码
}


void CCG2018112559GView::OnJ221t()
{
	//2.2.1 圆算法 对比测试
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.MidCircle({ 500,500 }, 100);
	lull.MidCircleArc({ 500,500 }, 200, 1, 2);
	lull.MidCircleArc({ 500,500 }, 200, 3, 4);
	lull.MidCircleArc({ 500,500 }, 200, 5, 6);
	lull.BreshenhamCircle({ 500,500 }, 300);
	lull.MidEllipsolid({ 100,100,500,300 });
	lull.MidEllipsolidArc({ 0,0,500,300 }, 1, 2);
	lull.MidEllipsolidArc({ 0,0,500,300 }, 3, 4);
	lull.MidEllipsolidArc({ 0,0,500,300 }, 5, 6);
}



void CCG2018112559GView::OnJ221a()
{
	//2.2.1 圆算法 中点画圆
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.MidCircle({ 300,300 }, 200);
}


void CCG2018112559GView::OnJ221b()
{
	//2.2.1 圆算法 breshenham画圆
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.BreshenhamCircle({ 300,300 }, 200);

}


void CCG2018112559GView::OnJ221c()
{
	//2.2.1 圆算法 中点椭圆
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.MidEllipsolid(CRect(100, 100, 500, 300));
	lull.Ellipse(CRect{ 0,0,1,1 });
}



void CCG2018112559GView::OnJ221d()
{
	//2.2.1 圆算法 中点圆弧
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.MidCircleArc({ 500,500 }, 400, 0, 5);
}


void CCG2018112559GView::OnJ221e()
{
	//2.2.1 圆算法 中点椭圆弧
	MFCcls();
	C2018112559_Lullaby lull(this);
	lull.MidEllipsolidArc({ 100,100,500,300 }, 0, 9);
}

void CCG2018112559GView::OnJ221z()
{
	//2.2.1 圆算法 同屏参数测试
	MFCcls();
}


void CCG2018112559GView::OnJ23a()
{
	//线型算法 基本展示
	MFCcls();
	C2018112559_Lullaby lull(this);
	vector<C2018112559_Lullaby::LineFormat> lineF = {
		C2018112559_Lullaby::LineFormatSimple("1000000000000", 4).getLineFormat() ,
		C2018112559_Lullaby::LineFormatSimple("1100000000000", 4).getLineFormat(),
		C2018112559_Lullaby::LineFormatSimple("1110000000000", 4).getLineFormat(),
		C2018112559_Lullaby::LineFormatSimple("100100100100", 4).getLineFormat(),
		C2018112559_Lullaby::LineFormatSimple("100011001110", 4).getLineFormat(),
		C2018112559_Lullaby::LineFormatSimple("1111000010000", 4).getLineFormat()
	};

	lull.MidLineWithLineFormat({ 100,100 }, { 400,400 }, 0, lineF[0]);
	lull.MidLineWithLineFormat({ 100,200 }, { 400,500 }, 0, lineF[1]);
	lull.MidLineWithLineFormat({ 100,300 }, { 400,600 }, 0, lineF[2]);
	lull.MidLineWithLineFormat({ 100,400 }, { 400,700 }, 0, lineF[3]);
	lull.MidLineWithLineFormat({ 100,500 }, { 400,800 }, 0, lineF[4]);
	lull.MidLineWithLineFormat({ 100,600 }, { 400,900 }, 0, lineF[5]);
	vector<std::string> f = {
		"111111111111111111111111111111111111111111111",
		"100000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"100000000011000000000000000001100000000000001",
		"100000001100110000000000000110011000000000001",
		"100000011000011000000000001100001100000000001",
		"100001100000000110000000110000000011000000001",
		"100110000000000001100011000000000000110000001",
		"100000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"100000000000110000000000001100000000000000001",
		"100000000000001100000000110000000000000000001",
		"100000000000000011000011000000000000000000001",
		"100000000000000000111100000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000001",
		"111111111111111111111111111111111111111111111"
	};
	for (int i = 0; i < f.size() / 2; ++i)swap(f[i], f[f.size() - i - 1]);
	C2018112559_Lullaby::LineFormat awesomeLineF(f);
	lull.MidLineWithLineFormat({ 500,500 }, {1800,200 },0, awesomeLineF);
}

 static atomic<int> ai=0;
void CCG2018112559GView::OnJ23b()
{
	// 线型算法 输入窗格 

	auto lamp = [](atomic<int>*pai) {
		long p =long( pai);
		ASSERT(long(pai) != NULL);
		ASSERT(long(pai) != -858993460);//栈raw value
		DlgDynamicInputNeeds ddin;
		ddin.DoModal();
		pai->store(0); 
	};
	
	if(tm.countExist(__func__)==0) 
		tm.addThread<decltype(lamp),void,atomic<int>*>(__func__,lamp,&ai);

	return;
}
