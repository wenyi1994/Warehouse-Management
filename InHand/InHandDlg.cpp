
// InHandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "InHand.h"
#include "InHandDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CInHandDlg 对话框




CInHandDlg::CInHandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInHandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInHandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CInHandDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_BN_QUERY,OnBnQuery)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_QUERY, &CInHandDlg::OnBnClickedQuery)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CInHandDlg::OnTcnSelchangeTab)
	ON_EN_SETFOCUS(IDC_GETID, &CInHandDlg::OnEnSetfocusGetid)
END_MESSAGE_MAP()


// CInHandDlg 消息处理程序

BOOL CInHandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	ShowCount = -1;
	ShowCount2 = -1;
	m_Number1 = -1;
	m_Number2 = -1;
	m_Needed1 = _T("");
	m_Needed2 = _T("");

	// init position of controls
	SetWindowPos(GetDlgItem(IDD_INHAND_DIALOG), NULL,NULL,1200,800,SWP_NOMOVE|SWP_NOZORDER);
	CRect   rect;        
	GetClientRect(&rect);//得到相对坐标
	m_Tab.InsertItem(0,_T("Part"));
	m_Tab.InsertItem(1,_T("Order"));
	m_Part.Create(IDD_PART,&m_Tab);
	m_Order.Create(IDD_ORDER,&m_Tab);

	GetDlgItem(IDC_TAB)->SetWindowPos(this, 30, 100, rect.Width()-660, rect.Height()-160, SWP_NOZORDER);
	GetDlgItem(IDC_OUTPUT)->SetWindowPos(this,400,30,rect.Width()-434,60,SWP_NOZORDER);
	// shelves
	GetDlgItem(IDC_SH1)->SetWindowPos(this,rect.Width()-620,120,300,300,SWP_NOZORDER);
	GetDlgItem(IDC_SH2)->SetWindowPos(this,rect.Width()-310,120,300,300,SWP_NOZORDER);
	GetDlgItem(IDC_SH3)->SetWindowPos(this,rect.Width()-620,(rect.Height()+80)/2,300,300,SWP_NOZORDER);
	GetDlgItem(IDC_SH4)->SetWindowPos(this,rect.Width()-310,(rect.Height()+80)/2,300,300,SWP_NOZORDER);
	
	m_Tab.GetClientRect(&rect);
	rect.left += 10;                  
	rect.right -= 10;   
	rect.top += 30;   
	rect.bottom -= 10;
	m_Part.SetWindowPos(NULL,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
	m_Order.SetWindowPos(NULL,rect.left,rect.top,rect.Width(),rect.Height(),SWP_HIDEWINDOW);
	GetDlgItem(IDC_GETID)->SetWindowPos(this,80,50,200,20,SWP_NOZORDER);
	GetDlgItem(IDC_NAME_ID)->SetWindowPos(this,30,52,50,20,SWP_NOZORDER);
	GetDlgItem(IDC_QUERY)->SetWindowPos(this,300,50,60,20,SWP_NOZORDER);

	/////////////////////////////////////////////////////////////////



	CInHandApp *pApp = (CInHandApp *)AfxGetApp();
	pApp->InitComplete = true;
	

	try
	{
		HRESULT hr =m_pConnection.CreateInstance("ADODB.Connection");//创建Connection对象
		if(SUCCEEDED(hr))
		{
			hr =m_pConnection->Open("Provider = Microsoft.Jet.OLEDB.4.0; Data Source =testDB.mdb","","",adModeUnknown);//连接数据库
		}
	}
	catch(_com_error e)//捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败！\r\n错误信息：%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);//显示错误信息
	}

	count_record = GetCountRecord();
	// count_record = 3;
	// m_AllPart = new CColorStatic[count_record];


	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open("SELECT * FROM Part",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return FALSE;
		}
		int a,b,c;
		int i = 0;
		while(!m_pRecordset->adoEOF)
		{
			m_AllPart[i] = new CColorStatic;
			m_AllPart[i]->Create(NULL,WS_CHILD|WS_VISIBLE, CRect(0,0,200,200),this);
			m_AllPart[i]->ChangeBkColor(RGB(0,0,255));
			var = m_pRecordset->GetCollect("Shelve");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				a = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Storey");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				b = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Count");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				c = _ttoi(str);
			}
			m_AllPart[i]->SetPosData(a,b,c);
			m_AllPart[i]->SetBlockPos(3,4);
			i++;
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;

	GetPartInfo(m_Part.m_List,rect.Width());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CInHandDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInHandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInHandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CInHandDlg::OnBnQuery(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedQuery();
	return 0;
}
void CInHandDlg::OnBnClickedQuery()
{
	m_Number1 = -1;
	m_Number2 = -1;
	for(int i=0; i<count_record; i++)
	{
		m_AllPart[i]->ChangeBkColor(RGB(0,0,255));
		m_AllPart[i]->SetWindowText(_T(""));
	}
	CString strBarCode;
	GetDlgItemText(IDC_GETID,strBarCode);
	if (QueryBarCode(strBarCode) == 0)
	{
		CInHandApp *pApp = (CInHandApp *)AfxGetApp();
		pApp->m_BarCode = strBarCode;
		INT_PTR nRes;
		CAddBarCode m_AddBarCode;
		nRes = m_AddBarCode.DoModal();
		if (IDOK == nRes)
		{
			AddBarCode();
		}
	}
	OnEnSetfocusGetid();
}

void CInHandDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_TAB))
	{
		GetDlgItem(IDC_TAB)->SetWindowPos(this, 30, 100, cx-660, cy-160, SWP_NOZORDER);
		CRect tabRect;
		m_Tab.GetClientRect(&tabRect);   
		tabRect.left += 10;   
		tabRect.right -= 10;   
		tabRect.top += 30;   
		tabRect.bottom -= 10;
		if (m_Part.GetSafeHwnd())
		{
			m_Part.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_NOZORDER);
		}
		if (m_Order.GetSafeHwnd())
		{
			m_Order.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_NOZORDER);
		}
	}
	if (GetDlgItem(IDC_OUTPUT))
	{
		GetDlgItem(IDC_OUTPUT)->SetWindowPos(this,400,30,cx-434,60,SWP_NOZORDER);
	}
	if(GetDlgItem(IDC_SH1)) GetDlgItem(IDC_SH1)->SetWindowPos(this,cx-620,120,300,300,SWP_NOZORDER);
	if(GetDlgItem(IDC_SH2)) GetDlgItem(IDC_SH2)->SetWindowPos(this,cx-310,120,300,300,SWP_NOZORDER);
	if(GetDlgItem(IDC_SH3)) GetDlgItem(IDC_SH3)->SetWindowPos(this,cx-620,(cy+80)/2,300,300,SWP_NOZORDER);
	if(GetDlgItem(IDC_SH4)) GetDlgItem(IDC_SH4)->SetWindowPos(this,cx-310,(cy+80)/2,300,300,SWP_NOZORDER);

	CInHandApp *pApp = (CInHandApp *)AfxGetApp();
	if (pApp->InitComplete)
	{
		for (int i = 0; i<count_record; i++)
		{
			m_AllPart[i]->SetBlockPos(3,4);
		}
	}
}

void CInHandDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;    // 标签控件客户区的Rect   

	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
	m_Tab.GetClientRect(&tabRect);   
	tabRect.left += 10;   
	tabRect.right -= 10;   
	tabRect.top += 30;   
	tabRect.bottom -= 10;   

	switch (m_Tab.GetCurSel())   
	{
	case 0:   
		m_Part.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// GetDlgItem(IDC_PLIST)->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_NOZORDER);
		m_Order.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		GetPartInfo(m_Part.m_List,tabRect.Width());
		break;   
	case 1:   
		m_Part.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
		m_Order.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		GetOrderInfo(m_Order.m_List,tabRect.Width());
		break;   
	default:   
		break;   
	}   
}

