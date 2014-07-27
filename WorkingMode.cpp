// WorkingMode.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "WorkingMode.h"
#include "RTC5impl.hpp"
#include "LaserScanDoc.h"


// CWorkingMode dialog

IMPLEMENT_DYNAMIC(CWorkingMode, CDialog)

CWorkingMode::CWorkingMode(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkingMode::IDD, pParent)
{

}

CWorkingMode::~CWorkingMode()
{
}

void CWorkingMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_WorkingMode, m_tree_Working);
}


BEGIN_MESSAGE_MAP(CWorkingMode, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_WorkingMode, &CWorkingMode::OnTvnSelchangedTreeWorkingmode)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkingMode::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWorkingMode message handlers

BOOL CWorkingMode::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	HTREEITEM hItem, hSubItem;
	hItem = m_tree_Working.InsertItem(_T("Select Working Mode"), TVI_ROOT);
	hSubItem = m_tree_Working.InsertItem(_T("Wobbel Motion"), hItem);
	hSubItem = m_tree_Working.InsertItem(_T("Processing-on-the-fly"), hItem, hSubItem);
	hSubItem = m_tree_Working.InsertItem(_T("Automatic Self-Calibration"), hItem, hSubItem);
	m_tree_Working.Expand(hItem,TVE_EXPAND);

	m_Wobbel.Create(IDD_Wobbel, this);
	m_Processing.Create(IDD_Processing, this);
	m_Automatic.Create(IDD_Automatic, this);

	CRect r;
	GetDlgItem(IDC_STATIC_WorkingMode)->GetWindowRect(r);
	ScreenToClient(r);
	GetDlgItem(IDC_STATIC_WorkingMode)->DestroyWindow();
	m_Wobbel.MoveWindow(r);
	m_Processing.MoveWindow(r);
	m_Automatic.MoveWindow(r);
	m_Wobbel.ShowWindow(SW_HIDE);
	m_Processing.ShowWindow(SW_HIDE);
	m_Automatic.ShowWindow(SW_HIDE);

	m_Wobbel.transversal=CLaserScanDoc::s_transversal;
	m_Wobbel.longitudinal=CLaserScanDoc::s_longitudinal;
	m_Wobbel.freq=CLaserScanDoc::s_freq;
	m_Wobbel.mode=CLaserScanDoc::s_mode;
	m_Wobbel.UpdateData(FALSE);
	m_Processing.scalex=CLaserScanDoc::s_scalex;
	m_Processing.scaley=CLaserScanDoc::s_scaley;
	m_Processing.rot_x=CLaserScanDoc::s_rot_x;
	m_Processing.rot_y=CLaserScanDoc::s_rot_y;
	m_Processing.resolution=CLaserScanDoc::s_resolution;
	m_Processing.ret_x=CLaserScanDoc::s_ret_x;
	m_Processing.ret_y=CLaserScanDoc::s_ret_y;
	m_Processing.func=CLaserScanDoc::s_func_p;
	m_Processing.UpdateData(FALSE);
	m_Automatic.headNo=CLaserScanDoc::s_headNo;
	m_Automatic.command=CLaserScanDoc::s_command;
	m_Automatic.gainX=CLaserScanDoc::s_gainX;
	m_Automatic.gainY=CLaserScanDoc::s_gainY;
	m_Automatic.offsetX=CLaserScanDoc::s_offsetX;
	m_Automatic.offsetY=CLaserScanDoc::s_offsetY;
	m_Automatic.Ecode=CLaserScanDoc::s_Ecode;
	m_Automatic.func=CLaserScanDoc::s_func_a;
	m_Automatic.UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWorkingMode::OnTvnSelchangedTreeWorkingmode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_tree_Working.GetSelectedItem();
	CString str = m_tree_Working.GetItemText(hItem);

	if (str.Compare(_T("Wobbel Motion")) == 0)
	{
		m_Wobbel.ShowWindow(SW_SHOW);
		m_Processing.ShowWindow(SW_HIDE);
		m_Automatic.ShowWindow(SW_HIDE);

		m_Wobbel.UpdateData();
		//m_Wobbel.transversal=CLaserScanDoc::s_transversal;
		//m_Wobbel.longitudinal=CLaserScanDoc::s_longitudinal;
		//m_Wobbel.freq=CLaserScanDoc::s_freq;
		//m_Wobbel.mode=CLaserScanDoc::s_mode;
		//m_Wobbel.UpdateData(FALSE);
	}
	else if (str.Compare(_T("Processing-on-the-fly")) == 0)
	{
		m_Wobbel.ShowWindow(SW_HIDE);
		m_Processing.ShowWindow(SW_SHOW);
		m_Automatic.ShowWindow(SW_HIDE);

		m_Processing.UpdateData();
		//m_Processing.scalex=CLaserScanDoc::s_scalex;
		//m_Processing.scaley=CLaserScanDoc::s_scaley;
		//m_Processing.rot_x=CLaserScanDoc::s_rot_x;
		//m_Processing.rot_y=CLaserScanDoc::s_rot_y;
		//m_Processing.resolution=CLaserScanDoc::s_resolution;
		//m_Processing.ret_x=CLaserScanDoc::s_ret_x;
		//m_Processing.ret_y=CLaserScanDoc::s_ret_y;
		//m_Processing.func=CLaserScanDoc::s_func_p;
		//m_Processing.UpdateData(FALSE);
	}
	else if (str.Compare(_T("Automatic Self-Calibration")) == 0)
	{
		m_Wobbel.ShowWindow(SW_HIDE);
		m_Processing.ShowWindow(SW_HIDE);
		m_Automatic.ShowWindow(SW_SHOW);

		m_Automatic.UpdateData();
		//m_Automatic.headNo=CLaserScanDoc::s_headNo;
		//m_Automatic.command=CLaserScanDoc::s_command;
		//m_Automatic.gainX=CLaserScanDoc::s_gainX;
		//m_Automatic.gainY=CLaserScanDoc::s_gainY;
		//m_Automatic.offsetX=CLaserScanDoc::s_offsetX;
		//m_Automatic.offsetY=CLaserScanDoc::s_offsetY;
		//m_Automatic.Ecode=CLaserScanDoc::s_Ecode;
		//m_Automatic.func=CLaserScanDoc::s_func_a;
		//m_Automatic.UpdateData(FALSE);
	}
	else
	{
		m_Wobbel.ShowWindow(SW_HIDE);
		m_Processing.ShowWindow(SW_HIDE);
		m_Automatic.ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}

