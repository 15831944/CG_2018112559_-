
// CG2018112559GView.h: CCG2018112559GView 类的接口
//

#pragma once


class CCG2018112559GView : public CScrollView
{
protected: // 仅从序列化创建
	CCG2018112559GView() noexcept;
	DECLARE_DYNCREATE(CCG2018112559GView)

// 特性
public:
	CCG2018112559GDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCG2018112559GView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnJob11();
};

#ifndef _DEBUG  // CG2018112559GView.cpp 中的调试版本
inline CCG2018112559GDoc* CCG2018112559GView::GetDocument() const
   { return reinterpret_cast<CCG2018112559GDoc*>(m_pDocument); }
#endif