bool CInHandDlg::GetPartInfo(CListCtrl & Ctrl, int Width)
{
	Ctrl.DeleteAllItems();
	Ctrl.DeleteColumn(5);
	Ctrl.DeleteColumn(4);
	Ctrl.DeleteColumn(3);
	Ctrl.DeleteColumn(2);
	Ctrl.DeleteColumn(1);
	Ctrl.DeleteColumn(0);
	Ctrl.InsertColumn(0,_T("Part Name"),LVCFMT_CENTER, Width/6, 0);
	Ctrl.InsertColumn(1,_T("Number of Stock"),LVCFMT_CENTER, Width/6, 0);
	Ctrl.InsertColumn(2,_T("In Order"),LVCFMT_CENTER, Width/6, 0);
	Ctrl.InsertColumn(3,_T("Shelve"),LVCFMT_CENTER, Width/6, 0);
	Ctrl.InsertColumn(4,_T("Storey"),LVCFMT_CENTER, Width/6, 0);
	Ctrl.InsertColumn(5,_T("Count"),LVCFMT_CENTER, Width/6, 0);
	// open table
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open("SELECT * FROM Part",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return FALSE;
		}
		int row = 0;
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("PartName");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.InsertItem(row, str);
			}
			var = m_pRecordset->GetCollect("Stock");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 1, str); 
			}
			var = m_pRecordset->GetCollect("InOrder");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 2, str); 
			}
			var = m_pRecordset->GetCollect("Shelve");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 3, str); 
			}
			var = m_pRecordset->GetCollect("Storey");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 4, str); 
			}
			var = m_pRecordset->GetCollect("Count");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 5, str); 
			}
			row++;
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
	return TRUE;
}

bool CInHandDlg::GetOrderInfo(CListCtrl & Ctrl, int Width)
{
	Ctrl.DeleteAllItems();
	Ctrl.DeleteColumn(4);
	Ctrl.DeleteColumn(3);
	Ctrl.DeleteColumn(2);
	Ctrl.DeleteColumn(1);
	Ctrl.DeleteColumn(0);
	Ctrl.InsertColumn(0,_T("Name of Order"),LVCFMT_CENTER, Width/5, 0);
	Ctrl.InsertColumn(1,_T("Needed Part 1"),LVCFMT_CENTER, Width/5, 0);
	Ctrl.InsertColumn(2,_T("Number of Part-1"),LVCFMT_CENTER, Width/5, 0);
	Ctrl.InsertColumn(3,_T("Needed Part 2"),LVCFMT_CENTER, Width/5, 0);
	Ctrl.InsertColumn(4,_T("Number of Part2"),LVCFMT_CENTER, Width/5, 0);
	// open table
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open("SELECT * FROM [Order]",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return FALSE;
		}
		int row = 0;
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("OrderName");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.InsertItem(row, str);
			}
			var = m_pRecordset->GetCollect("Needed1");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 1, str); 
			}
			var = m_pRecordset->GetCollect("Number1");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 2, str); 
			}
			var = m_pRecordset->GetCollect("Needed2");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 3, str); 
			}
			var = m_pRecordset->GetCollect("Number2");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				Ctrl.SetItemText(row, 4, str); 
			}
			row++;
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
	return TRUE;
}
BOOL CInHandDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO

	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE: //Esc按键事件  
			return true;  
		case VK_RETURN: //Enter按键事件
			OnBnClickedQuery();
			return true;  
		default:  
			;  
		}  
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CInHandDlg::OnEnSetfocusGetid()
{
	// TODO
	
	GetDlgItem(IDC_GETID)->PostMessage(EM_SETSEL,0,-1);

}

