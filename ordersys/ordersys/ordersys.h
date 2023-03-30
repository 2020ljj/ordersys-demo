
// ordersys.h: ordersys 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号
#include "CPublic.h"

// CordersysApp:
// 有关此类的实现，请参阅 ordersys.cpp
//
//
class CordersysApp : public CWinApp
{
public:
	CordersysApp() noexcept;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};


extern CordersysApp theApp;