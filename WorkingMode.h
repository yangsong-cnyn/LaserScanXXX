#pragma once
#include "Working_Automatic.h"
#include "Working_Processing.h"
#include "Working_Wobbel.h"
#include "afxcmn.h"


// CWorkingMode dialog

class CWorkingMode : public CDialog
{
	DECLARE_DYNAMIC(CWorkingMode)

public:
	CWorkingMode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorkingMode();

// Dialog Data
	enum { IDD = IDD_WorkingMode };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CWorking_Automatic m_Automatic;
	CWorking_Processing m_Processing;
	CWorking_Wobbel m_Wobbel;
	CTreeCtrl m_tree_Working;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTreeWorkingmode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
};
