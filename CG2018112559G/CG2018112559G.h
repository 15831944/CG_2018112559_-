﻿
// CG2018112559G.h: CG2018112559G 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CCG2018112559GApp:
// 有关此类的实现，请参阅 CG2018112559G.cpp
//

class CCG2018112559GApp : public CWinApp
{
public:
	CCG2018112559GApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCG2018112559GApp theApp;
