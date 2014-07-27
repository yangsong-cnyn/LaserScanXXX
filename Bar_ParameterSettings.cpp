// Bar_ParameterSettings.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Bar_ParameterSettings.h"


// CBar_ParameterSettings dialog

IMPLEMENT_DYNCREATE(CBar_ParameterSettings, CDialog)

CBar_ParameterSettings::CBar_ParameterSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CBar_ParameterSettings::IDD, pParent)
{

}

CBar_ParameterSettings::~CBar_ParameterSettings()
{
}

void CBar_ParameterSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBar_ParameterSettings, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBar_ParameterSettings message handlers

void CBar_ParameterSettings::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//if(IsWindow(m_lookFor))
	//	m_lookFor.MoveWindow (0,20,cx,20);

	//if(IsWindow(m_filter))
	//	m_filter.MoveWindow (0,60,cx,20);

	// TODO: Add your message handler code here
}
