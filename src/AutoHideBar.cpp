/////////////////////////////////////////////////////////////////////////
//
// CAutoHideBar            Version 1.2
//
// Created: Mar 30, 2004
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
//

#include "stdafx.h"
#include "AutoHideBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAHFloatWnd  Implementation Start

CAHFloatWnd::CAHFloatWnd()
{
	m_font.CreatePointFont(85, _T("Tahoma"));
	m_Title = "AutoHideFloatWnd";
	m_bCursorInAutoHideBarItem=FALSE;
	m_animDispParam.slideStep=0;
	m_animDispParam.slideStepCount=0;
	m_animDispParam.bInAnimateDisplay=FALSE;
	m_animDispParam.timerId=0;
	m_activePageItem=NULL;
}

CAHFloatWnd::~CAHFloatWnd()
{
}


BEGIN_MESSAGE_MAP(CAHFloatWnd, CWnd)
	//{{AFX_MSG_MAP(CAHFloatWnd)
	ON_WM_NCCALCSIZE()
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_MOUSEACTIVATE()
	ON_WM_NCLBUTTONUP()
	ON_WM_TIMER()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()	
	//}}AFX_MSG_MAP
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAHFloatWnd message handlers
void CAHFloatWnd::GetBorderWidths(DWORD dwStyle,BORDER_WIDTH & borderWidth)
{
	switch(dwStyle&0xFF00)
	{
	case CBRS_LEFT:
		{
			borderWidth.cx_left=0;
			borderWidth.cx_right=::GetSystemMetrics(SM_CXFRAME);
			borderWidth.cy_top=2;
			borderWidth.cy_bottom=0;
		}
		break;
	case CBRS_RIGHT:
		{
			borderWidth.cx_left=::GetSystemMetrics(SM_CXFRAME);
			borderWidth.cx_right=1;
			borderWidth.cy_top=2;
			borderWidth.cy_bottom=0;
		}
		break;
	case CBRS_TOP:
		{
			borderWidth.cx_left=0;
			borderWidth.cx_right=1;
			borderWidth.cy_top=2;
			borderWidth.cy_bottom=3;
		}
		break;
	case CBRS_BOTTOM:
		{
			borderWidth.cx_left=0;
			borderWidth.cx_right=1;
			borderWidth.cy_top=2;
			borderWidth.cy_bottom=2;
		}
		break;
	default:
		{
			borderWidth.cx_left=borderWidth.cx_right=borderWidth.cy_top=borderWidth.cy_bottom=0;
		}
		break;
	}

}
void CAHFloatWnd::StartAnimateDisplay( DWORD dwFlag,DWORD dwTime)
{
	m_animDispParam.bInAnimateDisplay=TRUE;
	m_animDispParam.slideStepCount=max(1,dwTime/50);

	if(TID_SLIDE_IN==dwFlag){
		m_animDispParam.slideStep=m_animDispParam.slideStepCount-1;
		if(m_activePageItem)
			GetWindowRect(&(m_activePageItem->m_lastAHFloatWndRect));
		KillTimer(TID_AUTO_HIDE_DELAY);
	}else{
		SetTimer(TID_AUTO_HIDE_DELAY,AUTO_HIDE_DELAY_TIMES, NULL);
		m_animDispParam.slideStep=0;
	}

	//Reset previous animate display timer
	if(m_animDispParam.timerId!=0)
		KillTimer(m_animDispParam.timerId);

	m_animDispParam.timerId=dwFlag;
	SetTimer(dwFlag,50,NULL);
}
void CAHFloatWnd::DoSlideStep()
{
	CRect rc(m_animDispParam.rect);

	switch(m_dwStyle&CBRS_ALIGN_ANY) 
	{
	case CBRS_ALIGN_LEFT: 
		rc.OffsetRect((m_animDispParam.slideStep + 1)*rc.Width()/m_animDispParam.slideStepCount-rc.Width(),0);
		break;
	case CBRS_ALIGN_RIGHT: 
		rc.OffsetRect(rc.Width()-(m_animDispParam.slideStep + 1)*rc.Width()/m_animDispParam.slideStepCount,0); 
		break;
	case CBRS_ALIGN_TOP: 
		rc.OffsetRect(0,(m_animDispParam.slideStep + 1)*rc.Height()/m_animDispParam.slideStepCount-rc.Height());
		break;
	case CBRS_ALIGN_BOTTOM: 
		rc.OffsetRect(0,rc.Height()-(m_animDispParam.slideStep + 1)*rc.Height()/m_animDispParam.slideStepCount);
		break;
	}
	SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);	
	Invalidate(FALSE);
}
void CAHFloatWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);

	CRect rc(&lpncsp->rgrc[0]);
	BORDER_WIDTH borderWidth;
	GetBorderWidths(m_dwStyle,borderWidth);

	rc.DeflateRect(-::GetSystemMetrics(SM_CXFRAME),-::GetSystemMetrics(SM_CXFRAME),
				   -::GetSystemMetrics(SM_CXFRAME),-::GetSystemMetrics(SM_CXFRAME));
	rc.DeflateRect(borderWidth.cx_left+1,CAPTION_HEIGHT+borderWidth.cy_top*2+1, borderWidth.cx_right+1,borderWidth.cy_bottom+1);
	lpncsp->rgrc[0] = rc;
   //Non Clinet coordinate refered to the windows's topleft
	m_captionRect.left=borderWidth.cx_left;
	m_captionRect.right=m_captionRect.left+rc.Width();
	m_captionRect.top=borderWidth.cy_top;
	m_captionRect.bottom=m_captionRect.top+CAPTION_HEIGHT;
}

