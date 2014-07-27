// RectPro.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserScan.h"
#include "RectPro.h"


// CRectPro 对话框

IMPLEMENT_DYNAMIC(CRectPro, CDialog)

CRectPro::CRectPro(CWnd* pParent /*=NULL*/)
	: CDialog(CRectPro::IDD, pParent)
	, m_Fill(FALSE)
{

}

CRectPro::~CRectPro()
{
}

void CRectPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_Fill);
}


BEGIN_MESSAGE_MAP(CRectPro, CDialog)
END_MESSAGE_MAP()


// CRectPro 消息处理程序
