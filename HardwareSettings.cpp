// HardwareSettings.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "HardwareSettings.h"


// CHardwareSettings dialog

IMPLEMENT_DYNAMIC(CHardwareSettings, CDialog)

CHardwareSettings::CHardwareSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CHardwareSettings::IDD, pParent)
{

}

CHardwareSettings::~CHardwareSettings()
{
}

void CHardwareSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_Hardware, m_Tree_Hardware);
}


BEGIN_MESSAGE_MAP(CHardwareSettings, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_Hardware, &CHardwareSettings::OnTvnSelchangedTreeHardware)
END_MESSAGE_MAP()


// CHardwareSettings message handlers

BOOL CHardwareSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//display
	/*m_Tree_Hardware.DeleteAllItems();
	m_Tree_Hardware.InsertItem(_T("Initialization"));
	m_Tree_Hardware.InsertItem(_T("Optics"));*/


	/*HTREEITEM m_hParent = m_Tree_Hardware.InsertItem(_T("Hardware Setting"),TVI_ROOT);
	HTREEITEM m_hChild1 = m_Tree_Hardware.InsertItem(_T("ScanHead status"),m_hParent,TVI_LAST);
	HTREEITEM m_hChild2 = m_Tree_Hardware.InsertItem(_T("Initialization"),m_hParent,TVI_LAST);
	HTREEITEM m_hChild3 = m_Tree_Hardware.InsertItem(_T("Optics"),m_hParent,TVI_LAST);

	Tree.SetItemData(m_hParent,0);
	Tree.SetItemData(m_hChild1,1);
	Tree.SetItemData(m_hChild2,2);*/


	m_Tree_Hardware.DeleteAllItems();
	HTREEITEM t_HardwareSettings=m_Tree_Hardware.InsertItem(_T("Hardware Settings"));
	HTREEITEM t_Initialization=m_Tree_Hardware.InsertItem(_T("Initialization"),t_HardwareSettings);
	HTREEITEM t_ScanHead=m_Tree_Hardware.InsertItem(_T("ScanHead status"),t_HardwareSettings);
	HTREEITEM t_Optics=m_Tree_Hardware.InsertItem(_T("Optics"),t_HardwareSettings);

	m_Tree_Hardware.Expand(t_HardwareSettings,TVE_EXPAND);


	m_Initialization.Create(IDD_Initialization,this);
	m_Optics.Create(IDD_Optics,this);
	m_ScanHead.Create(IDD_HardwareSettings_ScanHead,this);

	CRect r;
	GetDlgItem(IDC_STATIC_Hardware)->GetWindowRect(r);
	ScreenToClient(r);

	m_Initialization.MoveWindow(r);
	m_Optics.MoveWindow(r);
	m_ScanHead.MoveWindow(r);

	m_Initialization.ShowWindow(SW_HIDE);
	m_Optics.ShowWindow(SW_HIDE);
	m_ScanHead.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CHardwareSettings::OnTvnSelchangedTreeHardware(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	TVITEM item=pNMTreeView->itemNew;
	CString str=m_Tree_Hardware.GetItemText(item.hItem);
	if(str.Compare(_T("Initialization"))==0)
	{
		m_Initialization.ShowWindow(SW_SHOW);
	    m_Optics.ShowWindow(SW_HIDE);
		m_ScanHead.ShowWindow(SW_HIDE);
	}
	else if(str.Compare(_T("Optics"))==0)
	{
	    m_Initialization.ShowWindow(SW_HIDE);
	    m_Optics.ShowWindow(SW_SHOW);
		m_ScanHead.ShowWindow(SW_HIDE);
	}
	else if (str.Compare(_T("ScanHead status"))==0)
	{
		m_Initialization.ShowWindow(SW_HIDE);
		m_Optics.ShowWindow(SW_HIDE);
		m_ScanHead.ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}


