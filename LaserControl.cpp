// LaserControl.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "LaserControl.h"
#include "LaserScanDoc.h"
#include "RTC5impl.hpp"


// CLaserControl dialog

IMPLEMENT_DYNAMIC(CLaserControl, CDialog)

CLaserControl::CLaserControl(CWnd* pParent /*=NULL*/)
	: CDialog(CLaserControl::IDD, pParent)
{

}

CLaserControl::~CLaserControl()
{
}

void CLaserControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_LaserControl, m_Tree_LaserControl);
}


BEGIN_MESSAGE_MAP(CLaserControl, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_LaserControl, &CLaserControl::OnTvnSelchangedTreeLasercontrol)
	ON_BN_CLICKED(IDC_LaserControl_Accept, &CLaserControl::OnLasercontrolAccept)
	ON_BN_CLICKED(IDC_LaserControl_Exit, &CLaserControl::OnLasercontrolExit)
END_MESSAGE_MAP()


// CLaserControl message handlers

BOOL CLaserControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Tree_LaserControl.DeleteAllItems();
	HTREEITEM t_LaserControl=m_Tree_LaserControl.InsertItem(_T("Laser Settings"));
	HTREEITEM t_LaserControl_Settings=m_Tree_LaserControl.InsertItem(_T("Laser Settings"),t_LaserControl);
	HTREEITEM t_LaserControl_Status=m_Tree_LaserControl.InsertItem(_T("Laser Status"),t_LaserControl);

	m_Tree_LaserControl.Expand(t_LaserControl,TVE_EXPAND);

	m_LaserControl_Settings.Create(IDD_LaserControl_Settings,this);
	m_LaserControl_Status.Create(IDD_LaserControl_Status,this);

	CRect r;
	GetDlgItem(IDC_STATIC_LaserControl)->GetWindowRect(r);
	ScreenToClient(r);

	m_LaserControl_Settings.MoveWindow(r);
	m_LaserControl_Status.MoveWindow(r);

	m_LaserControl_Settings.ShowWindow(SW_HIDE);
	m_LaserControl_Status.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLaserControl::OnTvnSelchangedTreeLasercontrol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	TVITEM item=pNMTreeView->itemNew;
	CString str=m_Tree_LaserControl.GetItemText(item.hItem);
	if(str.Compare(_T("Laser Settings"))==0)
	{
		//if(m_LaserControl_Status.m_Com.get_PortOpen())
		//	m_LaserControl_Settings.m_Com.put_PortOpen(FALSE);

		//if (CLaserScanDoc::s_SerialPort_Open==TRUE)
		//{
		//	m_LaserControl_Status.m_Com.put_PortOpen(FALSE);
		//}
		if(m_LaserControl_Status.m_Com.get_PortOpen())
			m_LaserControl_Status.m_Com.put_PortOpen(FALSE);
		m_LaserControl_Settings.ShowWindow(SW_SHOW);
		m_LaserControl_Status.ShowWindow(SW_HIDE);		
	}
	else if(str.Compare(_T("Laser Status"))==0)
	{
		m_LaserControl_Settings.ShowWindow(SW_HIDE);
		m_LaserControl_Status.ShowWindow(SW_SHOW);

		m_LaserControl_Status.SetTimer(1,100,NULL);  //action

		//if (CLaserScanDoc::s_SerialPort_Open==TRUE)
		//{
		//	m_LaserControl_Settings.m_Com.put_PortOpen(FALSE);
		//}

		if(m_LaserControl_Settings.m_Com.get_PortOpen())
			m_LaserControl_Settings.m_Com.put_PortOpen(FALSE);

	}
	*pResult = 0;
}

void CLaserControl::OnLasercontrolAccept()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	m_LaserControl_Settings.UpdateData(TRUE);
	//m_LaserControl_Settings.m_nIndex=2;

	m_LaserControl_Settings.SetTimer(1,100,NULL);

	set_laser_mode(m_LaserControl_Settings.m_LaserMode);
	switch(m_LaserControl_Settings.m_LaserMode)
	{
	case 0:
		set_standby(m_LaserControl_Settings.m_StandbyHalfPeriod,m_LaserControl_Settings.m_StanbyPulseLength);
		//set_standby(106,106);
		set_laser_pulses_ctrl(m_LaserControl_Settings.m_HalfPeriod,m_LaserControl_Settings.m_PulseLengthSignal);
		break;
	case 1:
	case 2:
	case 3:
	case 5:
		set_firstpulse_killer(m_LaserControl_Settings.m_FirstPulseKillerLengthSignal);
		set_qswitch_delay(m_LaserControl_Settings.m_QSwtchDelaySignal);
		break;
	default:
		break;
	}
//Update data
	m_LaserControl_Settings.UpdateData(TRUE);
	//laser
	CLaserScanDoc::s_LaserPower=m_LaserControl_Settings.m_LaserPower;
	CLaserScanDoc::s_LaserSetpoint=m_LaserControl_Settings.m_LaserSetpoint;
	CLaserScanDoc::s_Frequency=m_LaserControl_Settings.m_Frequency;
	//serial Port
	CLaserScanDoc::s_SerialPort_Number=m_LaserControl_Settings.m_SerialPort_Number;
	//CString CLaserScanDoc::s_SerialPort_Parameters=m_SerialPort_Parameters;
	CLaserScanDoc::s_nInputMode=m_LaserControl_Settings.m_nInputMode;
	//scan head output and input
	//CLaserScanDoc::s_LaserMode=m_LaserControl_Settings.m_LaserMode;
	CLaserScanDoc::s_HalfPeriod=m_LaserControl_Settings.m_HalfPeriod;
	CLaserScanDoc::s_FrequencySignal=m_LaserControl_Settings.m_FrequencySignal;
	CLaserScanDoc::s_PulseLengthSignal=m_LaserControl_Settings.m_PulseLengthSignal;
	CLaserScanDoc::s_FirstPulseKillerLengthSignal=m_LaserControl_Settings.m_FirstPulseKillerLengthSignal;
	CLaserScanDoc::s_QSwtchDelaySignal=m_LaserControl_Settings.m_QSwtchDelaySignal;
	//standby
	CLaserScanDoc::s_StandbyHalfPeriod=m_LaserControl_Settings.m_StandbyHalfPeriod;
	CLaserScanDoc::s_StandbyFrequency=m_LaserControl_Settings.m_StandbyFrequency;
	CLaserScanDoc::s_StanbyPulseLength=m_LaserControl_Settings.m_StanbyPulseLength;
	//CDialog::OnOK();
}

void CLaserControl::OnLasercontrolExit()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
