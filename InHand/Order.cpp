// Order.cpp : 实现文件
//

#include "stdafx.h"
#include "InHand.h"
#include "Order.h"


// COrder 对话框

IMPLEMENT_DYNAMIC(COrder, CDialog)

COrder::COrder(CWnd* pParent /*=NULL*/)
	: CDialog(COrder::IDD, pParent)
{

}

COrder::~COrder()
{
}

void COrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OLIST, m_List);
}


BEGIN_MESSAGE_MAP(COrder, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COrder 消息处理程序

void COrder::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if (GetDlgItem(IDC_OLIST))
	{
		GetDlgItem(IDC_OLIST)->SetWindowPos(this,0,0,cx,cy,SWP_NOZORDER);
		m_List.SetColumnWidth(0,cx/5);
		m_List.SetColumnWidth(1,cx/5);
		m_List.SetColumnWidth(2,cx/5);
		m_List.SetColumnWidth(3,cx/5);
		m_List.SetColumnWidth(4,cx/5);
	}
}

BOOL COrder::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	CRect   rect;        
	GetClientRect(&rect);//得到相对坐标
	GetDlgItem(IDC_OLIST)->SetWindowPos(this, 0,0,rect.Width(),rect.Height(),SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
}

BOOL COrder::PreTranslateMessage(MSG* pMsg)
{
	// TODO

	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE: //Esc按键事件  
			return true;  
		case VK_RETURN: //Enter按键事件
			GetParent()->GetParent()->SendMessage(WM_BN_QUERY);
			return true;  
		default:  
			;  
		}  
	}
	return CDialog::PreTranslateMessage(pMsg);
}
