// MyStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "MyStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar

CMyStatusBar::CMyStatusBar()
{
}

CMyStatusBar::~CMyStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMyStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CMyStatusBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar message handlers

void CMyStatusBar::OnPaint() 
{
	Default();

    CClientDC cDC (this);
	CPen pen(PS_SOLID, 1, ::GetSysColor (COLOR_3DSHADOW));
	HPEN oldPen = (HPEN)cDC.SelectObject(pen);

    CRect rcItem;

    cDC.SelectObject (::GetStockObject (NULL_BRUSH));

    for ( int i = 0; i < m_nCount; i++ )
    {
        GetItemRect (i, rcItem);
        cDC.Rectangle (rcItem); 
    }
	cDC.SelectObject (oldPen);
}

BOOL CMyStatusBar::SetIndicators (const UINT* lpIDArray, int nIDCount)
{
    if ( !CStatusBar::SetIndicators (lpIDArray, nIDCount) )
    {
        return false;
    }
    SendMessage (SB_SETMINHEIGHT, 20);

    for ( int i = 0; i < nIDCount; i++ )
    {
        UINT a, b;
        int c;

        GetPaneInfo (i, a, b, c);
        SetPaneInfo (i, a, b|SBPS_NOBORDERS, c);
    }
    return true;
}