void CAHFloatWnd::OnNcPaint() 
{
	//CWnd::OnNcPaint();
    CWindowDC dc(this);

	//Get bounding rect of the client coordinate
    CRect rcBar,rect;
    GetWindowRect(rcBar);//Screen coordinate

	rcBar.OffsetRect (-rcBar.TopLeft ());//Logic coordinate
	rect = rcBar;
	BORDER_WIDTH borderWidth;
	GetBorderWidths(m_dwStyle,borderWidth);

	//Draw the flat frame border
	//|-----------------------------|
	//|							    |
	//|                             |
	//|                             |
	//|                             |
	//|-----------------------------|

	//|
	//|
	//|
	rect.right = borderWidth.cx_left;
	dc.FillSolidRect(&rect, ::GetSysColor(COLOR_BTNFACE));
	//----------------
	rect = rcBar;
	rect.top = rect.bottom - borderWidth.cy_bottom;
	dc.FillSolidRect(&rect, ::GetSysColor(COLOR_BTNFACE));
	//|
	//|
	//|
	rect = rcBar;
	rect.left = rect.right - borderWidth.cx_right;
	dc.FillSolidRect(&rect, ::GetSysColor(COLOR_BTNFACE));
	//-----------------
    rect=rcBar;
    rect.bottom = rect.top + CAPTION_HEIGHT + borderWidth.cy_top*2;
	dc.FillSolidRect(&rect, ::GetSysColor(COLOR_BTNFACE));

	CRect clientBorderRc=rcBar;

	//if (IsHorzDocked())
	clientBorderRc.DeflateRect(borderWidth.cx_left,CAPTION_HEIGHT+borderWidth.cy_top*2
							   ,borderWidth.cx_right+1,borderWidth.cy_bottom+1);
	//else
	//	clientBorderRc.DeflateRect(1,CAPTION_HEIGHT,3,3);

	CPen penRect(PS_SOLID, 1, RGB(128,128,128));
	HPEN oldPen = (HPEN)dc.SelectObject (&penRect);
	dc.MoveTo(clientBorderRc.TopLeft());
	dc.LineTo(clientBorderRc.right,clientBorderRc.top);
	dc.LineTo(clientBorderRc.right,clientBorderRc.bottom);
	dc.LineTo(clientBorderRc.left,clientBorderRc.bottom);
	dc.LineTo(clientBorderRc.left,clientBorderRc.top);
	dc.SelectObject (oldPen);	


    //Draw the single border 3D side adage
	CPen pen1(PS_SOLID,1,RGB(128,128,128));            //DarkGrey
	CPen pen2(PS_SOLID,1,RGB(0,0,0));				   //Black
	CPen pen3(PS_SOLID,1,RGB(255,255,255));            //White
	CPen pen4(PS_SOLID,1,::GetSysColor(COLOR_BTNFACE));//LightGrey
	
	HPEN pOldPen=NULL;
	switch(m_dwStyle&0xFF00) // CBRS_ALIGN_ANY|CBRS_BORDER_ANY == 0xFF00
	{
		case CBRS_TOP:
			{
				pOldPen = (HPEN)dc.SelectObject (&pen2);
				CPoint pt=rcBar.BottomRight();			
				pt.Offset(-2,-1);
				dc.MoveTo(pt);
				pt.Offset(1-rcBar.Width(),0);
				dc.LineTo(pt);

				dc.SelectObject (&pen1);	
				pt=rcBar.BottomRight();
				pt.Offset(-2,-2);

				dc.MoveTo(pt);
				pt.Offset(1-rcBar.Width(),0);
				dc.LineTo(pt);
			}
			break;
		case CBRS_LEFT:
			{	
				pOldPen = (HPEN)dc.SelectObject (&pen2);
				CPoint pt=rcBar.BottomRight();
				pt.Offset(-1,0);
				dc.MoveTo(pt);
				pt.Offset(0,-rcBar.Height());
				dc.LineTo(pt);

				dc.SelectObject (&pen1);	
				pt=rcBar.BottomRight();
				pt.Offset(-2,0);

				dc.MoveTo(pt);
				pt.Offset(0,-rcBar.Height());
				dc.LineTo(pt);
			}
			break;
		case CBRS_BOTTOM:
			{
				pOldPen = (HPEN)dc.SelectObject (&pen4);
				CPoint pt=rcBar.TopLeft();
				dc.MoveTo(pt);
				pt.Offset(rcBar.Width()-1,0);
				dc.LineTo(pt);

				dc.SelectObject (&pen3);	
				pt=rcBar.TopLeft();
				pt.Offset(0,1);

				dc.MoveTo(pt);
				pt.Offset(rcBar.Width()-1,0);
				dc.LineTo(pt);
			}
			break;
		case CBRS_RIGHT:
			{
				pOldPen = (HPEN)dc.SelectObject (&pen4);
				CPoint pt=rcBar.TopLeft();
				pt.Offset(1,0);
				dc.MoveTo(pt);
				pt.Offset(0,rcBar.Height()-1);
				dc.LineTo(pt);

				dc.SelectObject (&pen3);	
				pt=rcBar.TopLeft();
				pt.Offset(2,0);

				dc.MoveTo(pt);
				pt.Offset(0,rcBar.Height()-1);
				dc.LineTo(pt);
			}	
			break;
		default:
			break;
	}
	if (pOldPen!=NULL)
		dc.SelectObject(pOldPen);

	//Draw the caption
	CRect gripper = rect;
    CRect rcbtn = m_biHide.GetRect();


    gripper.DeflateRect(borderWidth.cx_left,borderWidth.cy_top,
						borderWidth.cx_right,borderWidth.cy_top);

	CDC* pDC = &dc;
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

		// Draw better caption rect
		// ------------------------------
		//|                              |
		// ------------------------------

		// ------------------------------>
		CPoint pt=gripper.TopLeft();
		pt.Offset(1,0);
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right-1 ,gripper.top );

		// ------------------------------>
		pt=gripper.TopLeft();
		pt.Offset(1,gripper.Height());
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right-1 ,gripper.bottom );

		//                                  ^
		//									|
		//									|
		pt=gripper.BottomRight();
		pt.Offset(-1,-1);
		pDC->MoveTo (pt);
		pDC->LineTo (gripper.right-1 ,gripper.top);
		//^
		//|
		//|
		pt=gripper.BottomRight();
		pt.Offset(-gripper.Width(),-1);
		pDC->MoveTo(pt);
		pDC->LineTo (gripper.left ,gripper.top);

		crOldText = pDC->SetTextColor(RGB(0,0,0));
	}
	
	gripper.left += 4;
	gripper.top += 2;

	// Draw caption text
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

	if(rcBar.Width()<pDC->GetTextExtent(m_Title).cx+17+13)
		return;

	//Draw the hide & close button
	CPoint ptOrgBtn;
    ptOrgBtn = CPoint(gripper.right - 15, gripper.top);
	m_biHide.Move(ptOrgBtn);
    m_biHide.Paint(pDC, m_isActive);

	ptOrgBtn.x -= 17;
	m_stud.Move (ptOrgBtn);
	m_stud.Paint(pDC, m_isActive);
}

void CAHFloatWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CWnd* pWnd = GetWindow(GW_CHILD);
	if (pWnd != NULL)
	{
		pWnd->MoveWindow(0, 0, cx, cy);
	}
	SendMessage(WM_NCPAINT);
	
}

void CAHFloatWnd::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	BOOL bNeedPaint = FALSE;

    CPoint pt;
    ::GetCursorPos(&pt);

	///////////////////////////////////////////////////////////
	// hit close
    BOOL bHit = (OnNcHitTest(pt) == HTHIDE);
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
	m_bCursorInAutoHideBarItem=FALSE;
	CWnd::OnNcMouseMove(nHitTest, point);
}

LRESULT CAHFloatWnd::OnNcHitTest(CPoint point) 
{
	CRect rcBar;
    GetWindowRect(rcBar);

	UINT nRet = CWnd::OnNcHitTest(point);

    CRect rc = m_biHide.GetRect();
    rc.OffsetRect(rcBar.TopLeft());
    if (rc.PtInRect(point))
        return HTHIDE;
	else
	{
		if(TRUE == m_biHide.bRaised)
		{
			m_biHide.bRaised = FALSE;
			SendMessage(WM_NCPAINT);
		}
	}

	rc = m_stud.GetRect();
    rc.OffsetRect(rcBar.TopLeft());
    if (rc.PtInRect(point))
        return HTSTUD;
	else
	{
		if(TRUE == m_stud.bRaised)
		{
			m_stud.bRaised = FALSE;
			SendMessage(WM_NCPAINT);
		}
	}

	rc=m_captionRect;
    rc.OffsetRect(rcBar.TopLeft());
	if(rc.PtInRect(point))
		return HTNCCLIENT;

	if (m_dwStyle & CBRS_ALIGN_TOP)
		nRet = (HTBOTTOM == nRet?nRet: HTNOWHERE);
	else if (m_dwStyle & CBRS_ALIGN_BOTTOM)
		nRet = (HTTOP == nRet?nRet: HTNOWHERE);
	else if (m_dwStyle & CBRS_ALIGN_LEFT)
		nRet = (HTRIGHT == nRet?nRet: HTNOWHERE);
	else if (m_dwStyle & CBRS_ALIGN_RIGHT)
		nRet = (HTLEFT == nRet?nRet: HTNOWHERE);
	else
		ASSERT(FALSE);      // can never happen

    return nRet;
}

int CAHFloatWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	m_isActive = TRUE;
	SendMessage(WM_NCPAINT);
	SetFocus();
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CAHFloatWnd::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	CWnd::OnNcLButtonUp(nHitTest, point);
	if (nHitTest == HTHIDE)
	{
        ShowWindow(SW_HIDE);
		m_biHide.bPushed = FALSE;
	}
	if (nHitTest == HTSTUD)
	{
		m_stud.bPushed = FALSE;
		OnStudClick();
	}
}

void CAHFloatWnd::OnStudClick()
{
	m_HideItem->Dock ();
}

void CAHFloatWnd::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case TID_AUTO_HIDE_DELAY:
		{
			POINT pt;
			GetCursorPos(&pt);
			RECT rect;
			GetWindowRect(&rect);
			
			if (!PtInRect(&rect,pt)&&!m_bCursorInAutoHideBarItem&&!GetCapture())
			{
				KillTimer(TID_AUTO_HIDE_DELAY);
				StartAnimateDisplay(TID_SLIDE_IN);
			}		
		}
		break;
	case TID_SLIDE_OUT:  //Show
		if(m_animDispParam.slideStep<m_animDispParam.slideStepCount-1)
		{
			m_animDispParam.slideStep++;
			DoSlideStep();
		}else{
			//clean timer and reset animate display parameter
			SetWindowPos(NULL,
						 m_animDispParam.rect.left,m_animDispParam.rect.top,
						 m_animDispParam.rect.Width(),m_animDispParam.rect.Height(),
						 SWP_NOZORDER|SWP_SHOWWINDOW);
			KillTimer(TID_SLIDE_OUT);
			m_animDispParam.slideStep=0;
			m_animDispParam.bInAnimateDisplay=FALSE;
		}
		break;
	case TID_SLIDE_IN:  //Hide
		if(m_animDispParam.slideStep>-1)
		{
			m_animDispParam.slideStep--;
			DoSlideStep();
		}else{
			//clean timer and reset animate display parameter
			KillTimer(TID_SLIDE_IN);
			ShowWindow(SW_HIDE);
			m_animDispParam.slideStep=m_animDispParam.slideStepCount-1;
			m_animDispParam.bInAnimateDisplay=FALSE;
		}
		break;
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}

