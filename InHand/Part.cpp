// Part.cpp : 实现文件
//

#include "stdafx.h"
#include "InHand.h"
#include "Part.h"


// CPart 对话框

IMPLEMENT_DYNAMIC(CPart, CDialog)

CPart::CPart(CWnd* pParent /*=NULL*/)
	: CDialog(CPart::IDD, pParent)
{

}

CPart::~CPart()
{
}

void CPart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLIST, m_List);
}


BEGIN_MESSAGE_MAP(CPart, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPart 消息处理程序

void CPart::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if (GetDlgItem(IDC_PLIST))
	{
		GetDlgItem(IDC_PLIST)->SetWindowPos(this, 0,0,cx,cy,SWP_NOZORDER);
		m_List.SetColumnWidth(0,cx/6);
		m_List.SetColumnWidth(1,cx/6);
		m_List.SetColumnWidth(2,cx/6);
		m_List.SetColumnWidth(3,cx/6);
		m_List.SetColumnWidth(4,cx/6);
		m_List.SetColumnWidth(5,cx/6);
	}
}

BOOL CPart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	CRect   rect;        
	GetClientRect(&rect);//得到相对坐标
	GetDlgItem(IDC_PLIST)->SetWindowPos(this, 0,0,rect.Width(),rect.Height(),SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}

BOOL CPart::PreTranslateMessage(MSG* pMsg)
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
