// Bar_LaserControl_Settings.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Bar_LaserControl_Settings.h"


// CBar_LaserControl_Settings dialog

IMPLEMENT_DYNCREATE(CBar_LaserControl_Settings, CDialog)

CBar_LaserControl_Settings::CBar_LaserControl_Settings(CWnd* pParent /*=NULL*/)
	: CDialog(CBar_LaserControl_Settings::IDD, pParent)
{

}

CBar_LaserControl_Settings::~CBar_LaserControl_Settings()
{
}

void CBar_LaserControl_Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBar_LaserControl_Settings, CDialog)
END_MESSAGE_MAP()


// CBar_LaserControl_Settings message handlers
