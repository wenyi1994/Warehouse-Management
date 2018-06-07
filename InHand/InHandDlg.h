
// InHandDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Order.h"
#include "Part.h"
#include "AddBarCode.h"
#include "ColorStatic.h"


// CInHandDlg 对话框
class CInHandDlg : public CDialog
{
// 构造
public:
	CInHandDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INHAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	_ConnectionPtr m_pConnection; //连接，可以调用execute函数执行sql语句
	_RecordsetPtr m_pRecordset;//结果集，可以掉用open函数执行sql语句
	_RecordsetPtr m_pRecordset2;
	_CommandPtr m_pCommand; //命令对象，可以调用execute执行sql语句


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