void CWorkingMode::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_tree_Working.GetSelectedItem();
	CString str = m_tree_Working.GetItemText(hItem);
	if (str.Compare(_T("Wobbel Motion")) == 0)
	{
		m_Wobbel.UpdateData();
		set_start_list(1);
		set_wobbel_mode(m_Wobbel.transversal, m_Wobbel.longitudinal, m_Wobbel.freq, m_Wobbel.mode);
		set_end_of_list();
		execute_list(1);
		m_Wobbel.UpdateData(false);
	}
	else if (str.Compare(_T("Processing-on-the-fly")) == 0)
	{
		m_Processing.UpdateData();
		set_start_list(1);
		if (m_Processing.func == 0)
		{
			set_fly_x(m_Processing.scalex);
			set_fly_y(m_Processing.scaley);
		}
		else if (m_Processing.func == 1)
		{
			set_rot_center(m_Processing.rot_x, m_Processing.rot_y);
			set_fly_rot(m_Processing.resolution);
		}
		else if (m_Processing.func == 2)
		{
			fly_return(m_Processing.ret_x, m_Processing.ret_y);
		}
		else
		{
			MessageBox(_T("ERROR!"));
		}
		set_end_of_list();
		execute_list(1);
		m_Processing.UpdateData(false);
	}
	else if (str.Compare(_T("Automatic Self-Calibration")) == 0)
	{
		m_Automatic.UpdateData();
		set_start_list(1);
		if (m_Automatic.func == 0)
		{
			UINT ErrorCode = auto_cal(m_Automatic.headNo, m_Automatic.command);
			m_Automatic.Ecode = ErrorCode;		
		}
		else if (m_Automatic.func == 1)
		{
			set_hi(m_Automatic.headNo, m_Automatic.gainX, m_Automatic.gainY, m_Automatic.offsetX, m_Automatic.offsetY);
		}
		set_end_of_list();
		execute_list(1);
		m_Automatic.UpdateData(false);
	}
	m_Wobbel.UpdateData();
	CLaserScanDoc::s_transversal=m_Wobbel.transversal;
	CLaserScanDoc::s_longitudinal=m_Wobbel.longitudinal;
	CLaserScanDoc::s_freq=m_Wobbel.freq;
	CLaserScanDoc::s_mode=m_Wobbel.mode;
	m_Processing.UpdateData();
	CLaserScanDoc::s_scalex=m_Processing.scalex;
	CLaserScanDoc::s_scaley=m_Processing.scaley;
	CLaserScanDoc::s_rot_x=m_Processing.rot_x;
	CLaserScanDoc::s_rot_y=m_Processing.rot_y;
	CLaserScanDoc::s_resolution=m_Processing.resolution;
	CLaserScanDoc::s_ret_x=m_Processing.ret_x;
	CLaserScanDoc::s_ret_y=m_Processing.ret_y;
	CLaserScanDoc::s_func_p=m_Processing.func;
	//m_Automatic
	m_Automatic.UpdateData();
	CLaserScanDoc::s_headNo=m_Automatic.headNo;
	CLaserScanDoc::s_command=m_Automatic.command;
	CLaserScanDoc::s_gainX=m_Automatic.gainX;
	CLaserScanDoc::s_gainY=m_Automatic.gainY;
	CLaserScanDoc::s_offsetX=m_Automatic.offsetX;
	CLaserScanDoc::s_offsetY=m_Automatic.offsetY;
	CLaserScanDoc::s_Ecode=m_Automatic.Ecode;
	CLaserScanDoc::s_func_a=m_Automatic.func;
}
