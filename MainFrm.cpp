// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LaserScan.h"
#include "LaserControl.h"
#include "HardwareSettings.h"
#include "WorkingMode.h"
#include "ParameterSettings.h"
#include "MainFrm.h"
#include "Draw.h"
#include "Bar_ParameterSettings.h"
#include "Bar_LaserControl_Settings.h"
#include "Bar_CNC2000.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMDIAutoHideFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIAutoHideFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HARDWARE_HARDWARESETTINGS, &CMainFrame::OnHardwaresettings)
	ON_COMMAND(ID_HARDWARE_LASERCONTROL, &CMainFrame::OnHardwareLasercontrol)
	ON_COMMAND(ID_HARDWARE_WORKINGMODE, &CMainFrame::OnHardwareWorkingmode)
	ON_COMMAND(ID_HARDWARE_PARAMETERSETTINGS, &CMainFrame::OnHardwareParametersettings)
	ON_COMMAND(ID_OPERATION_DRAW, &CMainFrame::OnOperationDraw)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

//autohidebar
	if (!m_wndDockPageBar.Create(_T("DockPageBar"), this, CSize(330,260),TRUE,123))
	{
		TRACE0("Failed to create DockPageBar.\n");
			return -1;
	}
	m_wndDockPageBar.SetBarStyle(m_wndDockPageBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndDockPageBar.EnableDocking (CBRS_ALIGN_ANY);

	//if (!m_wndDockPageBar1.Create(_T("DockPageBar"), this, CSize(230,260),TRUE,1234))
	//{
	//	TRACE0("Failed to create DockPageBar.\n");
	//		return -1;
	//}
	//m_wndDockPageBar1.SetBarStyle(m_wndDockPageBar1.GetBarStyle() |
	//	CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	//m_wndDockPageBar1.EnableDocking (CBRS_ALIGN_ANY);


	//// TODO: Delete these three lines if you don't want the toolbar to
	////  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndDockPageBar, AFX_IDW_DOCKBAR_LEFT);
	//DockControlBar(&m_wndDockPageBar1, AFX_IDW_DOCKBAR_RIGHT);

	//if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
	//	TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
	//	CRect(0, 0, 0, 0), this, 100))
	//{
	//	TRACE0("Failed to create instant bar child\n");
	//	return -1;
	//}

	//HTREEITEM hti = m_wndTree.InsertItem(_T("Welcome to the VCKbase"));
	//m_wndTree.InsertItem(_T("Visual c++"), hti);
	//m_wndTree.InsertItem(_T("C++论坛"), hti);
	//m_wndTree.InsertItem(_T(".NET论坛"), hti);
	//m_wndTree.InsertItem(_T("C++ Builder"), hti);
	//m_wndTree.InsertItem(_T("Java"), hti);
	//m_wndTree.InsertItem(_T("软件工程"), hti);
	//m_wndTree.InsertItem(_T("灌水乐园"), hti);
	//
	//if (!m_wndEdit.Create(WS_CHILD|WS_VISIBLE|
	//	ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL,
	//	CRect(0,0,0,0), this, 123))
	//	return -1;	


	//The new created dialog by m_wndDockPageBar.AddPage will be released by Mainframe 
	//m_wndDockPageBar.AddPage(&m_wndTree,_T("Contents"),IDI_HELP);
 m_dlgList.AddTail(m_wndDockPageBar.AddPage(RUNTIME_CLASS(CBar_CNC2000), IDD_Bar_CNC, _T("CNC2000"), IDI_CNC2000));
	m_dlgList.AddTail(m_wndDockPageBar.AddPage(RUNTIME_CLASS(CBar_ParameterSettings), IDD_Bar_ParameterSettings, _T("Parameter"), IDI_Para));
    m_dlgList.AddTail(m_wndDockPageBar.AddPage(RUNTIME_CLASS(CBar_LaserControl_Settings), IDD_Bar_LaserControl_Settings, _T("Laser"), IDI_LaserControl));
	//m_wndDockPageBar.AddPage(&m_wndEdit,_T("Edit"),IDI_INDEX);
//dock
	//m_dlgList.AddTail(m_wndDockPageBar1.AddPage(RUNTIME_CLASS(CLaserScan_ParameterSettings), IDD_ParameterSettings, _T("ParameterSettings"), IDI_Para));

	//m_dlgList.AddTail(m_wndDockPageBar1.AddPage (RUNTIME_CLASS(CSearchResult), IDD_SEARCHRESULT, _T("Search Result"), IDI_SEARCHRESULT));

	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




void CMainFrame::OnHardwaresettings()
{
	// TODO: Add your command handler code here
	CHardwareSettings HardwareSettings;
	HardwareSettings.DoModal();
}

void CMainFrame::OnHardwareLasercontrol()
{
	// TODO: Add your command handler code here
	CLaserControl LaserControl;
	LaserControl.DoModal();
}

void CMainFrame::OnHardwareWorkingmode()
{
	// TODO: Add your command handler code here
	CWorkingMode WorkingMode;
	WorkingMode.DoModal();
}

void CMainFrame::OnHardwareParametersettings()
{
	// TODO: 在此添加命令处理程序代码
	CParameterSettings ParameterSettings;
	ParameterSettings.DoModal();
}

void CMainFrame::OnOperationDraw()
{
	// TODO: Add your command handler code here
	CDraw Draw;
	Draw.DoModal();
}
