#pragma once
#include "afxcmn.h"


// CPart 对话框

class CPart : public CDialog
{
	DECLARE_DYNAMIC(CPart)

public:
	CPart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPart();

// 对话框数据
	enum { IDD = IDD_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
