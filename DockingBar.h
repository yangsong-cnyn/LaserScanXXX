#pragma once
#include ".\src\dockpagebar.h"

class CDockingBar : public CDockPageBar
{
//construction
public:
	CDockingBar(void);
	using CDockPageBar::AddPage;
	virtual ~CDockingBar(void);

// Implementation
public:
	CObject * AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID);


	// Generated message map functions
protected:
	//{{AFX_MSG(CTestBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
class CTestBar : public CDockPageBar
{
// Construction
public:
	CTestBar();
	using CDockPageBar::AddPage;
// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	CObject * AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID);
	virtual ~CTestBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

*/