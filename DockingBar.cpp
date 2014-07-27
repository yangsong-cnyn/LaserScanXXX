#include "StdAfx.h"
//#include "LaserScan.h"
#include "DockingBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDockingBar::CDockingBar(void)
{
}

CDockingBar::~CDockingBar(void)
{
}


BEGIN_MESSAGE_MAP(CDockingBar, CDockPageBar)
	//{{AFX_MSG_MAP(CTestBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestBar message handlers

int CDockingBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

CObject* CDockingBar::AddPage(CRuntimeClass *pClass, UINT nIDTemplate, LPCTSTR sText, UINT IconID)
{
	CDialog *pDlg = (CDialog*)pClass->CreateObject();
	if(pDlg != NULL)
	{
		if(pDlg->Create(nIDTemplate,this))
		{
			if(AddPage(pDlg, sText, IconID))
				return pDlg;
			else{
				delete pDlg;
				return NULL;
			}
		}
	}

	return NULL;
}
/*
#include "stdafx.h"
#include "CNCBar.h"
#include "TestBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBar

CTestBar::CTestBar()
{
}

CTestBar::~CTestBar()
{

}


BEGIN_MESSAGE_MAP(CTestBar, CDockPageBar)
	//{{AFX_MSG_MAP(CTestBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestBar message handlers

int CTestBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

CObject* CTestBar::AddPage(CRuntimeClass *pClass, UINT nIDTemplate, LPCTSTR sText, UINT IconID)
{
	CDialog *pDlg = (CDialog*)pClass->CreateObject();
	if(pDlg != NULL)
	{
		if(pDlg->Create(nIDTemplate,this))
		{
			if(AddPage(pDlg, sText, IconID))
				return pDlg;
			else{
				delete pDlg;
				return NULL;
			}
		}
	}

	return NULL;
}

*/