#pragma once
#include "afxcmn.h"


// CPart �Ի���

class CPart : public CDialog
{
	DECLARE_DYNAMIC(CPart)

public:
	CPart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPart();

// �Ի�������
	enum { IDD = IDD_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
