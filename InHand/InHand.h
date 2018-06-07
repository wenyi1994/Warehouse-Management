
// InHand.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CInHandApp:
// 有关此类的实现，请参阅 InHand.cpp
//

class CInHandApp : public CWinAppEx
{
public:
	CInHandApp();

// 重写
	public:
	virtual BOOL InitInstance();

	CString m_BarCode;
	CString m_AddName;
	CString m_AddStock;
	CString m_AddInOrder;
	CString m_AddNeeded1;
	CString m_AddNumber1;
	CString m_AddNeeded2;
	CString m_AddNumber2;
	CString m_AddShelve;
	CString m_AddStorey;
	CString m_AddCount;
	int m_AddProperty;
	bool InitComplete;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CInHandApp theApp;