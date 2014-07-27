// ParameterSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserScan.h"
#include "ParameterSettings.h"
#include "RTC5impl.hpp"
#include "LaserScanDoc.h"


// CParameterSettings 对话框

IMPLEMENT_DYNAMIC(CParameterSettings, CDialog)

CParameterSettings::CParameterSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterSettings::IDD, pParent)
	, m_LaserOnDelay(0)
	, m_LaserOffDelay(0)
	, m_JumpDelay(0)
	, m_MarkDelay(0)
	, m_PolygonDelay(0)
	, m_JumpSpeed(0)
	, m_MarkSpeed(0)
	, m_CalibrationFactor_KSpeed(8.320)
{

}

CParameterSettings::~CParameterSettings()
{
}

void CParameterSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_LaserOnDelay, m_LaserOnDelay);
	DDX_Text(pDX, IDC_EDIT2_LaserOffDelay, m_LaserOffDelay);
	DDX_Text(pDX, IDC_EDIT3_JumpDelay, m_JumpDelay);
	DDX_Text(pDX, IDC_EDIT4_MarkDelay, m_MarkDelay);
	DDX_Text(pDX, IDC_EDIT5_PolygonDelay, m_PolygonDelay);
	DDX_Text(pDX, IDC_EDIT6_JumpSpeed, m_JumpSpeed);
	DDX_Text(pDX, IDC_EDIT7_MarkSpeed, m_MarkSpeed);
}


BEGIN_MESSAGE_MAP(CParameterSettings, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CParameterSettings::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT6_JumpSpeed, &CParameterSettings::OnEnChangeJumpspeed)
	ON_EN_CHANGE(IDC_EDIT7_MarkSpeed, &CParameterSettings::OnEnChangeMarkspeed)
END_MESSAGE_MAP()


// CParameterSettings 消息处理程序

void CParameterSettings::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//speed,delay settings
	set_start_list( 1 ); 
    set_scanner_delays( m_JumpDelay, m_MarkDelay
		,m_PolygonDelay);
    set_laser_delays( m_LaserOnDelay, m_LaserOffDelay);
    set_jump_speed( m_JumpSpeed*m_CalibrationFactor_KSpeed);
	set_mark_speed( m_MarkSpeed*m_CalibrationFactor_KSpeed);
    set_end_of_list();
    execute_list( 1 );

	CLaserScanDoc::s_JumpSpeed=m_JumpSpeed;
	CLaserScanDoc::s_MarkSeepd=m_MarkSpeed;
	CLaserScanDoc::s_JumpSpeed_Iner=m_JumpSpeed*m_CalibrationFactor_KSpeed;
	CLaserScanDoc::s_MarkSeepd_Iner=m_MarkSpeed*m_CalibrationFactor_KSpeed;
	CLaserScanDoc::s_LaserOnDelay=m_LaserOnDelay;
	CLaserScanDoc::s_LaserOffDelay=m_LaserOffDelay;
	CLaserScanDoc::s_JumpDelay=m_JumpDelay;
	CLaserScanDoc::s_MarkDelay=m_MarkDelay;
	CLaserScanDoc::s_PolygonDelay=m_PolygonDelay;
	OnOK();
}

BOOL CParameterSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_CalibrationFactor_KSpeed=CLaserScanDoc::s_FactorSpeed;
	m_JumpSpeed= CLaserScanDoc::s_JumpSpeed;
	m_MarkSpeed= CLaserScanDoc::s_MarkSeepd;
	m_LaserOnDelay= CLaserScanDoc::s_LaserOnDelay;
	m_LaserOffDelay= CLaserScanDoc::s_LaserOffDelay;
	m_JumpDelay= CLaserScanDoc::s_JumpDelay;
	m_MarkDelay= CLaserScanDoc::s_MarkDelay;
	m_PolygonDelay= CLaserScanDoc::s_PolygonDelay;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CParameterSettings::OnEnChangeJumpspeed()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
}

void CParameterSettings::OnEnChangeMarkspeed()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
