/////////////////////////////////////////////////////////////////////////
//
// CDockPageBar            Version 1.2
//
// Created: Mar 16, 2004
//
/////////////////////////////////////////////////////////////////////////
// Copyright (C) 2004 by Cuick. All rights reserved.
//
// This code is free for personal and commercial use, providing this 
// notice remains intact in the source files and all eventual changes are
// clearly marked with comments.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to
// Cuick@163.net
//
// Hint: These classes are intended to be used as base classes. Do not
// simply add your code to these file - instead create a new class
// derived from CDockPageBar classes and put there what you need. See 
// CTestBar classes in the demo projects for examples.
// Modify this file only to fix bugs, and don't forget to send me a copy.
/////////////////////////////////////////////////////////////////////////
// Acknowledgements:
//	o	感谢Cristi Posea的CSizingControlBar
//	o	借鉴了王骏的《轻松实现类VC界面》中的部分代码，在这里表示感谢。
//  o   感谢hengai帮助修改了部分内存泄漏问题
//	o	开发过程中遇到的问题得到了VC知识库论坛中很多人的帮助，这里一并感谢。
//


// DockPageBar.cpp : implementation file
//

#include "stdafx.h"
#include "DockPageBar.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
// delete the line between menu bar and tool bar

// From <afximpl.h>
struct AUX_DATA
{
	int _unused1, _unused2;
	int _unused3, _unused4;
	int cxBorder2, cyBorder2;
};

extern __declspec(dllimport) AUX_DATA afxData;

class INIT_afxData
{
public:
    INIT_afxData ()
    {
        afxData.cxBorder2 = afxData.cyBorder2 = 0;
    }
} g_afxData2;

/////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
    bRaised = FALSE;
    bPushed = FALSE;
}

void CMyButton::Paint(CDC* pDC, BOOL isActive)
{
    CRect rc = GetRect();

    if (bPushed)
        pDC->Draw3dRect(rc, ::GetSysColor(COLOR_BTNSHADOW),
            ::GetSysColor(COLOR_BTNHIGHLIGHT));
    else
        if (bRaised)
            pDC->Draw3dRect(rc, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
}

// draw close button
void CCloseButton::Paint(CDC* pDC, BOOL isActive)
{
	CMyButton::Paint(pDC, isActive);

	COLORREF clrOldTextColor = pDC->GetTextColor();

	if(TRUE == isActive)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));

    int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);
    CFont font;
    int ppi = pDC->GetDeviceCaps(LOGPIXELSX);
    int pointsize = MulDiv(75, 96, ppi); // 6 points at 96 ppi
    font.CreatePointFont(pointsize, _T("Marlett"));
    CFont* oldfont = pDC->SelectObject(&font);

    pDC->TextOut(ptOrg.x + 2, ptOrg.y + 2, CString(_T("r"))); // x-like

    pDC->SelectObject(oldfont);
    pDC->SetBkMode(nPrevBkMode);
    pDC->SetTextColor(clrOldTextColor);
}

CStudButton::CStudButton()
{
}

// draw stud
void CStudButton::Paint(CDC* pDC, BOOL isActive)
{
	CMyButton::Paint(pDC, isActive);

	HPEN oldPen;
	CPen pen;
	if(TRUE == isActive)
		pen.CreatePen (PS_SOLID, 1, RGB(255,255,255));
	else
		pen.CreatePen (PS_SOLID, 1, RGB(0,0,0));

	oldPen = (HPEN)pDC->SelectObject (pen);

	if(FALSE == bFloat)
	{
		pDC->MoveTo (ptOrg.x + 4, ptOrg.y + 8);
		pDC->LineTo (ptOrg.x + 4, ptOrg.y + 3);
		pDC->LineTo (ptOrg.x + 8, ptOrg.y + 3);
		pDC->LineTo (ptOrg.x + 8, ptOrg.y + 8);
		
		pDC->MoveTo (ptOrg.x + 7, ptOrg.y + 3);
		pDC->LineTo (ptOrg.x + 7, ptOrg.y + 8);
		
		pDC->MoveTo (ptOrg.x + 2, ptOrg.y + 8);
		pDC->LineTo (ptOrg.x + 11, ptOrg.y + 8);
		
		pDC->MoveTo (ptOrg.x + 6, ptOrg.y + 8);
		pDC->LineTo (ptOrg.x + 6, ptOrg.y + 12);
	}
	else
	{
		pDC->MoveTo (ptOrg.x + 5, ptOrg.y + 4);
		pDC->LineTo (ptOrg.x + 10, ptOrg.y + 4);
		pDC->LineTo (ptOrg.x + 10, ptOrg.y + 8);
		pDC->LineTo (ptOrg.x + 5, ptOrg.y + 8);
		
		pDC->MoveTo (ptOrg.x + 5, ptOrg.y + 7);
		pDC->LineTo (ptOrg.x + 10, ptOrg.y + 7);
		
		pDC->MoveTo (ptOrg.x + 5, ptOrg.y + 2);
		pDC->LineTo (ptOrg.x + 5, ptOrg.y + 11);
		
		pDC->MoveTo (ptOrg.x + 1, ptOrg.y + 6);
		pDC->LineTo (ptOrg.x + 5, ptOrg.y + 6);
	}

	pDC->SelectObject(oldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CPageItem 


void CPageItem::Draw(CDC *pDC, BOOL bActive)
{
	CRect rect = m_rect;
	COLORREF crOldText;

	rect.top +=2;
	if(bActive)
	{
		rect.bottom -= 2;
		
		CRect rcButton=rect;
		rcButton.DeflateRect(-1,0,0,-2);
		CBrush brush(GetSysColor(COLOR_3DFACE));
		pDC->FillRect(rcButton,&brush);

		CPen pen(PS_SOLID,1,GetSysColor(COLOR_3DDKSHADOW));
		HPEN oldPen = (HPEN)pDC->SelectObject (&pen);
		pDC->MoveTo (rect.left-1 , rect.bottom+2 );
		pDC->LineTo (rect.right ,rect.bottom+2);

		pDC->MoveTo (rect.right-1, rect.top);
		pDC->LineTo (rect.right-1,rect.bottom+3 );

		pDC->SelectObject (oldPen);

		crOldText = pDC->SetTextColor(RGB(0,0,0));
		m_pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		CPen pen(PS_SOLID, 1, RGB(128,128,128));
		HPEN oldPen = (HPEN)pDC->SelectObject (&pen);

		pDC->MoveTo (rect.right, rect.top + 5);
		pDC->LineTo (rect.right, rect.bottom -1);

		pDC->SelectObject (oldPen);

		crOldText = pDC->SetTextColor(RGB(128,128,128));
		m_pWnd->ShowWindow(SW_HIDE);
	}

	rect.left += 3;
	rect.right -= 2;
	
	// draw Icon
	if(rect.Width() > 16 && m_hIcon != NULL)
	{
		::DrawIconEx(pDC->m_hDC,rect.left,rect.top + 3,m_hIcon,16,16,0,NULL,DI_NORMAL);
		rect.left += 22;
	}
	if (!m_sText.IsEmpty())
	{
		// draw text
		rect.top += 2;
		CString sText = m_sText;
		int l = sText.GetLength();
		int i;

		for(i=0;i<10 && pDC->GetTextExtent(sText).cx > rect.Width();i++,l-=2)
			sText = sText.Left(l-2);
		if(i > 0)
		{
			sText = sText.Left(l-2);
			sText += "...";
		}
		int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);
		
		pDC->DrawText(sText, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nPrevBkMode);
	}

	pDC->SetTextColor (crOldText);
}

/////////////////////////////////////////////////////////////////////////////
// CDockPageBar

IMPLEMENT_DYNAMIC(CDockPageBar, baseCDockPageBar);

CDockPageBar::CDockPageBar()
{
	m_szMinHorz = CSize(50, 50);
    m_szMinVert = CSize(60, 60);
    m_szMinFloat = CSize(150, 150);

	m_cyGripper = CAPTION_HEIGHT+4;
	m_isActive = FALSE;
	m_Title = "";
	m_nActivePage = -1;
	m_stud.bFloat = FALSE;
}

CDockPageBar::~CDockPageBar()
{
	for(POSITION pos = m_PageList.GetHeadPosition(); pos;)
	{
		CPageItem* pItem=(CPageItem*)m_PageList.GetNext(pos);
		delete pItem; pItem=NULL;
	}
	m_PageList.RemoveAll();
	for(POSITION pos = m_pDPBContext.GetHeadPosition(); pos;)
	{
		CDockPageBarContext* pDPBContext = (CDockPageBarContext*)m_pDPBContext.GetNext(pos);
		if(pDPBContext)
		{
			pDPBContext->FreeAll();
		}
	}
	m_pDPBContext.RemoveAll();
}


BEGIN_MESSAGE_MAP(CDockPageBar, baseCDockPageBar)
	//{{AFX_MSG_MAP(CDockPageBar)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
	//ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockPageBar message handlers

int CDockPageBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseCDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (m_font.CreatePointFont(85, _T("Tahoma")))
			SetFont(&m_font);

	m_isActive = FALSE;

	return 0;
}
void CDockPageBar::OnDestroy()
{
	
}

