// Hardware_Initialization.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Hardware_Initialization.h"
#include "RTC5impl.hpp"
#include "LaserScanDoc.h"

// CHardware_Initialization dialog

IMPLEMENT_DYNAMIC(CHardware_Initialization, CDialog)

CHardware_Initialization::CHardware_Initialization(CWnd* pParent /*=NULL*/)
	: CDialog(CHardware_Initialization::IDD, pParent)
	, m_Description(_T(""))
{

}

CHardware_Initialization::~CHardware_Initialization()
{
}

void CHardware_Initialization::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_Initial_bit0);
	DDX_Control(pDX, IDC_RADIO2, m_Initial_bit1);
	DDX_Control(pDX, IDC_RADIO3, m_Initial_bit2);
	DDX_Control(pDX, IDC_RADIO4, m_Initial_bit3);
	DDX_Control(pDX, IDC_RADIO5, m_Initial_bit4);
	DDX_Control(pDX, IDC_RADIO6, m_Initial_bit8);
	DDX_Control(pDX, IDC_RADIO7, m_Initial_bit9);
	DDX_Control(pDX, IDC_RADIO8, m_Initial_bit10);
	DDX_Text(pDX, IDC_STATIC_Description, m_Description);
}


BEGIN_MESSAGE_MAP(CHardware_Initialization, CDialog)
END_MESSAGE_MAP()


// CHardware_Initialization message handlers

BOOL CHardware_Initialization::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	set_start_list(1);
	UINT Error=get_error();
	set_end_of_list();
	CLaserScanDoc::s_GetError=Error;
	execute_list(1);
	UINT bit;
	m_Description="";
	bit=Error % 2;
	m_Initial_bit0.SetCheck(bit);
	if (bit) m_Description +="-no board found\n\n";
	Error=Error / 2;
	
	bit=Error % 2;
	m_Initial_bit1.SetCheck(bit);
	if (bit) m_Description +="-access denied \n\n";
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit2.SetCheck(bit);
	if (bit) m_Description +="-command not found \n\n";
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit3.SetCheck(bit);
	if (bit) m_Description +="-no response from board \n\n";
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit4.SetCheck(bit);
	if (bit) m_Description +="-invalid parameter \n\n";
	Error=Error / 2;
	
	bit=Error % 2;
	Error=Error / 2;

	bit=Error % 2;
	Error=Error / 2;

	bit=Error % 2;
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit8.SetCheck(bit);
	if (bit) m_Description +="-Version error \n\n";
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit9.SetCheck(bit);
	if (bit) m_Description +="-Verify error\n\n";
	Error=Error / 2;

	bit=Error % 2;
	m_Initial_bit10.SetCheck(bit);
	if (bit) m_Description +="-DSP version error %d";
	Error=Error / 2;

	UpdateData(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
