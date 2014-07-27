// Working_Automatic.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Working_Automatic.h"


// CWorking_Automatic dialog

IMPLEMENT_DYNAMIC(CWorking_Automatic, CDialog)

CWorking_Automatic::CWorking_Automatic(CWnd* pParent /*=NULL*/)
	: CDialog(CWorking_Automatic::IDD, pParent)
	, headNo(0)
	, command(0)
	, gainX(0)
	, gainY(0)
	, offsetX(0)
	, offsetY(0)
	, Ecode(0)
	, func(0)
{

}

CWorking_Automatic::~CWorking_Automatic()
{
}

void CWorking_Automatic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, headNo);
	DDX_Text(pDX, IDC_EDIT2, command);
	DDX_Text(pDX, IDC_EDIT3, gainX);
	DDX_Text(pDX, IDC_EDIT4, gainY);
	DDX_Text(pDX, IDC_EDIT5, offsetX);
	DDX_Text(pDX, IDC_EDIT6, offsetY);
	DDX_Text(pDX, IDC_STATIC1, Ecode);
	DDX_Radio(pDX, IDC_RADIO10, func);
}


BEGIN_MESSAGE_MAP(CWorking_Automatic, CDialog)
END_MESSAGE_MAP()


// CWorking_Automatic message handlers
