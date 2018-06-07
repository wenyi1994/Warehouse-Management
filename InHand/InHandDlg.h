
// InHandDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Order.h"
#include "Part.h"
#include "AddBarCode.h"
#include "ColorStatic.h"


// CInHandDlg �Ի���
class CInHandDlg : public CDialog
{
// ����
public:
	CInHandDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INHAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	_ConnectionPtr m_pConnection; //���ӣ����Ե���execute����ִ��sql���
	_RecordsetPtr m_pRecordset;//����������Ե���open����ִ��sql���
	_RecordsetPtr m_pRecordset2;
	_CommandPtr m_pCommand; //������󣬿��Ե���executeִ��sql���


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	COrder m_Order;
	CPart m_Part;
	CTabCtrl m_Tab;
	bool GetPartInfo(CListCtrl & Ctrl, int Width);
	bool GetOrderInfo(CListCtrl & Ctrl, int Width);
	int GetCountRecord();
	int QueryBarCode(CString strBarCode);
	bool AddBarCode();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnBnQuery(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnSetfocusGetid();
public:
	int count_record;
	CColorStatic * m_AllPart[100];
	int ShowCount;
	int GetShowCount(int a, int b, int c);
	void RefreshVisual();
	CString m_Needed1, m_Needed2;
	int m_Number1, m_Number2;
	int ShowCount2;
	void QueryFromName(CString strNeed, int Number, int SetShowCount);
};