void CDockPageBar::OnUpdateCmdUI(CFrameWnd *pTarget, BOOL bDisableIfNoHndler)
{
	if (!HasGripper())
        return;

    BOOL bNeedPaint = FALSE;

    CWnd* pFocus = GetFocus();
    BOOL bActiveOld = m_isActive;

    m_isActive = (pFocus->GetSafeHwnd() && IsChild(pFocus));
	m_isActive = m_isActive || (pFocus == this);
    if (m_isActive != bActiveOld)
        bNeedPaint = TRUE;


    CPoint pt;
    ::GetCursorPos(&pt);

	///////////////////////////////////////////////////////////
	// hit close
    BOOL bHit = (OnNcHitTest(pt) == HTCLOSE);
    BOOL bLButtonDown = (::GetKeyState(VK_LBUTTON) < 0);

    BOOL bWasPushed = m_biHide.bPushed;
    m_biHide.bPushed = bHit && bLButtonDown;

    BOOL bWasRaised = m_biHide.bRaised;
    m_biHide.bRaised = bHit && !bLButtonDown;

    bNeedPaint |= (m_biHide.bPushed ^ bWasPushed) ||
                  (m_biHide.bRaised ^ bWasRaised);

	////////////////////////////////////////////////////////////
	// hit stud
	bHit = (OnNcHitTest(pt) == HTSTUD);
	bWasPushed = m_stud.bPushed;
    m_stud.bPushed = bHit && bLButtonDown;

    bWasRaised = m_stud.bRaised;
    m_stud.bRaised = bHit && !bLButtonDown;

	bNeedPaint |= (m_stud.bPushed ^ bWasPushed) ||
                  (m_stud.bRaised ^ bWasRaised);

    if (bNeedPaint)
        SendMessage(WM_NCPAINT);

}

// draw title bar
void CDockPageBar::NcPaintGripper(CDC *pDC, CRect rcClient)
{
	//Note: Here the rcClient' coordinate is for NonClient painting,
	//      so it is referenced to the current window's topleft.

    if (!HasGripper())
        return;

    CRect clientBorderRc,gripper;
	clientBorderRc=gripper=rcClient;
    CRect rcbtn = m_biHide.GetRect();

	gripper.DeflateRect(-1,-1,0,0);

	gripper.top -= m_cyGripper;
	gripper.bottom = gripper.top + CAPTION_HEIGHT;


	HFONT oldFont = (HFONT)pDC->SelectObject (m_font);

	int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF crOldText;

	if(TRUE == m_isActive)			// active state
	{
		CBrush brush(RGB(10,36,106));
		pDC->FillRect(&gripper, &brush);

		crOldText = pDC->SetTextColor(RGB(255,255,255));
	}
	else
	{
		CPen pen(PS_SOLID, 1, RGB(128,128,128));
		
		HPEN poldPen = (HPEN)pDC->SelectObject (&pen);

        // Draw better rect
		// ------------------------------
		//|                              |
		//|                              |
		// ------------------------------

		CPoint pt=gripper.TopLeft();
		pt.Offset(1,0);
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right ,gripper.top );
		pt=gripper.TopLeft();
		pt.Offset(1,gripper.Height());
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right ,gripper.bottom );
		
		pt=gripper.BottomRight();
		pt.Offset(0,-1);
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right ,gripper.top);
		pt=gripper.BottomRight();
		pt.Offset(-gripper.Width(),-1);
		pDC->MoveTo(pt);
		pDC->LineTo (gripper.left ,gripper.top);

		pDC->SelectObject (poldPen);

		crOldText = pDC->SetTextColor(RGB(0,0,0));
	}
	
	gripper.left += 4;
	gripper.top += 2;

	// draw caption
	if (!m_Title.IsEmpty())
	{
		CString sText = m_Title;
		int l = sText.GetLength();
		int i;

		for(i=0;i<10 && pDC->GetTextExtent(sText).cx > (gripper.Width() - 30);i++,l-=2)
			sText = sText.Left(l-2);
		if(i > 0)
		{
			sText = sText.Left(l-2);
			sText += "...";
		}
		pDC->TextOut (gripper.left, gripper.top, sText);
	}

	pDC->SetTextColor (crOldText);
	pDC->SetBkMode(nPrevBkMode);
	pDC->SelectObject(oldFont);

	CPoint ptOrgBtn;
    ptOrgBtn = CPoint(gripper.right - 15, gripper.top);
	m_biHide.Move(ptOrgBtn);
    m_biHide.Paint(pDC, m_isActive);

	ptOrgBtn.x -= 17;
	m_stud.Move (ptOrgBtn);
	m_stud.Paint(pDC, m_isActive);
}

void CDockPageBar::NcCalcClient(LPRECT pRc, UINT nDockBarID)
{
	CRect rcBar(pRc); // save the bar rect

    // subtract edges
    baseCDockPageBar::NcCalcClient(pRc, nDockBarID);

    if (!HasGripper()&&!m_PageList.GetCount())
        return;

    CRect rc(pRc); // the client rect as calculated by the base class

	rc.DeflateRect(1,0,1,0);

    BOOL bHorz = (nDockBarID == AFX_IDW_DOCKBAR_TOP) ||
                 (nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);


	if(!IsFloating()){
		bHorz ? rc.DeflateRect(0, m_cyGripper-1, 2,0):
				rc.DeflateRect(0, m_cyGripper-1, 0,0);
	}

	if(m_PageList.GetCount()>1)
		rc.DeflateRect(0,0,0,ITEMBUTTON_HEIGHT);

	DEFLECT_RECT_FOR_STATIC_LINK(rc);
    *pRc = rc;
}

void CDockPageBar::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	if (nHitTest == HTCLOSE)
        m_pDockSite->ShowControlBar(this, FALSE, FALSE); // hide
	if (nHitTest == HTSTUD)
		OnStudClick();

	baseCDockPageBar::OnNcLButtonUp(nHitTest, point);
	if(::IsWindow(m_hWnd))
		SendMessage(WM_NCPAINT);
}

void CDockPageBar::OnStudClick()
{
	//GetParentFrame()->PostMessage(WM_AUTOHIDE_ON, m_nDockBarID, (LPARAM)this);
	//CDockPageBar * pWnd = (CDockPageBar *)lParam;
	CAutoHideBar * pAutoHideBar;

	switch(m_nDockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP:
		pAutoHideBar = (CAutoHideBar *)((CFrameWnd*)AfxGetMainWnd())->GetControlBar(AHBRS_TOP);
		break;
	case AFX_IDW_DOCKBAR_BOTTOM:
		pAutoHideBar = (CAutoHideBar *)((CFrameWnd*)AfxGetMainWnd())->GetControlBar(AHBRS_BOTTOM);
		break;
	case AFX_IDW_DOCKBAR_LEFT:
		pAutoHideBar = (CAutoHideBar *)((CFrameWnd*)AfxGetMainWnd())->GetControlBar(AHBRS_LEFT);
		break;
	case AFX_IDW_DOCKBAR_RIGHT:
		pAutoHideBar = (CAutoHideBar *)((CFrameWnd*)AfxGetMainWnd())->GetControlBar(AHBRS_RIGHT);
		break;
	}

	pAutoHideBar->HidePageBar(this);
	((CFrameWnd*)AfxGetMainWnd())->RecalcLayout();
}

