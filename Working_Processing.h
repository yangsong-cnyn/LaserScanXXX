#pragma once


// CWorking_Processing dialog

class CWorking_Processing : public CDialog
{
	DECLARE_DYNAMIC(CWorking_Processing)

public:
	CWorking_Processing(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorking_Processing();

// Dialog Data
	enum { IDD = IDD_Processing };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double scalex;
	double scaley;
	long rot_x;
	long rot_y;
	double resolution;
	long ret_x;
	long ret_y;
	int func;
};
