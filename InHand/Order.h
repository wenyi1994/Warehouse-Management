#pragma once
#include "afxcmn.h"


// COrder �Ի���

class COrder : public CDialog
{
	DECLARE_DYNAMIC(COrder)

public:
	COrder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COrder();

// �Ի�������
	enum { IDD = IDD_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
