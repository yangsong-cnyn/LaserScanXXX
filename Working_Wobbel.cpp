// Working_Wobbel.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Working_Wobbel.h"


// CWorking_Wobbel dialog

IMPLEMENT_DYNAMIC(CWorking_Wobbel, CDialog)

CWorking_Wobbel::CWorking_Wobbel(CWnd* pParent /*=NULL*/)
	: CDialog(CWorking_Wobbel::IDD, pParent)
	, transversal(0)
	, longitudinal(0)
	, freq(0)
	, mode(0)
{

}

CWorking_Wobbel::~CWorking_Wobbel()
{
}

void CWorking_Wobbel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, transversal);
	DDX_Text(pDX, IDC_EDIT2, longitudinal);
	DDX_Text(pDX, IDC_EDIT3, freq);
	DDX_Text(pDX, IDC_EDIT4, mode);
}


BEGIN_MESSAGE_MAP(CWorking_Wobbel, CDialog)
END_MESSAGE_MAP()


// CWorking_Wobbel message handlers
