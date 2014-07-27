#pragma once
#include "Resource.h"
#include "Hardware_Initialization.h"
#include "Hardware_Optics.h"
#include "afxcmn.h"
#include "HardwareSetting_ScanHead.h"


// CHardwareSettings dialog

class CHardwareSettings : public CDialog
{
	DECLARE_DYNAMIC(CHardwareSettings)

public:
	CHardwareSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHardwareSettings();

// Dialog Data
	enum { IDD = IDD_HardwareSettings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CHardware_Initialization m_Initialization;
	CHardware_Optics m_Optics;
	CTreeCtrl m_Tree_Hardware;
	CHardwareSetting_ScanHead m_ScanHead; 
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTreeHardware(NMHDR *pNMHDR, LRESULT *pResult);
};
