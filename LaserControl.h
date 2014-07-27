#pragma once
#include "afxcmn.h"
#include "LaserControl_Settings.h"
#include "LaserControl_Status.h"


// CLaserControl dialog

class CLaserControl : public CDialog
{
	DECLARE_DYNAMIC(CLaserControl)

public:
	CLaserControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLaserControl();

// Dialog Data
	enum { IDD = IDD_LaserControl };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CTreeCtrl m_Tree_LaserControl;
	CLaserControl_Settings m_LaserControl_Settings;
	CLaserControl_Status m_LaserControl_Status;
public:
	afx_msg void OnTvnSelchangedTreeLasercontrol(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLasercontrolAccept();
	afx_msg void OnLasercontrolExit();
};
