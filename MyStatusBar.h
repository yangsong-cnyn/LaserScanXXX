#if !defined(AFX_MYSTATUSBAR_H__2E633D8E_E76E_4B52_BD82_75184C07796D__INCLUDED_)
#define AFX_MYSTATUSBAR_H__2E633D8E_E76E_4B52_BD82_75184C07796D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar window

class CMyStatusBar : public CStatusBar
{
// Construction
public:
	CMyStatusBar();
	BOOL SetIndicators (const UINT* lpIDArray, int nIDCount);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatusBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATUSBAR_H__2E633D8E_E76E_4B52_BD82_75184C07796D__INCLUDED_)
