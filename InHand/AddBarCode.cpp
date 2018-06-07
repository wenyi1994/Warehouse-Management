// AddBarCode.cpp : 实现文件
//

#include "stdafx.h"
#include "InHand.h"
#include "AddBarCode.h"


// CAddBarCode 对话框

IMPLEMENT_DYNAMIC(CAddBarCode, CDialog)

CAddBarCode::CAddBarCode(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBarCode::IDD, pParent)
{

}

CAddBarCode::~CAddBarCode()
{
}

void CAddBarCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PO, m_Combo_PO);
}


BEGIN_MESSAGE_MAP(CAddBarCode, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddBarCode::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_NOADD, &CAddBarCode::OnBnClickedButtonNoadd)
	ON_CBN_SELCHANGE(IDC_COMBO_PO, &CAddBarCode::OnCbnSelchangeComboPo)
END_MESSAGE_MAP()


// CAddBarCode 消息处理程序

BOOL CAddBarCode::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO

	SetWindowPos(this,400,400,600,200,SWP_NOZORDER);
	GetDlgItem(IDC_NBARCODE)->SetWindowPos(this, 20,22,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_GOTTEN_BARCODE)->SetWindowPos(this,110,20,200,20,SWP_NOZORDER);
	GetDlgItem(IDC_NCLASS)->SetWindowPos(this,340,22,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_COMBO_PO)->SetWindowPos(this,430,20,120,20,SWP_NOZORDER);

	GetDlgItem(IDC_NP1)->SetWindowPos(this,20,62,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N1)->SetWindowPos(this,110,60,200,20,SWP_NOZORDER);
	GetDlgItem(IDC_NP2)->SetWindowPos(this,340,62,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N2)->SetWindowPos(this,430,60,120,20,SWP_NOZORDER);

	GetDlgItem(IDC_NP3)->SetWindowPos(this,20,102,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N3)->SetWindowPos(this,110,100,200,20,SWP_NOZORDER);
	GetDlgItem(IDC_NP6)->SetWindowPos(this,340,102,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N6)->SetWindowPos(this,430,100,120,20,SWP_NOZORDER);

	GetDlgItem(IDC_NP4)->SetWindowText(_T("Shelve"));
	GetDlgItem(IDC_NP4)->SetWindowPos(this,20,142,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N4)->SetWindowPos(this,110,140,200,20,SWP_NOZORDER);
	GetDlgItem(IDC_NP5)->SetWindowText(_T("Storey"));
	GetDlgItem(IDC_NP5)->SetWindowPos(this,340,142,80,20,SWP_NOZORDER);
	GetDlgItem(IDC_ED_N5)->SetWindowPos(this,430,140,120,20,SWP_NOZORDER);

	GetDlgItem(IDC_BUTTON_ADD)->SetWindowPos(this,220,170,60,20,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_NOADD)->SetWindowPos(this,320,170,60,20,SWP_NOZORDER);

	m_Combo_PO.AddString(_T("Part"));
	m_Combo_PO.AddString(_T("Order"));
	m_Combo_PO.SetCurSel(1);
	CInHandApp *pApp = (CInHandApp *)AfxGetApp();
	m_SendProperty = 0;
	GetDlgItem(IDC_GOTTEN_BARCODE)->SetWindowText(pApp->m_BarCode);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CAddBarCode::OnBnClickedButtonAdd()
{
	// TODO
	CInHandApp *pApp = (CInHandApp *)AfxGetApp();
	pApp->m_AddProperty = m_SendProperty;
	GetDlgItemText(IDC_GOTTEN_BARCODE,pApp->m_BarCode);
	switch (pApp->m_AddProperty)
	{
	case 0:
		GetDlgItemText(IDC_ED_N1,pApp->m_AddName);
		GetDlgItemText(IDC_ED_N2,pApp->m_AddStock);
		GetDlgItemText(IDC_ED_N3,pApp->m_AddInOrder);
		GetDlgItemText(IDC_ED_N4,pApp->m_AddShelve);
		GetDlgItemText(IDC_ED_N5,pApp->m_AddStorey);
		GetDlgItemText(IDC_ED_N6,pApp->m_AddCount);
		break;
	case 1:
		GetDlgItemText(IDC_ED_N1,pApp->m_AddName);
		GetDlgItemText(IDC_ED_N2,pApp->m_AddNeeded1);
		GetDlgItemText(IDC_ED_N3,pApp->m_AddNumber1);
		GetDlgItemText(IDC_ED_N4,pApp->m_AddNeeded2);
		GetDlgItemText(IDC_ED_N5,pApp->m_AddNumber2);
		break;
	}
	if (pApp->m_AddName.IsEmpty() || pApp->m_AddShelve.IsEmpty() || pApp->m_AddStorey.IsEmpty() || pApp->m_AddCount.IsEmpty())
	{
		MessageBox(_T("You should give it a name and exact position! \nAdd operation canceled!"));
		OnCancel();
		return;
	}
	OnOK();
}

