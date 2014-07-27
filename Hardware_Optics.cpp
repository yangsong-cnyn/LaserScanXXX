// Hardware_Optics.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Hardware_Optics.h"


// CHardware_Optics dialog

IMPLEMENT_DYNAMIC(CHardware_Optics, CDialog)

CHardware_Optics::CHardware_Optics(CWnd* pParent /*=NULL*/)
	: CDialog(CHardware_Optics::IDD, pParent)
{

}

CHardware_Optics::~CHardware_Optics()
{
}

void CHardware_Optics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHardware_Optics, CDialog)
END_MESSAGE_MAP()


// CHardware_Optics message handlers