void CAHFloatWnd::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	BOOL bNeedPaint = FALSE;
    BOOL bActiveOld = m_isActive;

    m_isActive = TRUE;
    if (m_isActive != bActiveOld)
        bNeedPaint = TRUE;

	///////////////////////////////////////////////////////////
	// hit close
    BOOL bHit = (nHitTest == HTHIDE);
    BOOL bLButtonDown = TRUE;

    BOOL bWasPushed = m_biHide.bPushed;
    m_biHide.bPushed = bHit && bLButtonDown;

    BOOL bWasRaised = m_biHide.bRaised;
    m_biHide.bRaised = bHit && !bLButtonDown;

    bNeedPaint |= (m_biHide.bPushed ^ bWasPushed) ||
                  (m_biHide.bRaised ^ bWasRaised);

	////////////////////////////////////////////////////////////
	// hit stud
	bHit = (nHitTest == HTSTUD);
	bWasPushed = m_stud.bPushed;
    m_stud.bPushed = bHit && bLButtonDown;

    bWasRaised = m_stud.bRaised;
    m_stud.bRaised = bHit && !bLButtonDown;

	bNeedPaint |= (m_stud.bPushed ^ bWasPushed) ||
                  (m_stud.bRaised ^ bWasRaised);

    if (bNeedPaint)
        SendMessage(WM_NCPAINT);	
	CWnd::OnNcLButtonDown(nHitTest, point);
}

void CAHFloatWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd * pFocusWnd=GetFocus();
	if(pFocusWnd!=this)
		m_isActive=FALSE;

	CWnd::OnShowWindow(bShow, nStatus);
}

void CAHFloatWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnGetMinMaxInfo(lpMMI);
	if(m_animDispParam.bInAnimateDisplay){
		lpMMI->ptMinTrackSize.x=5;
		lpMMI->ptMinTrackSize.y=5;
	}
}
//CAHFloatWnd implementation ends
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// CHidePageItem 
CHidePageItem::CHidePageItem()
{
	m_lastAHFloatWndRect.SetRectEmpty();
}

CHidePageItem::~CHidePageItem()
{
}

void CHidePageItem::Draw(CDC *pDC, BOOL bHorz)
{

	if(bHorz)
		::DrawIconEx(pDC->m_hDC,m_rect.left+3, m_rect.top+(m_rect.Height()-16)/2+1,m_hIcon,16,16,0,NULL,DI_NORMAL);
	else
		::DrawIconEx(pDC->m_hDC,m_rect.left+(m_rect.Width()-16)/2, m_rect.top + 3,m_hIcon,16,16,0,NULL,DI_NORMAL);
	CRect rect = m_rect;
	rect.left += 3;
	rect.top += 1;
	if(TRUE == m_isActive)
	{
		int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);
		if(TRUE == bHorz)
		{
			rect.left += 16 + 6; 
			pDC->ExtTextOut(rect.left, rect.top+3, ETO_CLIPPED, NULL, m_sText, NULL);
		}
		else
		{
			rect.top += 16 + 6;
			pDC->ExtTextOut(rect.right-3, rect.top, ETO_CLIPPED, NULL, m_sText, NULL);
		}
		pDC->SetBkMode(nPrevBkMode);
	}
	if(TRUE == bHorz)
	{
		pDC->MoveTo (m_rect.right, m_rect.top+2 );
		pDC->LineTo (m_rect.right, m_rect.bottom );
	}
	else
	{
		pDC->MoveTo (m_rect.left, m_rect.bottom );
		pDC->LineTo (m_rect.right, m_rect.bottom );			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// CHideItem

CHideItem::CHideItem()
{
	m_nActivePage = -1;
}

CHideItem::~CHideItem()
{	
}

void CHideItem::Draw(CDC *pDC)
{
	CBrush brush(GetSysColor(COLOR_3DFACE));
	pDC->FillRect(m_rect,&brush);

	CPen pen(PS_SOLID, 1, RGB(128,128,128));
	HPEN poldPen = (HPEN)pDC->SelectObject (&pen);

	if(m_dwStyle & CBRS_ORIENT_HORZ)
	{
		pDC->MoveTo (m_rect.left, m_rect.top );
		pDC->LineTo (m_rect.left, m_rect.bottom );
		pDC->MoveTo (m_rect.right, m_rect.top );
		pDC->LineTo (m_rect.right, m_rect.bottom );
		if (m_dwStyle & CBRS_ALIGN_TOP)
		{
			pDC->MoveTo (m_rect.left, m_rect.bottom );
			pDC->LineTo (m_rect.right+1, m_rect.bottom );//MS CDC Bug???
		}
		else if (m_dwStyle & CBRS_ALIGN_BOTTOM)
		{
			pDC->MoveTo (m_rect.left, m_rect.top );
			pDC->LineTo (m_rect.right, m_rect.top );
		}
	}
	else if(m_dwStyle & CBRS_ORIENT_VERT)
	{
		pDC->MoveTo (m_rect.left, m_rect.top );
		pDC->LineTo (m_rect.right, m_rect.top );
		pDC->MoveTo (m_rect.left, m_rect.bottom );
		pDC->LineTo (m_rect.right, m_rect.bottom );
		if (m_dwStyle & CBRS_ALIGN_LEFT)
		{
			pDC->MoveTo (m_rect.right, m_rect.top );
			pDC->LineTo (m_rect.right, m_rect.bottom+1);//MS CDC Bug???
		}
		else if (m_dwStyle & CBRS_ALIGN_RIGHT)
		{
			pDC->MoveTo (m_rect.left, m_rect.top );
			pDC->LineTo (m_rect.left, m_rect.bottom );
		}
	}

	CHidePageItem* pHidePageItem;
	for(int i =0; i< m_arrPags.GetSize(); i++)
	{
		pHidePageItem = (CHidePageItem*)m_arrPags[i];
		

		if(m_dwStyle & CBRS_ORIENT_HORZ)
		{
			pHidePageItem->Draw (pDC, TRUE);
		}
		else if(m_dwStyle & CBRS_ORIENT_VERT)
		{
			pHidePageItem->Draw (pDC, FALSE);
		}
	}
	pDC->SelectObject (poldPen);
}

void CHideItem::AddPageItem(CDockPageBar* pPageBar, CWnd* pWnd, DWORD dwStyle)
{
	m_dwStyle = dwStyle;
	//Copy the dockPageBar's Rect
	pPageBar->GetWindowRect (m_oldWndRect );
	pPageBar->GetParentFrame()->ScreenToClient (&m_oldWndRect);

	m_pAutoHideBar = pWnd;
	m_pDockPageBar = pPageBar;

	pPageBar->ShowWindow (SW_HIDE);
	m_wndFloat.CreateEx(WS_EX_LEFT,	AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW),
						NULL, (WS_CHILDWINDOW|WS_BORDER|WS_THICKFRAME|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS),
						m_oldWndRect, 
						AfxGetMainWnd(), 0);
	m_wndFloat.m_dwStyle = dwStyle;
	m_wndFloat.ShowWindow (SW_HIDE);
	m_wndFloat.m_HideItem = this;
	m_nActivePage = pPageBar->m_nActivePage;

	POSITION	pos;
	CPageItem*  pPageItem;

	for(pos=pPageBar->m_PageList.GetHeadPosition();pos!=NULL;)
	{
		pPageItem=(CPageItem*)pPageBar->m_PageList.GetNext(pos);
		if(pPageItem)
		{
			CHidePageItem* pHidePage = new CHidePageItem;
			pHidePage->m_hIcon = pPageItem->m_hIcon;
			pHidePage->m_pWnd = pPageItem->m_pWnd;
			pHidePage->m_sText = pPageItem->m_sText;
			m_arrPags.Add (pHidePage);
		}
	}

}

