#pragma once


// CWorking_Automatic dialog

class CWorking_Automatic : public CDialog
{
	DECLARE_DYNAMIC(CWorking_Automatic)

public:
	CWorking_Automatic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorking_Automatic();

// Dialog Data
	enum { IDD = IDD_Automatic };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	unsigned int headNo;
	unsigned int command;
	double gainX;
	double gainY;
	long offsetX;
	long offsetY;
	unsigned int Ecode;
	int func;
};
