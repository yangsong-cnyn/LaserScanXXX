#pragma once
#include "CMSComm.h"
#include "string.h"

// CLaserControl_Status dialog

class CLaserControl_Status : public CDialog
{
	DECLARE_DYNAMIC(CLaserControl_Status)

public:
	CLaserControl_Status(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLaserControl_Status();

// Dialog Data
	enum { IDD = IDD_LaserControl_Status };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnResetError();

	int m_SerialPort_Number;
	CString m_SerialPort_Parameters;
	CString m_SerialPort_StringManualSend;
	//CString m_SerialPort_StringResponse;
	bool m_bSend;
	bool m_bReceive;
	int m_nInputMode;
	char ConverHexChar(char ch);
	int String2Hex(CString str, CByteArray& senddata);
	void OpenPort(void);
	void OnCommResponse();
	afx_msg void OnManualsend();

	DECLARE_EVENTSINK_MAP()
public:
	CMSComm m_Com;
	CString m_SerialPort_StringResponse;
	bool m_Status_PortState;
	CString m_StatusGroup[11];
public:
	CString m_StatusResponse[11];
	//CStringArray m_StatusResponseArray;
	//CStringList m_StatusResponseList[11];
	int m_nCount;

};
