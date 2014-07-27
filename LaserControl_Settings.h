#pragma once
#include "CMSComm.h"



// CLaserControl_Settings dialog

class CLaserControl_Settings : public CDialog
{
	DECLARE_DYNAMIC(CLaserControl_Settings)

public:
	CLaserControl_Settings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLaserControl_Settings();

// Dialog Data
	enum { IDD = IDD_LaserControl_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_LaserPower;
	int m_LaserSetpoint;
	int m_Frequency;
	//afx_msg void OnLasercontrolAccept();
	int m_SerialPort_Number;
	CString m_SerialPort_Parameters;
	CString m_SerialPort_StringManualSend;
	CString m_SerialPort_StringResponse;
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
	bool m_Settings_PortState;
	CMSComm m_Com;


	int m_HalfPeriod;
	int m_FrequencySignal;
	int m_PulseLengthSignal;
	int m_FirstPulseKillerLengthSignal;
	int m_QSwtchDelaySignal;
	CString m_LaserPowerCom;
	CString m_LaserSetpointCom;
	CString m_LaserFrequencyCom;
	afx_msg void OnEnChangeLaserpower();
	afx_msg void OnEnChangeLaserSetpoint();
	afx_msg void OnEnChangeELaserFrequency();
	int m_StandbyHalfPeriod;
	int m_StandbyFrequency;
	int m_StanbyPulseLength;
	void SendData(void);
	virtual BOOL OnInitDialog();
	CString m_SerialPort_ManualResponse;
	int m_nIndex;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_LaserMode;
	//bool m_SerialPort_Open;
};