void CAddBarCode::OnBnClickedButtonNoadd()
{
	// TODO
	CInHandApp *pApp = (CInHandApp *)AfxGetApp();
	pApp->m_AddProperty = -1;
	OnCancel();
}

void CAddBarCode::OnCbnSelchangeComboPo()
{
	// TODO  
	int nSel;   

	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_Combo_PO.GetCurSel();   
	CString str;
	m_Combo_PO.GetLBText(nSel,str);
	if (str == (CString)_T("Part"))
	{
		m_SendProperty = 0;

		GetDlgItem(IDC_NP1)->SetWindowText(_T("Part Name"));

		GetDlgItem(IDC_NP2)->SetWindowText(_T("Number in Stock"));
		GetDlgItem(IDC_NP2)->SetWindowPos(this,340,62,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N2)->SetWindowPos(this,430,60,120,20,SWP_NOZORDER);
		GetDlgItem(IDC_NP3)->SetWindowText(_T("Number in Order"));
		GetDlgItem(IDC_NP3)->SetWindowPos(this,20,102,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N3)->SetWindowPos(this,110,100,200,20,SWP_NOZORDER);

		GetDlgItem(IDC_NP6)->SetWindowPos(this,340,102,80,20,SWP_NOZORDER|SWP_SHOWWINDOW);
		GetDlgItem(IDC_ED_N6)->SetWindowPos(this,430,100,120,20,SWP_NOZORDER|SWP_SHOWWINDOW);

		GetDlgItem(IDC_NP4)->SetWindowText(_T("Shelve"));
		GetDlgItem(IDC_NP4)->SetWindowPos(this,20,142,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N4)->SetWindowPos(this,110,140,200,20,SWP_NOZORDER);
		GetDlgItem(IDC_NP5)->SetWindowText(_T("Storey"));
		GetDlgItem(IDC_NP5)->SetWindowPos(this,340,142,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N5)->SetWindowPos(this,430,140,120,20,SWP_NOZORDER);
	}
	else
	{
		m_SendProperty = 1;

		GetDlgItem(IDC_NP1)->SetWindowText(_T("Order Name"));

		GetDlgItem(IDC_NP2)->SetWindowText(_T("Needed Part 1"));
		GetDlgItem(IDC_NP2)->SetWindowPos(this,20,102,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N2)->SetWindowPos(this,110,100,200,20,SWP_NOZORDER);
		GetDlgItem(IDC_NP3)->SetWindowText(_T("Needed Number"));
		GetDlgItem(IDC_NP3)->SetWindowPos(this,340,102,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N3)->SetWindowPos(this,430,100,120,20,SWP_NOZORDER);

		GetDlgItem(IDC_NP6)->SetWindowPos(this,340,102,80,20,SWP_NOZORDER|SWP_HIDEWINDOW);
		GetDlgItem(IDC_ED_N6)->SetWindowPos(this,430,100,120,20,SWP_NOZORDER|SWP_HIDEWINDOW);

		GetDlgItem(IDC_NP4)->SetWindowText(_T("Needed Part 2"));
		GetDlgItem(IDC_NP4)->SetWindowPos(this,20,142,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N4)->SetWindowPos(this,110,140,200,20,SWP_NOZORDER);
		GetDlgItem(IDC_NP5)->SetWindowText(_T("Needed Number"));
		GetDlgItem(IDC_NP5)->SetWindowPos(this,340,142,80,20,SWP_NOZORDER);
		GetDlgItem(IDC_ED_N5)->SetWindowPos(this,430,140,120,20,SWP_NOZORDER);
	}
}

BOOL CAddBarCode::PreTranslateMessage(MSG* pMsg)
{
	// TODO:
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE: //Esc按键事件  
			return true;  
		case VK_RETURN: //Enter按键事件
			return true;  
		default:  
			;  
		}  
	}
	return CDialog::PreTranslateMessage(pMsg);
}
