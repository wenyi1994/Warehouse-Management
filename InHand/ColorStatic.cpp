// ColorStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "InHand.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{

}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
//	ON_WM_CTLCOLOR()
//	ON_WM_PAINT()
ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CColorStatic 消息处理程序



HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	return m_Brush;
}

void CColorStatic::ChangeBkColor(COLORREF cr)
{
	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(cr);
	m_BackColor = cr;
	RedrawWindow();
}

bool CColorStatic::SetBlockPos(int count_part, int count_storey)
{
	CRect   rect;        
	GetParent()->GetClientRect(&rect);
	switch(m_Pos[0])
	{
	case 1:
		this->SetWindowPos(GetParent(),rect.Width()-610+270/count_part*(m_Pos[2]-1),135+270/count_storey*(m_Pos[1]-1),270/count_part,270/count_storey,SWP_NOZORDER);
		break;
	case 2:
		this->SetWindowPos(GetParent(),rect.Width()-290+270/count_part*(m_Pos[2]-1),135+270/count_storey*(m_Pos[1]-1),270/count_part,270/count_storey,SWP_NOZORDER);
		break;
	case 3:
		this->SetWindowPos(GetParent(),rect.Width()-610+270/count_part*(m_Pos[2]-1),55+270/count_storey*(m_Pos[1]-1)+rect.Height()/2,270/count_part,270/count_storey,SWP_NOZORDER);
		break;
	case 4:
		this->SetWindowPos(GetParent(),rect.Width()-290+270/count_part*(m_Pos[2]-1),55+270/count_storey*(m_Pos[1]-1)+rect.Height()/2,270/count_part,270/count_storey,SWP_NOZORDER);
		break;
	}
	return true;
}

void CColorStatic::SetPosData(int a, int b, int c)
{
	m_Pos[0] = a;
	m_Pos[1] = b;
	m_Pos[2] = c;
}