void CHideItem::UpDateSize(CDC* pDC, CRect *rect)
{

	CHidePageItem* pHidePageItem;

	m_rect = *rect;
	for(int i =0; i< m_arrPags.GetSize(); i++)
	{
		pHidePageItem = (CHidePageItem*)m_arrPags[i];
		if(NULL != pHidePageItem)
		{
			if(m_dwStyle & CBRS_ORIENT_HORZ)
			{
				pHidePageItem->m_rect = *rect;
				pHidePageItem->m_rect.right =  pHidePageItem->m_rect.left + 21;
				pHidePageItem->m_isActive = FALSE;
				if(m_nActivePage == i)
				{
					pHidePageItem->m_rect.right += 24;
					pHidePageItem->m_rect.right += pDC->GetTextExtent (pHidePageItem->m_sText).cx;
					pHidePageItem->m_rect.right += AUTO_HIDE_BAR_WIDTH;
					pHidePageItem->m_isActive = TRUE;
				}
				m_rect.right = rect->left = pHidePageItem->m_rect.right;
			}
			else if(m_dwStyle & CBRS_ORIENT_VERT)
			{
				pHidePageItem->m_rect = *rect;
				pHidePageItem->m_rect.bottom =  pHidePageItem->m_rect.top + 21;
				pHidePageItem->m_isActive = FALSE;
				if(m_nActivePage == i)
				{
					pHidePageItem->m_rect.bottom += 24;
					pHidePageItem->m_rect.bottom += pDC->GetTextExtent (pHidePageItem->m_sText).cx;
					pHidePageItem->m_rect.bottom += AUTO_HIDE_BAR_WIDTH;
					pHidePageItem->m_isActive = TRUE;
				}
				m_rect.bottom = rect->top = pHidePageItem->m_rect.bottom;
			}
		}
	}
	
}

