// HardwareSetting_ScanHead.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserScan.h"
#include "HardwareSetting_ScanHead.h"
#include "RTC5impl.hpp"
#include "LaserScanDoc.h"


// CHardwareSetting_ScanHead 对话框

IMPLEMENT_DYNAMIC(CHardwareSetting_ScanHead, CDialog)

CHardwareSetting_ScanHead::CHardwareSetting_ScanHead(CWnd* pParent /*=NULL*/)
	: CDialog(CHardwareSetting_ScanHead::IDD, pParent)
	
	, ScanHead_bit3(_T(""))
	, ScanHead_bit4(_T(""))
	, ScanHead_bit6(_T(""))
	, ScanHead_bit7(_T(""))
{

}

CHardwareSetting_ScanHead::~CHardwareSetting_ScanHead()
{
}

void CHardwareSetting_ScanHead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Text(pDX, IDC_STATIC_Px_Error, ScanHead_bit3);
	DDX_Text(pDX, IDC_STATIC_Py_Error, ScanHead_bit4);
	DDX_Text(pDX, IDC_STATIC_Ts_Error, ScanHead_bit6);
	DDX_Text(pDX, IDC_STATIC_Ps_Error, ScanHead_bit7);
}


BEGIN_MESSAGE_MAP(CHardwareSetting_ScanHead, CDialog)
END_MESSAGE_MAP()


// CHardwareSetting_ScanHead 消息处理程序

BOOL CHardwareSetting_ScanHead::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
		set_start_list(1);
		UINT query=get_head_status(1);
		set_end_of_list();
		execute_list(1);
		CLaserScanDoc::s_HeadStatus=query;
		UINT bit;
		bit=query % 2;
		query=query/2;
		bit=query % 2;
		query=query/2;
		bit=query % 2;
		query=query/2;
		bit=query % 2;
		query=query/2;
		//bit3=bit;
		if (bit) ScanHead_bit3="OK";
		else  ScanHead_bit3="ERROR";
		bit=query % 2;
		query=query/2;
		//bit4=bit;
		if (bit)  ScanHead_bit4="OK";
		else  ScanHead_bit4="ERROR";
		bit=query % 2;
		query=query/2;
		bit=query % 2;
		query=query/2;
		//bit6=bit;
		if (bit) ScanHead_bit6="OK";
		else  ScanHead_bit6="ERROR";
		bit=query % 2;
		query=query/2;
		//bit7=bit;
		if (bit) ScanHead_bit7="OK";
		else  ScanHead_bit7="ERROR";
		UpdateData(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
