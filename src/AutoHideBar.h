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
/////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOHIDEBAR_H__FD8E1698_F985_4904_8249_4D92F37ECF80__INCLUDED_)
#define AFX_AUTOHIDEBAR_H__FD8E1698_F985_4904_8249_4D92F37ECF80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoHideBar.h : header file
//

#include "DockPageBar.h"


#define TID_AUTO_HIDE_DELAY 100
#define TID_SLIDE_IN		0x01
#define TID_SLIDE_OUT		0x02

#define AUTO_HIDE_DELAY_TIMES 400

#define SLIDE_HIDE         0x0100
#define SLIDE_SHOW         0x0000

#define GET_SLIDE_SHOW_HIDE(a)  (a&0xFF00)
#define GET_SLIDE_IN_OUT(a)     (a&0x00FF)


#define ANIMATE_DISP_STEP  50
#define AUTO_HIDE_BAR_WIDTH 24

#define AHBRS_TOP		0xE82B
#define AHBRS_BOTTOM	0xE82C
#define AHBRS_LEFT		0xE82D
#define AHBRS_RIGHT		0xE82E

/////////////////////////////////////////////////////////////////////////////
// CAHFloatWnd window
class CHideItem;
class CHidePageItem;
class CAHFloatWnd : public CWnd
{
// Construction
public:
	CAHFloatWnd();

// Attributes
public:
	typedef struct ANIMATE_DISPLAY_PARAM{
		CRect rect;
		int slideStep;
		int slideStepCount;
		BOOL  bInAnimateDisplay;
		DWORD timerId;
	}ANIMATE_DISPLAY_PARAM;

	DWORD			m_dwStyle;
	CCloseButton	m_biHide;
	CStudButton		m_stud;
	CRect m_captionRect;
	BOOL m_bCursorInAutoHideBarItem;
	ANIMATE_DISPLAY_PARAM m_animDispParam;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAHFloatWnd)
	virtual ~CAHFloatWnd();
	//}}AFX_VIRTUAL

// Implementation
public:
	CHideItem* m_HideItem;
	CHidePageItem* m_activePageItem;
	void OnStudClick();
	CFont m_font;
	CString m_Title;
	BOOL m_isActive;
	BOOL IsHorzDocked(){ return m_dwStyle&CBRS_ORIENT_HORZ ? TRUE:FALSE;}
	void StartAnimateDisplay(DWORD dwFlag, DWORD dwTime=300);
	void DoSlideStep();

	// Generated message map functions
protected:
	typedef struct BORDER_WIDTH{
		int cx_left;
		int cx_right;
		int cy_top;
		int cy_bottom;
	}BORDER_WIDTH;
	void GetBorderWidths(DWORD dwStyle,BORDER_WIDTH & borderWidth);
	//{{AFX_MSG(CAHFloatWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////////
// CHidePageItem
class CHidePageItem : public CPageItem
{
public:
	BOOL	m_isActive;
	CRect   m_lastAHFloatWndRect;
public:
	CHidePageItem();
	virtual ~CHidePageItem();
	void Draw(CDC *pDC, BOOL bHorz);
};

/////////////////////////////////////////////////////////////////////////////////////
// CHideItem
class CHideItem  
{
public:
	CRect			m_rect;
	CDockPageBar*	m_pDockPageBar;
	CAHFloatWnd		m_wndFloat;
	CPtrArray		m_arrPags;
	CRect			m_oldWndRect;
	DWORD			m_dwStyle;
	int				m_nActivePage;
	CWnd*			m_pAutoHideBar;
public:
	void RemoveAll();
	void Dock();
	void Show(int nShow);
	BOOL OnMouseMove(CPoint pt);
	void UpDateSize(CDC* pDC, CRect* rect);
	void AddPageItem(CDockPageBar* pPageBar, CWnd* pWnd, DWORD dwStyle);
	CHidePageItem * GetActiveItem();
	CHideItem();
	virtual ~CHideItem();
	void Draw(CDC *pDC);

};

/////////////////////////////////////////////////////////////////////////////
// CAutoHideBar window

class CAutoHideBar : public CControlBar
{
// Construction
public:
	CAutoHideBar();

// Attributes
public:
	CPtrList		m_listBars;
	CSize			m_size;
	CFont			m_Font;
	CHideItem *		m_pCurSelItem;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoHideBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateBar();
	void GetClientRect(CRect* rect);
	void UpDateSize();
	void HidePageBar(CDockPageBar* pDockPageBar);
	void DrawItem(CDC* pDC);
	DWORD m_dwStyle;
	BOOL Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID);
	virtual ~CAutoHideBar();
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	// Generated message map functions
protected:
	//{{AFX_MSG(CAutoHideBar)
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
// CAutoHideFrame frame

class CAutoHideFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CAutoHideFrame)
protected:
	CAutoHideFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void EnableDocking(DWORD dwDockStyle);
	void GetPureClientRect(LPRECT lpRect);
	void BringClientWindowToBottom();
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoHideFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAutoHideFrame();

	// Generated message map functions
	//{{AFX_MSG(CAutoHideFrame)
	//afx_msg LRESULT OnAutoHideOn(WPARAM, LPARAM);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CMDIAutoHideFrame frame

class CMDIAutoHideFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CMDIAutoHideFrame)
protected:
	CMDIAutoHideFrame();           // protected constructor used by dynamic creation

	// Attributes
public:

	// Operations
public:
	void EnableDocking(DWORD dwDockStyle);
	void GetPureClientRect(LPRECT lpRect);
	void BringClientWindowToBottom();

protected:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoHideFrame)
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CMDIAutoHideFrame();

	// Generated message map functions
	//{{AFX_MSG(CAutoHideFrame)
	//afx_msg LRESULT OnAutoHideOn(WPARAM, LPARAM);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOHIDEBAR_H__FD8E1698_F985_4904_8249_4D92F37ECF80__INCLUDED_)
