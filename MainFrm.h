// MainFrm.h : interface of the CMainFrame class
//



#pragma once

#include "./src/AutoHideBar.h"
#include "DockingBar.h"
#include "MyStatusBar.h"


//class CMainFrame : public CMDIFrameWnd
class CMainFrame : public CMDIAutoHideFrame
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHardwaresettings();

protected:


public:
	afx_msg void OnHardwareLasercontrol();
	afx_msg void OnHardwareWorkingmode();
	afx_msg void OnHardwareParametersettings();
	afx_msg void OnOperationDraw();
	CMyStatusBar	m_wndStatusBar;
protected:  // control bar embedded members

	CToolBar		m_wndToolBar;

	//CTreeCtrl		m_wndTree;
	CDockingBar		m_wndDockPageBar;

	//CEdit			m_wndEdit;
	//CDockingBar		m_wndDockPageBar1;
	CPtrList        m_dlgList;
};