BOOL CDockPageBar::HasGripper() const
{
	if (IsFloating())
        return FALSE;
    return TRUE;
}

LRESULT CDockPageBar::OnNcHitTest(CPoint point) 
{
    CRect rcBar;
    GetWindowRect(rcBar);

	UINT nRet = baseCDockPageBar::OnNcHitTest(point);
	if (nRet != HTCLIENT)
		return nRet;

	CRect rc = m_biHide.GetRect();
	rc.OffsetRect(rcBar.TopLeft());
	if (rc.PtInRect(point))
		return HTCLOSE;

	rc = m_stud.GetRect();
	rc.OffsetRect(rcBar.TopLeft());
	if (rc.PtInRect(point))
		return HTSTUD;    

	GetItemGroupRect(&rc);
	if(rc.PtInRect(point))	
		return HTITEMBUTTON;
	GetCaptionRect(&rc);
	if(rc.PtInRect(point))	
		return HTGRIPPER;
	
    return HTCLIENT;
}


/////////////////////////////////////////////////////////////////////////////
// about PageIte

CPageItem* CDockPageBar::GetPageItem(int nIndex)
{
	CPageItem *pItem = NULL;
	POSITION pos = m_PageList.FindIndex(nIndex);
	if(pos)
		pItem = (CPageItem*)m_PageList.GetAt(pos);

	return pItem;
}

void CDockPageBar::SetActivePage(int nIndex)
{
	if(nIndex == m_nActivePage)
		return;
	CPageItem *pItem;

	pItem = (CPageItem*)GetPageItem(nIndex);

	if(!pItem) return;
	m_nActivePage = nIndex;

	m_Title = pItem->m_sText;

	SetWindowText(m_Title);
	SendMessage(WM_NCPAINT);
	Invalidate();
}

void CDockPageBar::OnSize(UINT nType, int cx, int cy) 
{
	UpdateSize();
	Invalidate();
	SendMessage(WM_NCPAINT);
}

void CDockPageBar::UpdateSize()
{
	UINT PageCount = m_PageList.GetCount();
	if(PageCount < 1) return;

	CPageItem	*pItem;
	CRect		ClientRect;
	
	if(PageCount == 1) 
	{
		GetClientRect(ClientRect);

		pItem = (CPageItem*)GetPageItem(0);;
		if(pItem->m_pWnd)
		{
				pItem->m_pWnd->MoveWindow(ClientRect);
				pItem->m_pWnd->ShowWindow(SW_SHOW);
		}
		return;
	}

	POSITION	pos;
	CRect rect,ItemRect,wndRect;
	GetWindowRect(&wndRect);
	GetClientRect(ClientRect);

	//Note: Here the rect/ItemRect' coordinate is for NonClient painting,
	//      so it is referenced to the current window's topleft.
	GetItemGroupRect(&rect);
	rect.OffsetRect(-wndRect.TopLeft());
	rect.DeflateRect(4,-3,4,3);

	DEFLECT_RECT_FOR_STATIC_LINK(rect);

	//rect.right-=10;
	ItemRect = rect;
	int AreaWidth = 0,ItemWidth,ItemIndex=0;

	for(pos=m_PageList.GetHeadPosition();pos!=NULL;ItemIndex++)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{
			ItemWidth = pItem->m_TabWidth;
			AreaWidth += ItemWidth;
			ItemRect.right = ItemRect.left+ItemWidth-1;
			pItem->m_rect = ItemRect;
			ItemRect.left = ItemRect.right + 1;
			if(pItem->m_pWnd)
				pItem->m_pWnd->MoveWindow(ClientRect);
		}
	}

	if(AreaWidth > rect.Width())
	{
		ItemRect = rect;
		int AreaWidth,MaxWidth = rect.Width()/PageCount;
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				AreaWidth = pItem->m_TabWidth;
				ItemWidth = (MaxWidth < AreaWidth)?MaxWidth:AreaWidth;
				ItemRect.right = ItemRect.left+ItemWidth;
				pItem->m_rect = ItemRect;
				ItemRect.left = ItemRect.right + 1;
			}
		}
	}
}
void CDockPageBar::GetItemGroupRect(LPRECT lpRect)
{
	CRect rcBar,cr;
	GetWindowRect(rcBar);
	rcBar.left+=1;
	rcBar.right-=3;
	rcBar.bottom-=1;
#ifdef STATIC_MFC_LINK
	rcBar.top=rcBar.bottom-ITEMBUTTON_HEIGHT;//+2;
#else
	rcBar.top=rcBar.bottom-ITEMBUTTON_HEIGHT+2;
#endif
	//Note: Here we return the rect, which referenced to the screen
	*lpRect=rcBar;
}
void CDockPageBar::GetCaptionRect(LPRECT lpRect)
{
	CRect rcBar,cr;
	GetWindowRect(rcBar);
	rcBar.left+=1;
	rcBar.right-=3;
	rcBar.top-=1;
	rcBar.bottom=rcBar.top+CAPTION_HEIGHT;
	*lpRect=rcBar;
}
BOOL CDockPageBar::AddPage(CWnd *pWnd, LPCTSTR sText, UINT IconID)
{
	ASSERT(IsWindow(pWnd->m_hWnd));
	DWORD dwStyle=pWnd->GetStyle();

	if(!(dwStyle&WS_CHILD)){
		TRACE0("Force the dock page bar content to be WS_CHILD style!");
		pWnd->ModifyStyle(WS_POPUP|WS_OVERLAPPED,WS_CHILD);
	}
	CPageItem *pItem;
	pItem = new CPageItem();
	pItem->m_pWnd = pWnd;
	pItem->m_pWnd->SetParent (this);
	pItem->m_sText = sText;
	CClientDC dc(this);
	
	pItem->m_TabWidth = dc.GetTextExtent (sText).cx;
	if(IconID)
	{
		pItem->m_hIcon = AfxGetApp()->LoadIcon(IconID);
		pItem->m_TabWidth += 18;
	}
	else
		pItem->m_hIcon = NULL;
	pItem->m_TabWidth += 9;
	if(pWnd)
	{
		CRect	rect;
		GetClientRect(rect);
		pWnd->MoveWindow(rect);
		pWnd->ShowWindow(SW_HIDE);
	}
	m_PageList.AddTail(pItem);
	UpdateWindow();
	return TRUE;
}

BOOL CDockPageBar::AddPage(CPageItem *pPageItem)
{
	pPageItem->m_pWnd->SetParent (this);
	m_PageList.AddTail(pPageItem);

	SetFocus();
	//Fore the system to send WM_NCCALCSIZE to update the client rect
	SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE);
	//Use the new size to update the window
	UpdateWindow();
	return TRUE;
}

BOOL CDockPageBar::AddPage(CDockPageBar *dockPageBar)
{
	POSITION	pos;
	CPageItem* pItem;
	for(pos = dockPageBar->m_PageList.GetHeadPosition();pos!=NULL;)
	{
		pItem=(CPageItem*)dockPageBar->m_PageList.GetNext(pos);
		if(pItem)
		{
			AddPage(pItem);
			SetActivePage(m_PageList.GetCount()-1);
		}
	}

	dockPageBar->m_pDockContext->m_pDockSite->FloatControlBar(dockPageBar,CSize(0,0),0);

	dockPageBar->m_PageList.RemoveAll();
	dockPageBar->m_pDockContext->m_pDockSite->RemoveControlBar(dockPageBar);
	UpdateWindow();
	return dockPageBar->DestroyWindow ();
}

