#pragma once
#include "afxwin.h"


// CAddBarCode �Ի���

class CAddBarCode : public CDialog
{
	DECLARE_DYNAMIC(CAddBarCode)

public:
	CAddBarCode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddBarCode();

// �Ի�������
	enum { IDD = IDD_ADD_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonNoadd();
	CComboBox m_Combo_PO;
	afx_msg void OnCbnSelchangeComboPo();

	int m_SendProperty;  // 0 = Part, 1 = Order
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
