#pragma once
#include "CPartVisual.h"
class CStorey
{
public:
	CStorey(void);
	~CStorey(void);
	int m_CountPart;
	CPartVisual *m_Parts;
};