CPageItem* CDockPageBar::DeletePage()
{
	CPageItem *pItem = NULL;
	POSITION pos = m_PageList.FindIndex(m_nActivePage);
	if(!pos)
	{
		return NULL;
	}
	pItem = (CPageItem*)m_PageList.GetAt(pos);
	pItem->m_pWnd->ShowWindow(SW_HIDE);
	m_PageList.RemoveAt (pos);
	m_nActivePage = -1;

	//Fore the system to send WM_NCCALCSIZE to update the client rect
	if(m_PageList.GetCount()==1)
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE);

	UpdateWindow();
	return pItem;
}

void CDockPageBar::UpdateWindow()
{
	if(m_nActivePage < 0)
		SetActivePage(0);	
	UpdateSize();
	Invalidate();
	SendMessage(WM_NCPAINT);;
}
void CDockPageBar::DEFLECT_RECT_FOR_STATIC_LINK(CRect & rect)
{
#ifdef STATIC_MFC_LINK
	switch(m_dwStyle&CBRS_ALIGN_ANY)
	{
	case CBRS_ALIGN_LEFT:
		rect.DeflateRect(1,1,1,1);
		break;
	case CBRS_ALIGN_RIGHT:
		rect.DeflateRect(1,1,0,1);
		break;
	case CBRS_ALIGN_TOP:
		rect.DeflateRect(1,1,0,1);
		break;
	case CBRS_ALIGN_BOTTOM:
		rect.DeflateRect(1,1,0,1);
		break;
	default:
		ASSERT(FALSE);
	}
#endif
}
void CDockPageBar::OnNcPaint()
{
	//If you are drawing the plastic line to change the dock page bar'size,
	//No painting will be done to avoid the dirty result
	if(m_bTracking) 
		return;

	// get window DC that is clipped to the non-client area
	CWindowDC dc(this);

	CRect rcClient, rcBar;
	GetClientRect(rcClient);
	ClientToScreen(rcClient);
	rcClient.DeflateRect(-1,0,-1,0);
	GetWindowRect(rcBar);
	rcClient.OffsetRect(-rcBar.TopLeft());
	rcBar.OffsetRect(-rcBar.TopLeft());

	CDC mdc;
	mdc.CreateCompatibleDC(&dc);

	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, rcBar.Width(), rcBar.Height());
	CBitmap* pOldBm = mdc.SelectObject(&bm);

	// draw borders in non-client area
	CRect rcDraw = rcBar;
	DrawBorders(&mdc, rcDraw);

	// erase the NC background
	mdc.FillRect(rcDraw, CBrush::FromHandle(
		(HBRUSH) GetClassLong(m_hWnd, GCL_HBRBACKGROUND)));


	//Draw border edges
	if (m_dwSCBStyle & SCBS_SHOWEDGES)
	{
		CRect rcEdge; // paint the sizing edges
		for (int i = 0; i < 4; i++)
			if (GetEdgeRect(rcBar, GetEdgeHTCode(i), rcEdge))
				mdc.Draw3dRect(rcEdge, ::GetSysColor(COLOR_BTNHIGHLIGHT),
				::GetSysColor(COLOR_BTNSHADOW));
	}

	//Draw Gripper(the caption bar)
	CRect rc=rcClient;
	DEFLECT_RECT_FOR_STATIC_LINK(rcClient);
	NcPaintGripper(&mdc, rcClient);
	rcClient=rc; //restore

	//Draw Client Boarder
	CRect clientBorderRc=rcBar;
	clientBorderRc.left=rcClient.left-1;
	clientBorderRc.right=rcClient.right;

	DEFLECT_RECT_FOR_STATIC_LINK(clientBorderRc);
	//if (IsHorzDocked())
	//	clientBorderRc.DeflateRect(1,m_cyGripper,5,3);
	//else
	//	clientBorderRc.DeflateRect(1,m_cyGripper,3,3);
	if (IsHorzDocked())
		clientBorderRc.DeflateRect(0,m_cyGripper,0,3);
	else
		clientBorderRc.DeflateRect(0,m_cyGripper,0,3);


	if(m_PageList.GetCount()>1)
		clientBorderRc.DeflateRect(0,0,0,ITEMBUTTON_HEIGHT);


	CPen penRect(PS_SOLID, 1, RGB(128,128,128));
	HPEN oldPen = (HPEN)mdc.SelectObject (&penRect);
	mdc.MoveTo(clientBorderRc.TopLeft());
	mdc.LineTo(clientBorderRc.right,clientBorderRc.top);
	mdc.LineTo(clientBorderRc.right,clientBorderRc.bottom);
	mdc.LineTo(clientBorderRc.left,clientBorderRc.bottom);
	mdc.LineTo(clientBorderRc.left,clientBorderRc.top);
	mdc.SelectObject (oldPen);	

	//Draw item tab button
	if(m_PageList.GetCount()>1)
	{

		CPageItem	*pItem;
		POSITION	pos;
		int			nItemIndex = 0;
		CRect		rect,wndRect;

		GetItemGroupRect(&rect);
		GetWindowRect(&wndRect);
		rect.OffsetRect(-wndRect.TopLeft());
		rect.OffsetRect(0,-1);

		DEFLECT_RECT_FOR_STATIC_LINK(rect);
		//rect.DeflateRect(0,-2,0,0);

		CBrush brush(RGB(247,243,233));
		mdc.FillRect(rect,&brush);

		CPen penButton(PS_SOLID,1,GetSysColor(COLOR_3DDKSHADOW));
		HPEN oldPen = (HPEN)mdc.SelectObject (&penButton);
		mdc.MoveTo (rect.TopLeft() );
		mdc.LineTo (rect.right, rect.top);
		mdc.SelectObject (oldPen);

		HFONT oldFont = (HFONT)mdc.SelectObject (m_font);
		// draw PageItem
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;nItemIndex++)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				pItem->Draw(&mdc,(m_nActivePage==nItemIndex)?TRUE:FALSE);
			}

		}
		mdc.SelectObject (oldFont);
	}

	// client area is not our bussiness :)
	dc.IntersectClipRect(rcBar);
	rcClient.DeflateRect(1,0,1,0);
	dc.ExcludeClipRect(rcClient);

	dc.BitBlt(0, 0, rcBar.Width(), rcBar.Height(), &mdc, 0, 0, SRCCOPY);

	ReleaseDC(&dc);

	mdc.SelectObject(pOldBm);
	bm.DeleteObject();
	mdc.DeleteDC();
}
/////////////////////////////////////////////////////////////////////////////
// 

