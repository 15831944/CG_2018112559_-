
// CG2018112559GView.h: CCG2018112559GView 类的接口
//

#pragma once

//添加的头
#include"C2018112559_Lullaby.h"
#include"threadManage.h"
class CCG2018112559GView : public CScrollView
{
private:
	void MFCcls();

protected: // 仅从序列化创建
	CCG2018112559GView() noexcept;
	DECLARE_DYNCREATE(CCG2018112559GView)

// 特性
public:
	CCG2018112559GDoc* GetDocument() const;

//属性
	threadManage tm;
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
	afx_msg void OnJob12();
	//afx_msg void On_Menu_Job_2_1();
	afx_msg void OnMenuJob21();
	//afx_msg void OnJ22();
	//afx_msg void OnJ23();
	//afx_msg void OnJ24();
	afx_msg void OnJ211();
	afx_msg void OnJ212();
	afx_msg void OnJ213();
	afx_msg void OnJ221();
	afx_msg void OnJ221t();
	afx_msg void OnJ221a();
	afx_msg void OnJ221b();
	afx_msg void OnJ221c();
	afx_msg void OnJ221z();
	afx_msg void OnJ221d();
	afx_msg void OnJ221e();
	afx_msg void OnJ23a();
	afx_msg void OnJ23b();
};

#ifndef _DEBUG  // CG2018112559GView.cpp 中的调试版本
inline CCG2018112559GDoc* CCG2018112559GView::GetDocument() const
   { return reinterpret_cast<CCG2018112559GDoc*>(m_pDocument); }
#endif