int CInHandDlg::QueryBarCode(CString strBarCode)
{
	// open table
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	CString strSQL;
	strSQL.Format(_T("SELECT Property FROM [Index] WHERE BarCode='%s'"),strBarCode);
	// MessageBox(strSQL);
	try
	{
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str,strOutput;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			// AfxMessageBox(_T("表内数据为空"));
			return 0;
		}
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("Property");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				if (str == _T("Part"))
				{
					strSQL.Format(_T("SELECT * FROM Part WHERE BarCode='%s'"),strBarCode);
					try
					{
						m_pRecordset2.CreateInstance(__uuidof(Recordset));
						m_pRecordset2->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
					}
					catch(_com_error *e2)
					{
						AfxMessageBox(e2->ErrorMessage());
					}////
					// read data
					_variant_t var2;
					CString str2;
					int a,b,c;
					try
					{
						if(!m_pRecordset2->BOF)
							m_pRecordset2->MoveFirst();
						else
						{
							AfxMessageBox(_T("表内数据为空"));
							return -1;
						}
						while(!m_pRecordset2->adoEOF)
						{
							var2 = m_pRecordset2->GetCollect("PartName");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								strOutput.Format(_T("Part Name: %s, "), str2);
							}
							var2 = m_pRecordset2->GetCollect("Shelve");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								a = _ttoi(str2);
								strOutput.Format(_T("%sShelve: %s, "), strOutput,str2);
							}
							var2 = m_pRecordset2->GetCollect("Storey");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								b = _ttoi(str2);
								strOutput.Format(_T("%sStorey: %s, "), strOutput,str2);
							}
							var2 = m_pRecordset2->GetCollect("Count");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								c = _ttoi(str2);
								strOutput.Format(_T("%sCount: %s \r\n"), strOutput,str2);
							}
							var2 = m_pRecordset2->GetCollect("Stock");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								strOutput.Format(_T("%sPart in Stock: %s \r\n"), strOutput, str2);
							}
							var2 = m_pRecordset2->GetCollect("InOrder");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								strOutput.Format(_T("%sPart in Order: %s"), strOutput, str2);
							}
							m_pRecordset2->MoveNext();
							ShowCount = GetShowCount(a,b,c);
							m_AllPart[ShowCount]->ChangeBkColor(RGB(0,255,0));
						}
					}
					catch(_com_error *e2)
					{
						AfxMessageBox(e2->ErrorMessage());
					}
					m_pRecordset2->Close();
					m_pRecordset2 = NULL;
				} 
				else
				{
					strSQL.Format(_T("SELECT * FROM [Order] WHERE BarCode='%s'"),strBarCode);
					try
					{
						m_pRecordset2.CreateInstance(__uuidof(Recordset));
						m_pRecordset2->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
					}
					catch(_com_error *e)
					{
						AfxMessageBox(e->ErrorMessage());
					}////
					// read data
					_variant_t var2;
					CString str2;
					try
					{
						if(!m_pRecordset2->BOF)
							m_pRecordset2->MoveFirst();
						else
						{
							AfxMessageBox(_T("表内数据为空"));
							return -1;
						}
						while(!m_pRecordset2->adoEOF)
						{
							var2 = m_pRecordset2->GetCollect("OrderName");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								strOutput.Format(_T("Order Name: %s \r\n"), str2);
							}
							var2 = m_pRecordset2->GetCollect("Needed1");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								m_Needed1 = str2;
								strOutput.Format(_T("%sNeeded Part1: %s, "), strOutput, str2);
							}
							var2 = m_pRecordset2->GetCollect("Number1");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								m_Number1 = _ttoi(str2);
								strOutput.Format(_T("%s Needed Number: %s \r\n"), strOutput, str2);
							}
							var2 = m_pRecordset2->GetCollect("Needed2");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								m_Needed2 = str2;
								strOutput.Format(_T("%sNeeded Part2: %s, "), strOutput, str2);
							}
							var2 = m_pRecordset2->GetCollect("Number2");
							if(var2.vt != VT_NULL)
							{
								str2 = (LPCSTR)_bstr_t(var2);
								m_Number2 = _ttoi(str2);
								strOutput.Format(_T("%s Needed Number: %s"), strOutput, str2);
							}
							m_pRecordset2->MoveNext();
						}
					}
					catch(_com_error *e2)
					{
						AfxMessageBox(e2->ErrorMessage());
					}
					m_pRecordset2->Close();
					m_pRecordset2 = NULL;
				}
			}
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
	GetDlgItem(IDC_OUTPUT)->SetWindowText(strOutput);
	if (m_Number1>0) QueryFromName(m_Needed1,m_Number1,ShowCount);
	if (m_Number2>0) QueryFromName(m_Needed2,m_Number2,ShowCount2);
	return 1;
}