void CDockPageBar::OnNcLButtonDown(UINT nFlags, CPoint point) 
{
	UINT nItemIndex=0;
	POSITION pos;
	CPageItem *pItem;
	CRect rect;

	//Note: Here the rect coordinate is for NonClient painting,
	//      so it is referenced to the current window's topleft.
	GetWindowRect(&rect);
	point.Offset(-rect.TopLeft());
	if (HTITEMBUTTON==nFlags){
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;nItemIndex++)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				if(pItem->m_rect.PtInRect(point))
				{
					SetFocus();
					SetActivePage(nItemIndex);
					CanDrag(point);			// drag PageItem
					return;
				}
			}
		}	
	}

	//Note: Here the rect coordinate is referenced to the screen
	point.Offset(rect.TopLeft());

	if ((nFlags >= HTSIZEFIRST) && (nFlags <= HTSIZELAST))
	{
		baseCDockPageBar::OnNcLButtonDown(nFlags, point);	
		return;
	}


	((CDockPageBarContext*)m_pDockContext)->m_isPage = FALSE;
	if (m_pDockBar != NULL&&HTGRIPPER==nFlags)
    {
        // start the drag
		SetFocus();
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->StartDrag(point);
    }
    else
        CWnd::OnNcLButtonDown(nFlags, point);

}
void CDockPageBar::OnNcLButtonDblClk(UINT nFlags, CPoint point)
{
	if (HTGRIPPER==nFlags&&m_pDockBar != NULL)
	{
		// start the drag
		ASSERT(m_pDockContext != NULL);
		m_pDockContext->ToggleDocking();
	}
	else
		CWnd::OnNcLButtonDblClk(nFlags, point);
}
void CDockPageBar::EnableDocking(DWORD dwDockStyle)
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
    ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);
    // cannot have the CBRS_FLOAT_MULTI style
    ASSERT((dwDockStyle & CBRS_FLOAT_MULTI) == 0);
    // the bar must have CBRS_SIZE_DYNAMIC style
    ASSERT((m_dwStyle & CBRS_SIZE_DYNAMIC) != 0);
	
    m_dwDockStyle = dwDockStyle;
    if (m_pDockContext == NULL)
    {
		m_pDockContext = new CDockPageBarContext(this);
		m_pDPBContext.AddTail(m_pDockContext);	//hengai
	}
	
    // permanently wire the bar's owner to its current parent
    if (m_hWndOwner == NULL)
        m_hWndOwner = ::GetParent(m_hWnd);
}

void CDockPageBar::CanDrag(CPoint pt)
{
	SetCapture();
	// get messages until capture lost or cancelled/accepted
	while (CWnd::GetCapture() == this)
	{
		MSG msg;
		if (!::GetMessage(&msg, NULL, 0, 0))
		{
			AfxPostQuitMessage(msg.wParam);
			break;
		}
		switch (msg.message)
		{
		case WM_LBUTTONUP:			
			ReleaseCapture();
			break;
		case WM_MOUSEMOVE:
			Move(msg.pt);
			break;
		default:
			DispatchMessage(&msg);
			break;
		}
	}
}

void CDockPageBar::Move(CPoint pt)
{
	CRect rect,wndRect;

	//Note: Here the rect coordinate is for NonClient painting,
	//      so it is referenced to the current window's topleft.

	GetWindowRect(&wndRect);
	GetItemGroupRect(&rect);
	rect.OffsetRect(-wndRect.TopLeft());
	pt.Offset(-wndRect.TopLeft());

	if(rect.PtInRect(pt))
	{
		int nItemIndex=0;
		POSITION pos;
		CPageItem *pItem;
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;nItemIndex++)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				if(pItem->m_rect.PtInRect(pt))
				{
					if(nItemIndex != m_nActivePage)
					{
						POSITION oldPos = m_PageList.FindIndex(m_nActivePage);
						POSITION curPos = m_PageList.FindIndex(nItemIndex);
						CPageItem *pOldItem = (CPageItem*)m_PageList.GetAt(oldPos);
						// exchange PageItem
						m_PageList.SetAt(oldPos, pItem);
						m_PageList.SetAt(curPos, pOldItem);

						m_nActivePage = nItemIndex;
						UpdateWindow();
						break;
					}
				}
			}
		}
	}
	else
	{
		ReleaseCapture();
		StartDrag(pt);
	}
}

void CDockPageBar::StartDrag(CPoint pt)
{
	ClientToScreen(&pt);
	((CDockPageBarContext*)m_pDockContext)->m_isPage = TRUE;
	m_pDockContext->StartDrag(pt);
	((CDockPageBarContext*)m_pDockContext)->m_isPage = FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CDockPageBarContext

#define _AfxGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

#define CX_BORDER   1
#define CY_BORDER   1

#define CBRS_ALIGN_INSERT_PAGE				0x0001L	// drag to another CDockPageBar
#define HORZF(dw) (dw & CBRS_ORIENT_HORZ)
#define VERTF(dw) (dw & CBRS_ORIENT_VERT)

 static void AFXAPI _AfxAdjustRectangle(CRect& rect, CPoint pt)
{
	int nXOffset = (pt.x < rect.left) ? (pt.x - rect.left) :
					(pt.x > rect.right) ? (pt.x - rect.right) : 0;
	int nYOffset = (pt.y < rect.top) ? (pt.y - rect.top) :
					(pt.y > rect.bottom) ? (pt.y - rect.bottom) : 0;
	rect.OffsetRect(nXOffset, nYOffset);
}

void CDockPageBarContext::StartDrag(CPoint pt)
{
	ASSERT_VALID(m_pBar);
	m_bDragging = TRUE;

	InitLoop();

	// GetWindowRect returns screen coordinates(not mirrored),
	// so if the desktop is mirrored then turn off mirroring
	// for the desktop dc so that we get correct focus rect drawn.
	// This layout change should be remembered, just in case ...

	if (m_pDC->GetLayout() & LAYOUT_RTL)
		m_pDC->SetLayout(LAYOUT_LTR);

	if (m_pBar->m_dwStyle & CBRS_SIZE_DYNAMIC)
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		m_ptLast = pt;
		CSize sizeHorz = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK);
		CSize sizeVert = m_pBar->CalcDynamicLayout(0, LM_VERTDOCK);
		CSize sizeFloat = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH);

		m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz);
		m_rectDragVert = CRect(rect.TopLeft(), sizeVert);

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = CRect(rect.TopLeft(), sizeFloat);
		m_rectFrameDragVert = CRect(rect.TopLeft(), sizeFloat);

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);

		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}
	else if (m_pBar->m_dwStyle & CBRS_SIZE_FIXED)
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		m_ptLast = pt;
		CSize sizeHorz = m_pBar->CalcDynamicLayout(-1, LM_HORZ | LM_HORZDOCK);
		CSize sizeVert = m_pBar->CalcDynamicLayout(-1, LM_VERTDOCK);

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz);
		m_rectFrameDragVert = m_rectDragVert = CRect(rect.TopLeft(), sizeVert);

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);
		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}
	else
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		m_ptLast = pt;
		BOOL bHorz = HORZF(m_dwStyle);
		DWORD dwMode = !bHorz ? (LM_HORZ | LM_HORZDOCK) : LM_VERTDOCK;
		CSize size = m_pBar->CalcDynamicLayout(-1, dwMode);

		// calculate inverted dragging rect
		if (bHorz)
		{
			m_rectDragHorz = rect;
			m_rectDragVert = CRect(CPoint(pt.x - rect.Height()/2, rect.top), size);
		}
		else // vertical orientation
		{
			m_rectDragVert = rect;
			m_rectDragHorz = CRect(CPoint(rect.left, pt.y - rect.Width()/2), size);
		}

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = m_rectDragHorz;
		m_rectFrameDragVert = m_rectDragVert;

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);
		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}

	// adjust rectangles so that point is inside
	_AfxAdjustRectangle(m_rectDragHorz, pt);
	_AfxAdjustRectangle(m_rectDragVert, pt);
	_AfxAdjustRectangle(m_rectFrameDragHorz, pt);
	_AfxAdjustRectangle(m_rectFrameDragVert, pt);

	// initialize tracking state and enter tracking loop
	m_dwOverDockStyle = CanDock();
	Move(pt);   // call it here to handle special keys
	Track();
}

CDockPageBarContext::~CDockPageBarContext(void)
{

}

//hengai
void CDockPageBarContext::FreeAll()
{
	for(POSITION pos = m_pDPBar.GetHeadPosition(); pos;)
	{
		CDockPageBar* pBar = (CDockPageBar*)m_pDPBar.GetNext(pos);
		ASSERT(pBar != NULL);
		delete pBar->m_pDockBar; pBar->m_pDockBar = NULL;
		delete pBar; pBar = NULL;
	}
	
	m_pDPBar.RemoveAll ();		// cuick 2004/04/08
}

