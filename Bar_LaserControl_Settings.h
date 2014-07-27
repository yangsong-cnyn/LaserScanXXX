#pragma once


// CBar_LaserControl_Settings dialog

class CBar_LaserControl_Settings : public CDialog
{
	DECLARE_DYNCREATE(CBar_LaserControl_Settings)

public:
	CBar_LaserControl_Settings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBar_LaserControl_Settings();

// Dialog Data
	enum { IDD = IDD_Bar_LaserControl_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
