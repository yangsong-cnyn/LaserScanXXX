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
/////////////////////////////////////////////////////////////////////////
#include "sizecbar.h"
#include "AutoHideBar.h"

#if !defined(AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_)
#define AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DockPageBar.h : header file
//
#define HTSTUD				22
#define HTHIDE				23
#define HTGRIPPER           24
#define HTITEMBUTTON        25

#define HTNCCLIENT          26

#define CAPTION_HEIGHT      16
#define	ITEMBUTTON_HEIGHT	24

	
#define GET_MAIN_FRAME_PURE_CLIENT(a,b) if((a)->IsKindOf(RUNTIME_CLASS(CMDIAutoHideFrame)))				\
								          ((CMDIAutoHideFrame*)(a))->GetPureClientRect(b);				\
									    else if((a)->IsKindOf(RUNTIME_CLASS(CAutoHideFrame)))			\
										  ((CAutoHideFrame*)(a))->GetPureClientRect(b);

#define BRING_CLIENT_WINDOW_TO_BOTTOM(a) if((a)->IsKindOf(RUNTIME_CLASS(CAutoHideFrame)))				\
										   ((CAutoHideFrame*)(a))->BringClientWindowToBottom();			\
										  else if((a)->IsKindOf(RUNTIME_CLASS(CMDIAutoHideFrame)))		\
											((CMDIAutoHideFrame*)(a))->BringClientWindowToBottom();		\
///////////////////////////////////////////////////////////////////////////
//  标题栏按钮
class CMyButton
{
public:
    CMyButton();

    void Move(CPoint ptTo) {ptOrg = ptTo; };
    virtual CRect GetRect() { return CRect(ptOrg, CSize(13, 13)); };
    virtual void Paint(CDC* pDC, BOOL isActive);

    BOOL    bPushed;
    BOOL    bRaised;

protected:
    CPoint  ptOrg;
};
//关闭按钮
class CCloseButton : public CMyButton
{
public:
	virtual void Paint(CDC* pDC, BOOL isActive);
};
//图钉按钮
class CStudButton : public CMyButton
{
public:
	CStudButton();
	BOOL	bFloat;
	virtual void Paint(CDC* pDC, BOOL isActive);
};

///////////////////////////////////////////////////////////////////////////
//  标签页
class CPageItem
{
public:
	CWnd*		m_pWnd;			//窗口,可以为NULL
	CString		m_sText;		//文字
	HICON		m_hIcon;		//图标
	UINT		m_TabWidth;		//标签宽度
	CRect		m_rect;			//标签位置
	CPageItem() { m_pWnd = NULL; }
public:
	void Draw(CDC *pDC,BOOL bActive);
};

/////////////////////////////////////////////////////////////////////////////
// CDockPageBar control bar

#ifndef baseCDockPageBar
#define baseCDockPageBar CSizingControlBar
#endif

class CDockPageBar : public baseCDockPageBar
{
	DECLARE_DYNAMIC(CDockPageBar);
// Construction
public:
	CDockPageBar();

// Attributes
public:
	int m_cyGripper;
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockPageBar)
	virtual BOOL HasGripper() const;
	virtual void UpdateSize();
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual ~CDockPageBar();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPtrList		m_PageList;
	CPtrList		m_pDPBContext;	//hengai
	int				m_nActivePage;
	BOOL			m_isActive;

	void OnStudClick();
	void EnableDocking(DWORD dwDockStyle);
	BOOL AddPage(CDockPageBar* dockPageBar);
	BOOL AddPage(CPageItem *pPageItem);
	BOOL AddPage(CWnd *pWnd, LPCTSTR sText, UINT IconID);
	CPageItem*		GetPageItem(int nIndex);
	CPageItem* DeletePage();
	void DEFLECT_RECT_FOR_STATIC_LINK(CRect &rect);

	CSize & GetHorSize(){ return m_szHorz; }
	CSize & GetVerSize(){ return m_szVert; }

	// Generated message map functions
protected:
	CRect m_itemGroupRect;

	CString			m_Title;
	CCloseButton	m_biHide;
	CStudButton		m_stud;	
	CFont			m_font;

	void Move(CPoint pt);
	void CanDrag(CPoint pt);
	void StartDrag(CPoint pt);
	void SetActivePage(int nIndex);
	void UpdateWindow();

	void GetItemGroupRect(LPRECT lpRect);
	void GetCaptionRect(LPRECT lpRect);
	
	// implementation helpers
	virtual void NcCalcClient(LPRECT pRc, UINT nDockBarID);
	virtual void NcPaintGripper(CDC* pDC, CRect rcClient);	

	//{{AFX_MSG(CDockPageBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDockPageBarContext dockcontext
#ifndef LAYOUT_LTR
#define LAYOUT_LTR			0x00000000
#endif

class CDockPageBarContext : public CDockContext
{
public:
// Construction
	CDockPageBarContext(CControlBar* pBar) : CDockContext(pBar) 
	{
		m_curRect.left=m_curRect.right=0;
		m_curRect.top=m_curRect.bottom=0;
		m_bAdvancedDock=FALSE;
		m_endDragDockStruct.dwDockStyle=0;
		m_endDragDockStruct.pDockPageBar=NULL;
	}	
	
	typedef struct END_DRAG_DOCK_STRUCT
	{
		DWORD dwDockStyle;
		CDockPageBar* pDockPageBar;
	}END_DRAG_DOCK_STRUCT;

	BOOL			m_isMe;
	BOOL			m_isPage;
	CDockPageBar*	m_pTgDockPage;
	END_DRAG_DOCK_STRUCT m_endDragDockStruct;


	virtual ~CDockPageBarContext(void);
	void FreeAll();
// Drag Operations
	virtual void StartDrag(CPoint pt);
	virtual BOOL Track();
	virtual void Move(CPoint pt);
	virtual void EndDrag();
	void DrawFocusRect(BOOL bRemoveRect = FALSE);
protected:
	CPtrList m_pDPBar;	//hengai
	CRect	 m_addRect;
	CRect    m_curRect;
	BOOL     m_bAdvancedDock;

	CDockPageBar* CreateNewBar();
	BOOL isDockPage(CPoint pt);
	CDockPageBar * TryToGetDockPageBar(POINT pt);
};

#endif // !defined(AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_)