BOOL CDockPageBarContext::Track()
{
	// don't handle if capture already set
	if (::GetCapture() != NULL)
		return FALSE;

	// set capture to the window which received this message
	m_pBar->SetCapture();
	ASSERT(m_pBar == CWnd::GetCapture());

	// get messages until capture lost or cancelled/accepted
	while (CWnd::GetCapture() == m_pBar)
	{
		MSG msg;
		if (!::GetMessage(&msg, NULL, 0, 0))
		{
			AfxPostQuitMessage(msg.wParam);
			break;
		}

		switch (msg.message)
		{
		case WM_LBUTTONUP:
			if (m_bDragging)
				EndDrag();
			else
				EndResize();
			return TRUE;
		case WM_MOUSEMOVE:
			if (m_bDragging)
				Move(msg.pt);
			else
				Stretch(msg.pt);
			break;
		case WM_KEYUP:
			if (m_bDragging)
				OnKey((int)msg.wParam, FALSE);
			break;
		case WM_KEYDOWN:
			if (m_bDragging)
				OnKey((int)msg.wParam, TRUE);
			if (msg.wParam == VK_ESCAPE)
			{
				CancelLoop();
				return FALSE;
			}
			break;
		case WM_RBUTTONDOWN:
			CancelLoop();
			return FALSE;

		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}

	CancelLoop();

	return FALSE;
}
CDockPageBar * CDockPageBarContext::TryToGetDockPageBar(POINT pt)
{
	CFrameWnd * pFrameWnd=(CFrameWnd *)AfxGetMainWnd();

	POSITION pos = pFrameWnd->m_listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		CControlBar* pBar = (CControlBar*)pFrameWnd->m_listControlBars.GetNext(pos);
		ASSERT(pBar != NULL);
		if (pBar->IsKindOf(RUNTIME_CLASS(CDockPageBar)))
		{
			CRect rect;
			pBar->GetWindowRect(&rect);
			if(rect.PtInRect(pt)&&!pBar->IsFloating())
				return (CDockPageBar*)pBar;
		}
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////
// drag and draw focus rect
void CDockPageBarContext::Move(CPoint pt)
{
	CPoint ptOffset = pt - m_ptLast;

	if(TRUE == isDockPage(pt))
	{
		m_dwOverDockStyle = CBRS_ALIGN_INSERT_PAGE;
	}
	else
	{

		//MACRO Definition for the adavnced docking
		//#define CBRS_ALIGN_INSERT_PAGE				0x0001L	
#define DOCK_ALIGN_INSERT_PAGE		CBRS_ALIGN_INSERT_PAGE
#define DOCK_IN_FRAME_CLIENT  0x02
#define DOCK_IN_FRAME_BORDER  0x04
#define DOCK_IN_DOCK_PAGE_BAR 0x08

#define HOR_BORDER_DETECT_PIXELS  max(CAPTION_HEIGHT+8,ITEMBUTTON_HEIGHT+8)
#define VER_BORDER_DETECT_PIXELS  16

#define BORDER_DETECT_LEFT   0x0100
#define BORDER_DETECT_RIGHT  0x0200
#define BORDER_DETECT_TOP    0x0400
#define BORDER_DETECT_BOTTOM 0x0800

		//POINT pt;
		//GetCursorPos(&pt);
		CWnd *pCurWnd= CWnd::FromHandle(::WindowFromPoint(pt));
		CDockPageBar *pDockPageBarWnd;

		DWORD borderDetect=0;
		CRect mainFrameRect,mainFrameClientRect;
		DWORD dwDockStyle=0;
		m_bAdvancedDock=FALSE;
		m_endDragDockStruct.dwDockStyle=0;

		CWnd *pMainFrameWnd=AfxGetMainWnd();

		pMainFrameWnd->GetWindowRect(&mainFrameRect);

		//Try to find a docking position
		if(mainFrameRect.PtInRect(pt))
		{
			//Get the pure client rect of the frame wnd
			GET_MAIN_FRAME_PURE_CLIENT(pMainFrameWnd,mainFrameClientRect);

			if((pDockPageBarWnd=TryToGetDockPageBar(pt))!=NULL){
				pDockPageBarWnd->GetWindowRect(&m_curRect);
				m_endDragDockStruct.dwDockStyle=dwDockStyle=DOCK_IN_DOCK_PAGE_BAR;
				m_bAdvancedDock=TRUE;
			}else if(mainFrameClientRect.PtInRect(pt)){
				m_curRect=mainFrameClientRect;
				m_endDragDockStruct.dwDockStyle=dwDockStyle=DOCK_IN_FRAME_CLIENT;
				m_bAdvancedDock=TRUE;
			}else{ //the bar is move to the non client area (tool bar for example)

				CRect rc=mainFrameClientRect;
				
				rc.DeflateRect(-VER_BORDER_DETECT_PIXELS,-HOR_BORDER_DETECT_PIXELS);
				if(rc.PtInRect(pt)){
					m_curRect=rc;
					m_endDragDockStruct.dwDockStyle=dwDockStyle=DOCK_IN_FRAME_BORDER;
					m_bAdvancedDock=TRUE;
				}else{
					const CRuntimeClass *pRunTimeClass=pCurWnd->GetRuntimeClass();
					TRACE0("Unprocessed window type:");
					//TRACE0(pRunTimeClass->m_lpszClassName);
					TRACE0("\r\n");
					m_bAdvancedDock=FALSE;
				}
			}
		}else{
			CRect rc=mainFrameRect;

			rc.DeflateRect(-VER_BORDER_DETECT_PIXELS,-HOR_BORDER_DETECT_PIXELS);
			if(rc.PtInRect(pt)){
				m_curRect=rc;
				m_endDragDockStruct.dwDockStyle=dwDockStyle=DOCK_IN_FRAME_BORDER;
				m_bAdvancedDock=TRUE;
			}else{
				const CRuntimeClass * pRunTimeClass=pCurWnd->GetRuntimeClass();
				TRACE0("Unprocessed window type:");
				//TRACE0(pRunTimeClass->m_lpszClassName);
				TRACE0("\r\n");
				m_bAdvancedDock=FALSE;
			}
		}

		//Check whether the current position can be used for the advanced docking :-)
		if(m_bAdvancedDock&&
		   m_curRect.Width()>VER_BORDER_DETECT_PIXELS*2+1&&
		   m_curRect.Height()>HOR_BORDER_DETECT_PIXELS*2+1)
		{		    
			//Init the current detection border rect 
			CRect rectLeft(m_curRect.TopLeft(),CSize(VER_BORDER_DETECT_PIXELS,m_curRect.Height())),
				  rectTop(m_curRect.TopLeft(),CSize(m_curRect.Width(),HOR_BORDER_DETECT_PIXELS));
		    CRect rectRight=rectLeft,rectBottom=rectTop;

			rectRight.OffsetRect(m_curRect.Width()-VER_BORDER_DETECT_PIXELS,0);
			rectBottom.OffsetRect(0,m_curRect.Height()-HOR_BORDER_DETECT_PIXELS);

			borderDetect|=rectLeft.PtInRect(pt) ?   BORDER_DETECT_LEFT:0;
			borderDetect|=rectRight.PtInRect(pt) ?  BORDER_DETECT_RIGHT:0;
			borderDetect|=rectTop.PtInRect(pt) ?    BORDER_DETECT_TOP:0;
			borderDetect|=rectBottom.PtInRect(pt) ? BORDER_DETECT_BOTTOM:0;

			ASSERT(!((borderDetect&BORDER_DETECT_LEFT)&&(borderDetect&BORDER_DETECT_RIGHT)));
			ASSERT(!((borderDetect&BORDER_DETECT_TOP)&&(borderDetect&BORDER_DETECT_BOTTOM)));

			if(borderDetect&BORDER_DETECT_LEFT)
			{
				borderDetect=BORDER_DETECT_LEFT;
				if(DOCK_IN_FRAME_CLIENT==dwDockStyle||DOCK_IN_FRAME_BORDER==dwDockStyle)
					dwDockStyle=CBRS_ALIGN_LEFT;
				else
					dwDockStyle=pDockPageBarWnd->m_dwStyle;
			}else if(borderDetect&BORDER_DETECT_RIGHT){
				borderDetect=BORDER_DETECT_RIGHT;
				if(DOCK_IN_FRAME_CLIENT==dwDockStyle||DOCK_IN_FRAME_BORDER==dwDockStyle)
					dwDockStyle=CBRS_ALIGN_RIGHT;
				else
					dwDockStyle=pDockPageBarWnd->m_dwStyle;
			}else if(borderDetect&BORDER_DETECT_TOP){
				borderDetect=BORDER_DETECT_TOP;
				if(DOCK_IN_FRAME_CLIENT==dwDockStyle||DOCK_IN_FRAME_BORDER==dwDockStyle)
					dwDockStyle=CBRS_ALIGN_TOP;
				else
					dwDockStyle=pDockPageBarWnd->m_dwStyle;
			}else if(borderDetect&BORDER_DETECT_BOTTOM){
				borderDetect=BORDER_DETECT_BOTTOM;
				if(DOCK_IN_FRAME_CLIENT==dwDockStyle||DOCK_IN_FRAME_BORDER==dwDockStyle)
					dwDockStyle=CBRS_ALIGN_BOTTOM;
				else
					dwDockStyle=pDockPageBarWnd->m_dwStyle;
			}

			CRect rc;
			m_pBar->GetWindowRect(&rc);
			INT hightWidth;			
			
			if(DOCK_IN_FRAME_BORDER==m_endDragDockStruct.dwDockStyle)
			{
				m_curRect.DeflateRect(VER_BORDER_DETECT_PIXELS,HOR_BORDER_DETECT_PIXELS);

				if(borderDetect&(BORDER_DETECT_LEFT|BORDER_DETECT_RIGHT)){
					if(m_curRect==mainFrameClientRect)
						(borderDetect&BORDER_DETECT_LEFT ? m_curRect.left:m_curRect.right)=
						(borderDetect&BORDER_DETECT_LEFT ? mainFrameClientRect.left:mainFrameClientRect.right);
					else
						(borderDetect&BORDER_DETECT_LEFT ? m_curRect.left:m_curRect.right)=
						(borderDetect&BORDER_DETECT_LEFT ? mainFrameRect.left:mainFrameRect.right);
					m_curRect.top=mainFrameRect.top;
					m_curRect.bottom=mainFrameRect.bottom;

				}else{
					if(m_curRect==mainFrameClientRect)
						(borderDetect&BORDER_DETECT_TOP ? m_curRect.top:m_curRect.bottom)=
						(borderDetect&BORDER_DETECT_TOP ? mainFrameClientRect.top:mainFrameClientRect.bottom);
					else
						(borderDetect&BORDER_DETECT_TOP ? m_curRect.top:m_curRect.bottom)=
						(borderDetect&BORDER_DETECT_TOP ? mainFrameRect.top:mainFrameRect.bottom);

					m_curRect.left=mainFrameRect.left;
					m_curRect.right=mainFrameRect.right;

				}
				hightWidth=borderDetect&(BORDER_DETECT_LEFT|BORDER_DETECT_RIGHT) ? mainFrameRect.Width():mainFrameRect.Height();
			}else
				hightWidth=borderDetect&(BORDER_DETECT_LEFT|BORDER_DETECT_RIGHT) ? rc.Width():rc.Height();

			switch(borderDetect)
			{
			case BORDER_DETECT_LEFT:
				m_curRect.right=m_curRect.left+min(hightWidth,m_curRect.Width()/2);
				break;
			case BORDER_DETECT_RIGHT:
				m_curRect.left=m_curRect.right-min(hightWidth,m_curRect.Width()/2);
				break;
			case BORDER_DETECT_TOP:
				m_curRect.bottom=m_curRect.top+min(hightWidth,m_curRect.Height()/2);
				break;
			case BORDER_DETECT_BOTTOM:
				m_curRect.top=m_curRect.bottom-min(hightWidth,m_curRect.Height()/2);
				break;
			default:
				m_bAdvancedDock=FALSE;
			}		
		}else
			m_bAdvancedDock=FALSE;

		if(m_bAdvancedDock){
			ASSERT(VERTF(dwDockStyle)||HORZF(dwDockStyle));
			m_dwOverDockStyle=dwDockStyle;
			if(DOCK_IN_DOCK_PAGE_BAR==m_endDragDockStruct.dwDockStyle){			
				m_endDragDockStruct.pDockPageBar=pDockPageBarWnd;
				m_endDragDockStruct.dwDockStyle|=borderDetect;
			}
			else
				m_endDragDockStruct.pDockPageBar=NULL;;
			m_rectDragVert.OffsetRect(ptOffset);
			m_rectDragHorz.OffsetRect(ptOffset);
			m_rectFrameDragHorz.OffsetRect(ptOffset);
			m_rectFrameDragVert.OffsetRect(ptOffset);
		}else{
			// offset all drag rects to new position
			m_rectDragHorz.OffsetRect(ptOffset);
			m_rectFrameDragHorz.OffsetRect(ptOffset);
			m_rectDragVert.OffsetRect(ptOffset);
			m_rectFrameDragVert.OffsetRect(ptOffset);
			m_dwOverDockStyle = 0;/*m_bForceFrame ? 0 : CanDock();*/
		}
	}

	m_ptLast = pt;
	// update feedback
	if(FALSE == m_isMe)
		DrawFocusRect();
	else
		DrawFocusRect(TRUE);
}

// get the target CDockPageBar on mouse move
BOOL CDockPageBarContext::isDockPage(CPoint pt)
{
	m_isMe = FALSE;
	HWND hWnd = WindowFromPoint(pt);
	CWnd * pWnd=CWnd::FromHandle (hWnd);

	if(pWnd->IsKindOf (RUNTIME_CLASS(CDockPageBar)))
	{
		CDockPageBar* pBar = (CDockPageBar*)pWnd;
		if(pBar != m_pBar)
		{
			CRect rectCaption,rectItem;
			pBar->GetWindowRect (&rectCaption);
			rectItem=rectCaption;

			rectCaption.bottom = rectCaption.top + pBar->m_cyGripper;
			rectItem.top=rectItem.bottom-ITEMBUTTON_HEIGHT;
			if(rectCaption.PtInRect (pt)||
			   (pBar->m_PageList.GetCount()>1)&&(rectItem.PtInRect(pt)))
			{
				m_pTgDockPage = pBar;
				pBar->GetWindowRect (&m_addRect);
				return TRUE;
			}
		}
		else
		{
			m_isMe = TRUE;
		}
	}else if(pWnd->IsKindOf(RUNTIME_CLASS(CMiniDockFrameWnd))){  //Docking in the float window

		CMiniDockFrameWnd * pFrameWnd=(CMiniDockFrameWnd *)pWnd;
		//Get the DockPageBar on the Floating MiniDockFrameWnd
		CDockPageBar* pBar = (CDockPageBar* )CWnd::FromHandle(pWnd->m_hWndOwner);
		ASSERT(pBar->IsKindOf(RUNTIME_CLASS(CDockPageBar)));

		if(pBar != m_pBar)
		{
			CRect rectCaption,rectItem;
			pFrameWnd->GetWindowRect (&rectCaption);
			pBar->GetWindowRect(&rectItem);
			rectCaption.bottom = rectCaption.top + pBar->m_cyGripper;
			rectItem.top=rectItem.bottom-ITEMBUTTON_HEIGHT;

			if(rectCaption.PtInRect (pt)||
			  (pBar->m_PageList.GetCount()>1)&&(rectItem.PtInRect(pt)))
			{
				m_pTgDockPage = pBar;
				pBar->GetWindowRect (&m_addRect);
				return TRUE;
			}
		}
		else
		{
			m_isMe = TRUE;
		}

	}

	m_pTgDockPage = NULL;
	return FALSE;
}

void CDockPageBarContext::EndDrag()
{
	CancelLoop();

	if(TRUE == m_isMe)
		return;

	// drag to another CDockPageBar
	if((NULL != m_pTgDockPage) && (m_dwOverDockStyle == CBRS_ALIGN_INSERT_PAGE))
	{
		if(TRUE == m_isPage)	// drag PageItem
		{
			CPageItem * pItem = (CPageItem *)((CDockPageBar*)m_pBar)->DeletePage ();
			m_pTgDockPage->AddPage(pItem);
		}
		else					// drag a CDockPageBar object to another CDockPageBar
		{
			m_pTgDockPage->AddPage((CDockPageBar*)m_pBar);

		}	
		return;
	}

	// if drag a PageItem, create a new bar which contains the PageItem
	CControlBar* pBar;
	if(TRUE == m_isPage)		// drag PageItem (dock or float)
		pBar = CreateNewBar();
	else
		pBar = m_pBar;			// drag CDockPageBar

	if(NULL == pBar)
		return;

	if (m_dwOverDockStyle != 0)
	{
		CDockBar* pDockBar;
		CFrameWnd * pFrameWnd=(CFrameWnd *)AfxGetMainWnd();

		//Find the specific docking bar
		POSITION pos = pFrameWnd->m_listControlBars.GetHeadPosition();
		while (pos != NULL)
		{
			pDockBar = (CDockBar*)pFrameWnd->m_listControlBars.GetNext(pos);
			if (pDockBar->IsDockBar() && pDockBar->IsWindowVisible() &&
				(pDockBar->m_dwStyle & m_dwOverDockStyle & CBRS_ALIGN_ANY) &&
				(!pDockBar->m_bFloating ||
				(m_dwOverDockStyle & pDockBar->m_dwStyle & CBRS_FLOAT_MULTI)))
			{
				break;
			}
		}
		ASSERT(pDockBar != NULL);

		CRect rect;
		if(m_bAdvancedDock){
			rect=m_curRect;
			if(m_endDragDockStruct.dwDockStyle&DOCK_IN_DOCK_PAGE_BAR)
			{
				ASSERT(m_endDragDockStruct.pDockPageBar);
				ASSERT(m_endDragDockStruct.pDockPageBar->IsKindOf(RUNTIME_CLASS(CDockPageBar)));
				CRect rc;
				m_endDragDockStruct.pDockPageBar->GetWindowRect(&rc);

				if(VERTF(m_endDragDockStruct.pDockPageBar->m_dwStyle))
				{
					if(m_endDragDockStruct.dwDockStyle&BORDER_DETECT_RIGHT)
						rect.OffsetRect(rc.Width()/2,0);			
					else if(m_endDragDockStruct.dwDockStyle&BORDER_DETECT_LEFT)
						rect.OffsetRect(-rc.Width()/2,0);			
				}else if(HORZF(m_endDragDockStruct.pDockPageBar->m_dwStyle))
				{
					if(m_endDragDockStruct.dwDockStyle&BORDER_DETECT_TOP)
						rect.OffsetRect(0,-rc.Width()/2);
					else if(m_endDragDockStruct.dwDockStyle&BORDER_DETECT_BOTTOM)
						rect.OffsetRect(0,rc.Width()/2);
				}else
					ASSERT(FALSE);
			}
			//Advanced docking :)
			if(VERTF(m_dwOverDockStyle))
			{
				((CDockPageBar*)pBar)->GetVerSize().cx=rect.Width();
				((CDockPageBar*)pBar)->GetVerSize().cy=rect.Height();				
			}else if(HORZF(m_dwOverDockStyle))
			{
				((CDockPageBar*)pBar)->GetHorSize().cx=rect.Width();
				((CDockPageBar*)pBar)->GetHorSize().cy=rect.Height();
			}else
				ASSERT(FALSE);

		}else
			rect= (m_dwOverDockStyle & CBRS_ORIENT_VERT) ? m_rectDragVert : m_rectDragHorz;

		UINT uID = _AfxGetDlgCtrlID(pDockBar->m_hWnd);
		if (uID >= AFX_IDW_DOCKBAR_TOP &&
			uID <= AFX_IDW_DOCKBAR_BOTTOM)
		{
			m_uMRUDockID = uID;
			m_rectMRUDockPos = rect;
			pDockBar->ScreenToClient(&m_rectMRUDockPos);
		}

		// dock it at the specified position, RecalcLayout will snap
		m_pDockSite->DockControlBar(pBar, pDockBar, &rect);
		m_pDockSite->RecalcLayout();
		if(DOCK_IN_DOCK_PAGE_BAR==m_endDragDockStruct.dwDockStyle)
			m_endDragDockStruct.pDockPageBar->SetFocus();
	}
	else if ((m_dwStyle & CBRS_SIZE_DYNAMIC) || (HORZF(m_dwStyle) && !m_bFlip) ||
			(VERTF(m_dwStyle) && m_bFlip))
	{
		m_dwMRUFloatStyle = CBRS_ALIGN_TOP | (m_dwDockStyle & CBRS_FLOAT_MULTI);
		m_ptMRUFloatPos = m_rectFrameDragHorz.TopLeft();
		m_pDockSite->FloatControlBar(pBar, m_ptMRUFloatPos, m_dwMRUFloatStyle);
	}
	else // vertical float
	{
		m_dwMRUFloatStyle = CBRS_ALIGN_LEFT | (m_dwDockStyle & CBRS_FLOAT_MULTI);
		m_ptMRUFloatPos = m_rectFrameDragVert.TopLeft();
		m_pDockSite->FloatControlBar(pBar, m_ptMRUFloatPos, m_dwMRUFloatStyle);
	}
}

CDockPageBar* CDockPageBarContext::CreateNewBar()
{
	CPageItem * pItem = (CPageItem *)((CDockPageBar*)m_pBar)->DeletePage ();

	CDockPageBar* pBar = new CDockPageBar();
	
	if (!(pBar->Create(_T("New Bar"), m_pDockSite, 12345)))
	{
		TRACE0("Failed to create mybar\n");
		return NULL;      // fail to create
	}
	
	pBar->SetBarStyle(m_pBar->GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	pBar->EnableDocking(CBRS_ALIGN_ANY);
	pBar->AddPage (pItem);
	m_pDPBar.AddTail(pBar);

	return pBar;
}

void CDockPageBarContext::DrawFocusRect(BOOL bRemoveRect)
{
	ASSERT(m_pDC != NULL);

	// default to thin frame
	CSize size(3,3);

	// determine new rect and size
	CRect rect;
	CBrush* pWhiteBrush = CBrush::FromHandle((HBRUSH)::GetStockObject(WHITE_BRUSH));
	CBrush* pDitherBrush = CDC::GetHalftoneBrush();
	CBrush* pBrush = pDitherBrush;

	if(m_bAdvancedDock)
	{
		rect=m_curRect;;
	}else{
		if (HORZF(m_dwOverDockStyle))
			rect = m_rectDragHorz;
		else if (VERTF(m_dwOverDockStyle))
			rect = m_rectDragVert;
		else
		{
			// use thick frame instead
			size.cx = GetSystemMetrics(SM_CXFRAME) - CX_BORDER;
			size.cy = GetSystemMetrics(SM_CYFRAME) - CY_BORDER;
			if ((HORZF(m_dwStyle) && !m_bFlip) || (VERTF(m_dwStyle) && m_bFlip))
				rect = m_rectFrameDragHorz;
			else
				rect = m_rectFrameDragVert;
			pBrush = pDitherBrush;
		}
	}

	if (bRemoveRect)
		size.cx = size.cy = 0;

	if(m_dwOverDockStyle == CBRS_ALIGN_INSERT_PAGE)
		rect = m_addRect;		// rect of target CDockPageBar

	// draw it and remember last size
	m_pDC->DrawDragRect(&rect, size, &m_rectLast, m_sizeLast,
		pBrush, m_bDitherLast ? pDitherBrush : pWhiteBrush);
	m_rectLast = rect;
	m_sizeLast = size;
	m_bDitherLast = (pBrush == pDitherBrush);
}



