#pragma once


// CColorStatic

class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnPaint();
	COLORREF m_BackColor;
	CBrush m_Brush;
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	void ChangeBkColor(COLORREF cr);
	int m_Pos[3];
	bool SetBlockPos(int count_part,int count_storey);
	void SetPosData(int a, int b, int c);
};


