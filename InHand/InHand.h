
// InHand.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInHandApp:
// �йش����ʵ�֣������ InHand.cpp
//

class CInHandApp : public CWinAppEx
{
public:
	CInHandApp();

// ��д
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

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CInHandApp theApp;