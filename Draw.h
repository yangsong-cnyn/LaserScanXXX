#pragma once
#include "afxwin.h"
#include "CMSComm.h"


// CDraw dialog

class CDraw : public CDialog
{
	DECLARE_DYNAMIC(CDraw)

public:
	CDraw(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDraw();

// Dialog Data
	enum { IDD = IDD_Draw };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnClose();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedImplement();

	double m_Plot_X;
	double m_Plot_Y;
	long m_Plot_Duration;

	double m_Line_StartX;
	double m_Line_StartY;
	double m_Line_EndX;
	double m_Line_EndY;
	int m_Line_Duration;

	double m_Arc_StartX;
	double m_Arc_StartY;
	double m_Arc_CenterX;
	double m_Arc_CenterY;
	double m_Arc_Angle;

	double m_Rec_StartX;
	double m_Rec_StartY;
	double m_Rec_EndX;
	double m_Rec_EndY;
	int m_Draw_Option;
	int m_Line_Option;
	int m_Circle_Option;
	int m_Rec_Option;
	afx_msg void OnBnClickedPlot();
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedArc();
	afx_msg void OnBnClickedRectangle();

//Serial Port
	CMSComm m_Com;
	int m_SerialPort_Number;
	CString m_SerialPort_Parameters;
	CString m_SerialPort_StringManualSend;
	CString m_SerialPort_StringResponse;
	bool m_bSend;
	bool m_bReceive;
	int m_nInputMode;
	int m_nIndex;
	CString m_SerialPort_ManualResponse;
	BOOL m_Draw_LaserOn;
	BOOL m_Draw_ModulationOn;
	void SendData(void);
	char ConverHexChar(char ch);
	int String2Hex(CString str, CByteArray& senddata);
	void OpenPort(void);
	void OnCommResponse();
	DECLARE_EVENTSINK_MAP()

	afx_msg void OnLaserOn();

	afx_msg void OnExit();
	afx_msg void OnModulation();
	double m_CalibrationFactor_K;
};
