// Working_Processing.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Working_Processing.h"


// CWorking_Processing dialog

IMPLEMENT_DYNAMIC(CWorking_Processing, CDialog)

CWorking_Processing::CWorking_Processing(CWnd* pParent /*=NULL*/)
	: CDialog(CWorking_Processing::IDD, pParent)
	, scalex(0)
	, scaley(0)
	, rot_x(0)
	, rot_y(0)
	, resolution(0)
	, ret_x(0)
	, ret_y(0)
	, func(0)
{

}

CWorking_Processing::~CWorking_Processing()
{
}

void CWorking_Processing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, scalex);
	DDX_Text(pDX, IDC_EDIT2, scaley);
	DDX_Text(pDX, IDC_EDIT6, rot_x);
	DDX_Text(pDX, IDC_EDIT7, rot_y);
	DDX_Text(pDX, IDC_EDIT3, resolution);
	DDX_Text(pDX, IDC_EDIT4, ret_x);
	DDX_Text(pDX, IDC_EDIT5, ret_y);
	DDX_Radio(pDX, IDC_RADIO8, func);
}


BEGIN_MESSAGE_MAP(CWorking_Processing, CDialog)
END_MESSAGE_MAP()


// CWorking_Processing message handlers