BOOL CHideItem::OnMouseMove(CPoint pt)
{
	CHidePageItem* pHidePageItem;

	for(int i =0; i< m_arrPags.GetSize(); i++)
	{
		pHidePageItem = (CHidePageItem*)m_arrPags[i];
		if(NULL != pHidePageItem)
		{
			if(pHidePageItem->m_rect.PtInRect (pt))
			{
				Show(i);
				if(m_nActivePage != i)
				{
					
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
	
	return FALSE;
}

void CHideItem::Show(int nShow)
{

	if(m_nActivePage == nShow&&m_wndFloat.IsWindowVisible ()||
	   m_wndFloat.m_animDispParam.bInAnimateDisplay)
		return;

	CRect rect;
	m_pAutoHideBar->GetWindowRect(rect);

	//Show the new activated one
	CHidePageItem * pCurActivePageItem=((CHidePageItem*)m_arrPags[nShow]);

	//Get the proper rect size for the new activated item
	if(pCurActivePageItem->m_lastAHFloatWndRect.IsRectEmpty())
		m_wndFloat.GetWindowRect (m_oldWndRect);
	else
		m_oldWndRect=pCurActivePageItem->m_lastAHFloatWndRect;
   
	if (m_dwStyle & CBRS_ORIENT_HORZ)
	{
		rect.bottom = rect.top + m_oldWndRect.Height();
		if (m_dwStyle & CBRS_ALIGN_TOP)
		{
			rect.OffsetRect (0, AUTO_HIDE_BAR_WIDTH-2);
		}
		else if (m_dwStyle & CBRS_ALIGN_BOTTOM)
		{
			rect.OffsetRect (0, -m_oldWndRect.Height());
		}
	}
	else if (m_dwStyle & CBRS_ORIENT_VERT)
	{
		rect.right = rect.left + m_oldWndRect.Width();
		if (m_dwStyle & CBRS_ALIGN_LEFT)
			rect.OffsetRect (AUTO_HIDE_BAR_WIDTH, 0);
		else if (m_dwStyle & CBRS_ALIGN_RIGHT)
			rect.OffsetRect (-m_oldWndRect.Width(), 0);
	}
	else
	{
		ASSERT(FALSE);      // can never happen
	}

	//Hide the float window first
	m_wndFloat.StartAnimateDisplay(TID_SLIDE_IN);
	m_wndFloat.MoveWindow(0,0,0,0);


	//Hide the previous active page
	((CHidePageItem*)m_arrPags[m_nActivePage])->m_pWnd->ShowWindow (SW_HIDE);
	((CHidePageItem*)m_arrPags[m_nActivePage])->m_pWnd->SetParent (m_pDockPageBar);
	
	//Set the new activated page's to the float window
	CWnd * pchild = pCurActivePageItem->m_pWnd;
	pchild->SetParent (&m_wndFloat);
	m_wndFloat.m_Title = pCurActivePageItem->m_sText;
	m_wndFloat.m_activePageItem=pCurActivePageItem;

	CWnd* pFrameWnd=AfxGetMainWnd();

	//Prevent the m_wndFloat window from being shadowed by the client view window
	BRING_CLIENT_WINDOW_TO_BOTTOM(pFrameWnd);

	//Use the client coordinate of the main frame
	pFrameWnd->ScreenToClient(&rect);	
	//Prevent the m_pAutoHideBar window from being shadowed by the m_wndFloat window
	m_wndFloat.SetWindowPos(m_pAutoHideBar,rect.left,rect.top ,rect.Width (), rect.Height (),SWP_HIDEWINDOW);
    m_wndFloat.m_animDispParam.rect=rect;

	//Move the new activated page to the float window
	CRect clientRect;
	m_wndFloat.GetClientRect(clientRect);
	pchild->MoveWindow(clientRect);
	pchild->ShowWindow (SW_SHOW);
	

	//Animate show
	m_nActivePage = nShow;	
	m_wndFloat.StartAnimateDisplay(TID_SLIDE_OUT);
}

void CHideItem::Dock()
{
	((CHidePageItem*)m_arrPags[m_nActivePage])->m_pWnd->SetParent (m_pDockPageBar);
	RemoveAll();

	m_wndFloat.DestroyWindow();
	m_pDockPageBar->ShowWindow (SW_SHOW);
	m_pDockPageBar->UpdateSize();
	((CAutoHideBar*)m_pAutoHideBar)->UpdateBar();
}

/////////////////////////////////////////////////////////////////////////////
// remove all item (2004/04/06)
void CHideItem::RemoveAll()
{
	CHidePageItem* pHidePageItem;
	int count = m_arrPags.GetSize();

	for(int i =0; i< count; i++)
	{
		pHidePageItem = (CHidePageItem*)m_arrPags[0];
		delete pHidePageItem;
		pHidePageItem = NULL;
		m_arrPags.RemoveAt(0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoHideBar implementation starts

CAutoHideBar::CAutoHideBar()
{
	m_pCurSelItem=NULL;
}

CAutoHideBar::~CAutoHideBar()
{
	POSITION	pos;
	CHideItem*	pHideItem;

	for(pos=m_listBars.GetHeadPosition();pos!=NULL;)
	{
		pHideItem = (CHideItem*)m_listBars.GetNext(pos);
		if(NULL != pHideItem)
		{
			pHideItem->RemoveAll ();
			delete pHideItem;
			pHideItem = NULL;
		}
	}
	m_listBars.RemoveAll ();
}


BEGIN_MESSAGE_MAP(CAutoHideBar, CControlBar)
	//{{AFX_MSG_MAP(CAutoHideBar)
	ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAutoHideBar message handlers

BOOL CAutoHideBar::Create(CWnd *pParentWnd, DWORD dwStyle, UINT nID)
{
	ASSERT(pParentWnd != NULL);
	ASSERT_KINDOF(CFrameWnd, pParentWnd);

	m_dwStyle = (dwStyle & CBRS_ALL);
	// register and create the window 
    CString wndclass = ::AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,
        ::LoadCursor(NULL, IDC_ARROW),
        ::GetSysColorBrush(COLOR_BTNFACE), 0);

    dwStyle &= ~CBRS_ALL; // keep only the generic window styles
    dwStyle |= WS_CLIPCHILDREN; // prevents flashing

	if(m_dwStyle & CBRS_ORIENT_HORZ)
	{
		m_Font.CreateFont(13 ,0, 0,0, FW_NORMAL, 0,0,0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
			FF_ROMAN , _T("Tahoma"));
	}
	else if(m_dwStyle & CBRS_ORIENT_VERT)
	{
		m_Font.CreateFont(13,0, -900,-900, FW_NORMAL, 0,0,0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
			FF_ROMAN , _T("Tahoma"));
	}

	// Note: Parent must resize itself for control bar to be resized
	return CWnd::Create(wndclass, NULL, dwStyle, CRect(0, 0, 0, 0), pParentWnd, nID);
}

LRESULT CAutoHideBar::OnSizeParent(WPARAM wParam, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;
	DWORD dwStyle = m_dwStyle;

	if(!(dwStyle & WS_VISIBLE))
	{
		SetWindowPos(NULL, 0, 0, 0, 0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_HIDEWINDOW);
	}

	if ((dwStyle & WS_VISIBLE) && (dwStyle & CBRS_ALIGN_ANY) != 0)
	{
		// align the control bar
		CRect rect;
		rect.CopyRect(&lpLayout->rect);

		CSize sizeAvail = rect.Size();  // maximum size available

		// get maximum requested size
		DWORD dwMode = lpLayout->bStretch ? LM_STRETCH : 0;
		if (dwStyle & CBRS_ORIENT_HORZ)
			dwMode |= LM_HORZ | LM_HORZDOCK;
		else
			dwMode |=  LM_VERTDOCK;

		CSize size (AUTO_HIDE_BAR_WIDTH,AUTO_HIDE_BAR_WIDTH);

		size.cx = min(size.cx, sizeAvail.cx);
		size.cy = min(size.cy, sizeAvail.cy);

		if (dwStyle & CBRS_ORIENT_HORZ)
		{
			lpLayout->sizeTotal.cy += size.cy;
			lpLayout->sizeTotal.cx = max(lpLayout->sizeTotal.cx, size.cx);
			if (dwStyle & CBRS_ALIGN_TOP)
				lpLayout->rect.top += size.cy;
			else if (dwStyle & CBRS_ALIGN_BOTTOM)
			{
				size.cy-=2; // Bottom alignment has different width from the Top alignment
				rect.top = rect.bottom - size.cy;
				lpLayout->rect.bottom -= size.cy;
			}
			rect.bottom = rect.top + size.cy;
			rect.right = lpLayout->rect.right;
		}
		else if (dwStyle & CBRS_ORIENT_VERT)
		{
			lpLayout->sizeTotal.cx += size.cx;
			lpLayout->sizeTotal.cy = max(lpLayout->sizeTotal.cy, size.cy);
			if (dwStyle & CBRS_ALIGN_LEFT)
				lpLayout->rect.left += size.cx;
			else if (dwStyle & CBRS_ALIGN_RIGHT)
			{
				rect.left = rect.right - size.cx;
				lpLayout->rect.right -= size.cx;
			}
			rect.right = rect.left + size.cx;
			rect.bottom = lpLayout->rect.bottom ;
		}
		else
		{
			ASSERT(FALSE);      // can never happen
		}
		m_size = CSize(rect.BottomRight() - rect.TopLeft());
		SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
	}
	return 0;
}

void CAutoHideBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	TRACKMOUSEEVENT trackEvt;
	trackEvt.cbSize=sizeof(TRACKMOUSEEVENT);
	trackEvt.dwFlags=TME_LEAVE|TME_HOVER;
	trackEvt.dwHoverTime=AUTO_HIDE_DELAY_TIMES;
	trackEvt.hwndTrack=m_hWnd;
	_TrackMouseEvent(&trackEvt);

	CControlBar::OnMouseMove(nFlags, point);
}

void CAutoHideBar::OnPaint() 
{
	CPaintDC PaintDC(this); // device context for painting
	
	CRect rcBar;
	GetClientRect(&rcBar);
	CDC	dc;
	dc.CreateCompatibleDC(&PaintDC);

	CBitmap bm;
	bm.CreateCompatibleBitmap(&PaintDC, rcBar.Width(), rcBar.Height());
	dc.SelectObject(bm);
	//dc.SetBoundsRect(&rcBar, DCB_DISABLE);

    // draw background
	CBrush brush(RGB(247,243,233));
    dc.FillRect(&rcBar, &brush);
	CPen pen(PS_SOLID,1,RGB(128,128,128)),*pOldPen=dc.SelectObject(&pen);
	dc.Rectangle(&rcBar);
	dc.SelectObject(pOldPen);

	dc.SelectObject (m_Font);

	//COLORREF crOldText;
	//crOldText = dc.SetTextColor(RGB(128,128,128));

	UpDateSize();
	DrawItem(&dc);
	//dc.SetTextColor(crOldText);

	PaintDC.BitBlt (rcBar.left, rcBar.top, rcBar.Width(), rcBar.Height(), &dc, 0,0,SRCCOPY);
	dc.DeleteDC ();
}

void CAutoHideBar::DrawItem(CDC *pDC)
{
	POSITION	pos;
	CHideItem* pHideItem;

	for(pos=m_listBars.GetHeadPosition();pos!=NULL;)
	{
		pHideItem = (CHideItem*)m_listBars.GetNext(pos);;
		if(NULL != pHideItem)
			pHideItem->Draw (pDC);
	}
}

void CAutoHideBar::HidePageBar(CDockPageBar *pDockPageBar)
{
	m_dwStyle |= WS_VISIBLE;
	CHideItem* pHideItem = new CHideItem;
	
	pHideItem->AddPageItem(pDockPageBar, this, m_dwStyle);

	m_listBars.AddTail (pHideItem);
	Invalidate();
}

void CAutoHideBar::UpDateSize()
{
	CPaintDC dc(this);
	dc.SelectObject (m_Font);

	CRect rect;
	GetClientRect(&rect);

	if(m_dwStyle & CBRS_ORIENT_HORZ)
	{
		rect.left += 2;
		if (m_dwStyle & CBRS_ALIGN_TOP)
			rect.bottom -= 3;
		else if (m_dwStyle & CBRS_ALIGN_BOTTOM)
			rect.top += 2;

	}
	else if(m_dwStyle & CBRS_ORIENT_VERT)
	{
		rect.top += 2;
		if (m_dwStyle & CBRS_ALIGN_LEFT)
			rect.right -= 3;
		else if (m_dwStyle & CBRS_ALIGN_RIGHT)
			rect.left += 2;
	}
	else
	{
		ASSERT(FALSE);      // can never happen
	}

	POSITION	pos;
	CHideItem* pHideItem;

	for(pos=m_listBars.GetHeadPosition();pos!=NULL;)
	{
		pHideItem = (CHideItem*)m_listBars.GetNext(pos);;
		if(NULL != pHideItem)
		{
			pHideItem->UpDateSize (&dc, &rect);
			if(m_dwStyle & CBRS_ORIENT_HORZ)
			{
				rect.left += 20;
			}
			else if(m_dwStyle & CBRS_ORIENT_VERT)
			{
				rect.top += 20;
			}
		}
	}
}

void CAutoHideBar::GetClientRect(CRect *rect)
{
	CWnd::GetClientRect (rect);
	if(m_dwStyle & CBRS_ORIENT_HORZ)
	{
		if (m_dwStyle & CBRS_ALIGN_TOP)
			rect->bottom -= 1;
	}
	else if(m_dwStyle & CBRS_ORIENT_VERT)
	{
		if (m_dwStyle & CBRS_ALIGN_LEFT)
			rect->right -= 1;
	}
	else
	{
		ASSERT(FALSE);      // can never happen
	}
}

void CAutoHideBar::UpdateBar()
{
	POSITION	pos, pos2;
	CHideItem* pHideItem;
	

	for(pos=m_listBars.GetHeadPosition();( pos2 = pos ) != NULL;)
	{
		pHideItem = (CHideItem*)m_listBars.GetNext(pos);;
		if(NULL != pHideItem)
		{
			if(pHideItem->m_arrPags.GetSize () == 0)
			{
				delete pHideItem;
				pHideItem = NULL;
				m_listBars.RemoveAt(pos2);
			}
		}
	}
	if(m_listBars.GetCount () == 0)
	{
		m_dwStyle &= ~WS_VISIBLE;
	}
	Invalidate ();
	GetParentFrame()->RecalcLayout();
}
void CAutoHideBar::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CControlBar::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

LRESULT CAutoHideBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MOUSELEAVE:
		if(m_pCurSelItem){
			m_pCurSelItem->m_wndFloat.m_bCursorInAutoHideBarItem=FALSE;
			m_pCurSelItem=NULL;
		}
		break;
	case WM_MOUSEHOVER:
	case WM_LBUTTONDOWN:
		{
			POSITION	pos;
			CHideItem*	pHideItem;

			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			for(pos=m_listBars.GetHeadPosition();pos!=NULL;)
			{
				pHideItem = (CHideItem*)m_listBars.GetNext(pos);
				if(NULL != pHideItem)
				{
					if(pHideItem->m_rect.PtInRect (point))
					{
						pHideItem->OnMouseMove (point);
						pHideItem->m_wndFloat.m_bCursorInAutoHideBarItem=TRUE;
						m_pCurSelItem=pHideItem;
					}else{
						pHideItem->m_wndFloat.m_bCursorInAutoHideBarItem=FALSE;
						m_pCurSelItem=NULL;
					}
				}
			}		
			Invalidate(FALSE);	
		}
		break;
	default:
		break;
	}
	return CControlBar::WindowProc(message, wParam, lParam);
}
 void CAutoHideBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
 {
 }
//CAutoHideBar implementation ends
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CAutoHideFrame

const DWORD dwHideBarMap[4][2] =
{
	{ AHBRS_TOP,      CBRS_TOP    },
	{ AHBRS_BOTTOM,   CBRS_BOTTOM },
	{ AHBRS_LEFT,     CBRS_LEFT   },
	{ AHBRS_RIGHT,    CBRS_RIGHT  },
};

IMPLEMENT_DYNCREATE(CAutoHideFrame, CFrameWnd)

CAutoHideFrame::CAutoHideFrame()
{
}

CAutoHideFrame::~CAutoHideFrame()
{

}

BEGIN_MESSAGE_MAP(CAutoHideFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CAutoHideFrame)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoHideFrame message handlers

void CAutoHideFrame::EnableDocking(DWORD dwDockStyle)
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	for (int i = 0; i < 4; i++)
	{
		if (dwHideBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
		{
			CAutoHideBar* pAutoHide = (CAutoHideBar*)GetControlBar(dwHideBarMap[i][0]);
			if (pAutoHide == NULL)
			{
				pAutoHide = new CAutoHideBar;
				if (!pAutoHide->Create(this,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
					dwHideBarMap[i][1], dwHideBarMap[i][0]))
				{
					AfxThrowResourceException();
				}
			}
		}
	}
	CFrameWnd::EnableDocking(dwDockStyle);
}
void CAutoHideFrame::OnDestroy()
{
	for (int i = 0; i < 4; i++)
	{
		CAutoHideBar* pAutoHide = (CAutoHideBar*)GetControlBar(dwHideBarMap[i][0]);
		if (pAutoHide != NULL)
		{
			pAutoHide->DestroyWindow();
			delete pAutoHide;
		}
	}
	CFrameWnd::OnDestroy();
}

void  CAutoHideFrame::GetPureClientRect(LPRECT lpRect)
{
	::GetWindowRect(((CFrameWnd*)this)->GetActiveView()->m_hWnd,lpRect);
}
void CAutoHideFrame::BringClientWindowToBottom()
{
	CWnd *pWnd=GetActiveView();
	pWnd->SetWindowPos(&CWnd::wndBottom ,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
}

//////////////////////////////////////////////////////////////////////////
//CMDIAutoHideFrame Implementation starts
IMPLEMENT_DYNCREATE(CMDIAutoHideFrame, CMDIFrameWnd)

CMDIAutoHideFrame::CMDIAutoHideFrame()
{
}

CMDIAutoHideFrame::~CMDIAutoHideFrame()
{

}


BEGIN_MESSAGE_MAP(CMDIAutoHideFrame,CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMDIAutoHideFrame)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIAutoHideFrame message handlers

void CMDIAutoHideFrame::EnableDocking(DWORD dwDockStyle)
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	for (int i = 0; i < 4; i++)
	{
		if (dwHideBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
		{
			CAutoHideBar* pAutoHide = (CAutoHideBar*)GetControlBar(dwHideBarMap[i][0]);
			if (pAutoHide == NULL)
			{
				pAutoHide = new CAutoHideBar;
				if (!pAutoHide->Create(this,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
					dwHideBarMap[i][1], dwHideBarMap[i][0]))
				{
					AfxThrowResourceException();
				}
			}
		}
	}
	CMDIFrameWnd::EnableDocking(dwDockStyle);
}

void  CMDIAutoHideFrame::GetPureClientRect(LPRECT lpRect)
{
	::GetWindowRect(((CMDIFrameWnd*)this)->m_hWndMDIClient,lpRect);
}

void CMDIAutoHideFrame::BringClientWindowToBottom()
{
	CWnd *pWnd=CWnd::FromHandle(m_hWndMDIClient);
	pWnd->SetWindowPos(&CWnd::wndBottom ,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
}

void CMDIAutoHideFrame::OnDestroy()
{
	for (int i = 0; i < 4; i++)
	{
		CAutoHideBar* pAutoHide = (CAutoHideBar*)GetControlBar(dwHideBarMap[i][0]);
		if (pAutoHide != NULL)
		{
			pAutoHide->DestroyWindow();
			delete pAutoHide;
		}
	}
	CMDIFrameWnd::OnDestroy();
}
//////////////////////////////////////////////////////////////////////////
//CMDIAutoHideFrame implementation ends