bool CInHandDlg::AddBarCode()
{
	CInHandApp *pApp = (CInHandApp *)AfxGetApp();

	CRect tabRect;
	m_Tab.GetClientRect(&tabRect);   
	tabRect.left += 10;   
	tabRect.right -= 10;   
	tabRect.top += 30;   
	tabRect.bottom -= 10;

	if (pApp->m_AddProperty == 0)
	{
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("SELECT * FROM Part",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		try
		{
			// 写入各字段值
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("BarCode", _variant_t(pApp->m_BarCode));
			m_pRecordset->PutCollect("PartName", _variant_t(pApp->m_AddName));
			m_pRecordset->PutCollect("Stock", _variant_t(pApp->m_AddStock));
			m_pRecordset->PutCollect("InOrder", _variant_t(pApp->m_AddInOrder));
			m_pRecordset->PutCollect("Shelve", _variant_t(pApp->m_AddShelve));
			m_pRecordset->PutCollect("Storey", _variant_t(pApp->m_AddStorey));
			m_pRecordset->PutCollect("Count", _variant_t(pApp->m_AddCount));
			// m_pRecordset->PutCollect("Stock", atol(m_Age));
			m_pRecordset->Update();
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_pRecordset->Close();
		m_pRecordset = NULL;

		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("SELECT * FROM [Index]",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		try
		{
			// 写入各字段值
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("BarCode", _variant_t(pApp->m_BarCode));
			m_pRecordset->PutCollect("Property", _variant_t(_T("Part")));
			// m_pRecordset->PutCollect("Stock", atol(m_Age));
			m_pRecordset->Update();
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_pRecordset->Close();
		m_pRecordset = NULL;
		RefreshVisual();
		GetPartInfo(m_Part.m_List,tabRect.Width());
		return true;
	}
	else if (pApp->m_AddProperty == 1)
	{
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("SELECT * FROM [Order]",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		try
		{
			// 写入各字段值
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("BarCode", _variant_t(pApp->m_BarCode));
			m_pRecordset->PutCollect("OrderName", _variant_t(pApp->m_AddName));
			m_pRecordset->PutCollect("Needed1", _variant_t(pApp->m_AddNeeded1));
			m_pRecordset->PutCollect("Number1", _variant_t(pApp->m_AddNumber1));
			m_pRecordset->PutCollect("Needed2", _variant_t(pApp->m_AddNeeded2));
			m_pRecordset->PutCollect("Number2", _variant_t(pApp->m_AddNumber2));
			// m_pRecordset->PutCollect("Stock", atol(m_Age));
			m_pRecordset->Update();
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_pRecordset->Close();
		m_pRecordset = NULL;

		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("SELECT * FROM [Index]",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		try
		{
			// 写入各字段值
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("BarCode", _variant_t(pApp->m_BarCode));
			m_pRecordset->PutCollect("Property", _variant_t(_T("Order")));
			// m_pRecordset->PutCollect("Stock", atol(m_Age));
			m_pRecordset->Update();
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_pRecordset->Close();
		m_pRecordset = NULL;
		GetOrderInfo(m_Order.m_List,tabRect.Width());
		return true;
	}

	return true;
}

int CInHandDlg::GetCountRecord()
{
	int nCount = 0;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open("SELECT * FROM Part",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	while(!m_pRecordset->adoEOF)
	{
		nCount++;
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
	return nCount;
}

int CInHandDlg::GetShowCount(int a, int b, int c)
{
	for (int i = 0; i<count_record;i++)
	{
		if (m_AllPart[i]->m_Pos[0] == a && m_AllPart[i]->m_Pos[1] == b && m_AllPart[i]->m_Pos[2] == c)
		{
			return i;
		}
	}
	return -1;
}

void CInHandDlg::RefreshVisual()
{
	for (int i=0; i<count_record; i++)
	{
		delete m_AllPart[i];
	}
	count_record = GetCountRecord();
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open("SELECT * FROM Part",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return;
		}
		int a,b,c;
		int i = 0;
		while(!m_pRecordset->adoEOF)
		{
			m_AllPart[i] = new CColorStatic;
			m_AllPart[i]->Create(NULL,WS_CHILD|WS_VISIBLE, CRect(0,0,200,200),this);
			m_AllPart[i]->ChangeBkColor(RGB(0,0,255));
			var = m_pRecordset->GetCollect("Shelve");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				a = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Storey");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				b = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Count");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				c = _ttoi(str);
			}
			m_AllPart[i]->SetPosData(a,b,c);
			m_AllPart[i]->SetBlockPos(3,4);
			i++;
			//str.Format(_T("%d"),i);
			//MessageBox(str);
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
}

void CInHandDlg::QueryFromName(CString strNeed, int Number, int SetShowCount)
{	
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM Part WHERE PartName='%s'"),strNeed);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// read data
	_variant_t var;
	CString str;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return;
		}
		int a,b,c,i;
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("Shelve");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				a = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Storey");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				b = _ttoi(str);
			}
			var = m_pRecordset->GetCollect("Count");
			if(var.vt != VT_NULL)
			{
				str = (LPCSTR)_bstr_t(var);
				c = _ttoi(str);
			}
			i = GetShowCount(a,b,c);
			SetShowCount = i;
			m_AllPart[i]->ChangeBkColor(RGB(0,255,255));
			str.Format(_T("%d"),Number);
			m_AllPart[i]->SetWindowText(str);
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset = NULL;
}