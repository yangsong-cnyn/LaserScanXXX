// Bar_CNC2000.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Bar_CNC2000.h"


// CBar_CNC2000 dialog

IMPLEMENT_DYNCREATE(CBar_CNC2000, CDialog)

CBar_CNC2000::CBar_CNC2000(CWnd* pParent /*=NULL*/)
	: CDialog(CBar_CNC2000::IDD, pParent)
{

}

CBar_CNC2000::~CBar_CNC2000()
{
}

void CBar_CNC2000::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBar_CNC2000, CDialog)
END_MESSAGE_MAP()


// CBar_CNC2000 message handlers
