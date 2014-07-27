#pragma once
#include "afxwin.h"
#include "Resource.h"

// CHardware_Initialization dialog

class CHardware_Initialization : public CDialog
{
	DECLARE_DYNAMIC(CHardware_Initialization)

public:
	CHardware_Initialization(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHardware_Initialization();

// Dialog Data
	enum { IDD = IDD_Initialization };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_Initial_bit0;
	CButton m_Initial_bit1;
	CButton m_Initial_bit2;
	CButton m_Initial_bit3;
	CButton m_Initial_bit4;
	CButton m_Initial_bit8;
	CButton m_Initial_bit9;
	CButton m_Initial_bit10;
	CString m_Description;
};
