#pragma once


// CBar_CNC2000 dialog

class CBar_CNC2000 : public CDialog
{
	DECLARE_DYNCREATE(CBar_CNC2000)

public:
	CBar_CNC2000(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBar_CNC2000();

// Dialog Data
	enum { IDD = IDD_Bar_CNC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
