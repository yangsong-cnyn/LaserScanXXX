#pragma once


// CBar_ParameterSettings dialog

class CBar_ParameterSettings : public CDialog
{
	DECLARE_DYNCREATE(CBar_ParameterSettings)

public:
	CBar_ParameterSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBar_ParameterSettings();

// Dialog Data
	enum { IDD = IDD_Bar_ParameterSettings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
