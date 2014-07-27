#pragma once


// CWorking_Wobbel dialog

class CWorking_Wobbel : public CDialog
{
	DECLARE_DYNAMIC(CWorking_Wobbel)

public:
	CWorking_Wobbel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorking_Wobbel();

// Dialog Data
	enum { IDD = IDD_Wobbel };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	unsigned int transversal;
	unsigned int longitudinal;
	double freq;
	long mode;
};
