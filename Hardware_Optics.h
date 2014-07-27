#pragma once
#include "Resource.h"

// CHardware_Optics dialog

class CHardware_Optics : public CDialog
{
	DECLARE_DYNAMIC(CHardware_Optics)

public:
	CHardware_Optics(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHardware_Optics();

// Dialog Data
	enum { IDD = IDD_Optics };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
