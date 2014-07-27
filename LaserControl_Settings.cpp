// LaserControl_Settings.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "LaserControl_Settings.h"
#include "LaserScanDoc.h"

// CLaserControl_Settings dialog

IMPLEMENT_DYNAMIC(CLaserControl_Settings, CDialog)

CLaserControl_Settings::CLaserControl_Settings(CWnd* pParent /*=NULL*/)
	: CDialog(CLaserControl_Settings::IDD, pParent)
	, m_LaserPower(0.6)
	, m_LaserSetpoint(50)
	, m_Frequency(20000)
	, m_SerialPort_Number(1)
	, m_SerialPort_Parameters(_T("57600,n,8,1"))
	, m_SerialPort_StringManualSend(_T(""))
	, m_SerialPort_StringResponse(_T(""))
	, m_bSend(FALSE)
	, m_bReceive(1)
	, m_nInputMode(1)
	, m_Settings_PortState(FALSE)
	, m_HalfPeriod(10)
	, m_FrequencySignal(10)
	, m_PulseLengthSignal(10)
	, m_FirstPulseKillerLengthSignal(10)
	, m_QSwtchDelaySignal(10)
	, m_StandbyHalfPeriod(0)
	, m_StandbyFrequency(0)
	, m_StanbyPulseLength(0)
	, m_nIndex(1)
	, m_LaserMode(0)
	//, m_SerialPort_Open(FALSE)

{
	m_SerialPort_ManualResponse="";

	m_LaserPowerCom="";
	m_LaserSetpointCom="";
	m_LaserFrequencyCom="";



}

CLaserControl_Settings::~CLaserControl_Settings()
{
}

void CLaserControl_Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LaserPower, m_LaserPower);
	//DDV_MinMaxDouble(pDX, m_LaserPower, 0, 20);
	DDX_Text(pDX, IDC_EDIT_LaserSetpoint, m_LaserSetpoint);
	DDV_MinMaxDouble(pDX, m_LaserSetpoint, 0, 100);
	DDX_Text(pDX, IDC_EDIT_LaserFrequency, m_Frequency);
	DDV_MinMaxDouble(pDX, m_Frequency,0, 600000);
	DDX_Text(pDX, IDC_EDIT_SerialpPort, m_SerialPort_Number);
	DDX_Text(pDX, IDC_EDIT_SerialPortParameters, m_SerialPort_Parameters);
	DDX_Text(pDX, IDC_EDIT_SerialpPort_StringManualSend, m_SerialPort_StringManualSend);
	DDX_Text(pDX, IDC_EDIT_SerialPort_Response, m_SerialPort_ManualResponse);
	DDX_Control(pDX, IDC_SerialPort_MSCOMM, m_Com);
	DDX_Text(pDX, IDC_EDIT_HalfPeriod, m_HalfPeriod);
	DDX_Text(pDX, IDC_EDIT_FrequencySignal, m_FrequencySignal);
	DDX_Text(pDX, IDC_EDIT_PulseLength, m_PulseLengthSignal);
	DDX_Text(pDX, IDC_EDIT_FirstPulseKillerLength, m_FirstPulseKillerLengthSignal);
	DDX_Text(pDX, IDC_EDIT_QSwitchDelay, m_QSwtchDelaySignal);
	DDX_Text(pDX, IDC_EDIT_StanbyHalfPeriod, m_StandbyHalfPeriod);
	DDX_Text(pDX, IDC_EDIT_StandbyFrequency, m_StandbyFrequency);
	DDX_Text(pDX, IDC_EDIT_StandbyPulseLength, m_StanbyPulseLength);
}


BEGIN_MESSAGE_MAP(CLaserControl_Settings, CDialog)
	//ON_BN_CLICKED(IDC_LaserControl_Settings_Accept, &CLaserControl_Settings::OnLasercontrolAccept)
	ON_BN_CLICKED(IDC_ManualSend, &CLaserControl_Settings::OnManualsend)
	ON_EN_CHANGE(IDC_EDIT_LaserPower, &CLaserControl_Settings::OnEnChangeLaserpower)
	ON_EN_CHANGE(IDC_EDIT_LaserSetpoint, &CLaserControl_Settings::OnEnChangeLaserSetpoint)
	ON_EN_CHANGE(IDC_EDIT_LaserFrequency, &CLaserControl_Settings::OnEnChangeELaserFrequency)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLaserControl_Settings message handlers

//void CLaserControl_Settings::OnLasercontrolAccept()
//{
//	// TODO: Add your control notification handler code here
//	//UpdateData(TRUE);
//    m_nIndex=2;
//
//    SetTimer(1,100,NULL);
//    UpdateData(TRUE);
//	//laser
//	CLaserScanDoc::s_LaserPower=m_LaserPower;
//	CLaserScanDoc::s_LaserSetpoint=m_LaserSetpoint;
//	CLaserScanDoc::s_Frequency=m_Frequency;
//	//serial Port
//	CLaserScanDoc::s_SerialPort_Number=m_SerialPort_Number;
//	//CString CLaserScanDoc::s_SerialPort_Parameters=m_SerialPort_Parameters;
//	CLaserScanDoc::s_nInputMode=m_nInputMode;
//	//scan head output and input
//	CLaserScanDoc::s_HalfPeriod=m_HalfPeriod;
//	CLaserScanDoc::s_FrequencySignal=m_FrequencySignal;
//	CLaserScanDoc::s_PulseLengthSignal=m_PulseLengthSignal;
//	CLaserScanDoc::s_FirstPulseKillerLengthSignal=m_FirstPulseKillerLengthSignal;
//	CLaserScanDoc::s_QSwtchDelaySignal=m_QSwtchDelaySignal;
//	//CDialog::OnOK();
//}
char CLaserControl_Settings::ConverHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else
		return -1;
	//	return 0;
}
int CLaserControl_Settings::String2Hex(CString str, CByteArray& senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);

	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr=='\0')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConverHexChar(hstr);
		lowhexdata=ConverHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;

	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;

	//return 0;
}
void CLaserControl_Settings::OpenPort(void)
{
	//	BOOL kp;
	//CLaserControl *pDlg=(CLaserControl*)AfxGetMainWnd();
	//int kp=pDlg->m_LaserControl_Status.m_Status_PortState;

	if(m_Com.get_PortOpen())
	{
		m_Com.put_PortOpen(FALSE);
		//m_SerialPort_Open=FALSE;
	}
	m_Com.put_CommPort(m_SerialPort_Number);
	if(!m_Com.get_PortOpen())
	{	
		m_Com.put_PortOpen(TRUE);
	    //m_SerialPort_Open=TRUE;
	    //m_Settings_PortState=m_Com.get_PortOpen();
	}
	else
		AfxMessageBox(_T("cannot open serial port"));
	m_Com.put_Settings(m_SerialPort_Parameters);
	m_Com.put_RThreshold(1);
	m_Com.put_InputMode(1);
	m_Com.put_InputLen(0);
	m_Com.get_Input();
}
void CLaserControl_Settings::OnManualsend()
{
	// TODO: Add your control notification handler code here
	m_nIndex=1;
	
    UpdateData(TRUE);
	m_SerialPort_StringResponse="";
	m_SerialPort_StringManualSend=m_SerialPort_StringManualSend+"\r";
	SendData();
	//if(m_Com.get_PortOpen())
	//{
	//	m_Com.put_PortOpen(FALSE);
	//	//m_SerialPort_Open=FALSE;
	//}
	//OpenPort();
	//m_Com.get_Input();

	//CString strSend;
	//if(m_nInputMode>1)
	//{
	//	CByteArray hexdata;
	//	int len=String2Hex(m_SerialPort_StringManualSend,hexdata);
	//	m_Com.put_Output(COleVariant(hexdata));
	//}
	//else
	//{
	//	m_Com.put_Output(COleVariant(m_SerialPort_StringManualSend));
	//}
}
BEGIN_EVENTSINK_MAP(CLaserControl_Settings, CDialog)
	ON_EVENT(CLaserControl_Settings, IDC_SerialPort_MSCOMM, 1, CLaserControl_Settings::OnCommResponse, VTS_NONE)
END_EVENTSINK_MAP()

void CLaserControl_Settings::OnCommResponse()
{
	// TODO: Add your message handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048];
	CString strtemp;
	if(m_bReceive)
	{
		if(m_Com.get_CommEvent()==2)
		{
			variant_inp=m_Com.get_Input();
			safearray_inp=variant_inp;
			len=safearray_inp.GetOneDimSize();
			for(k=0;k<len;k++)
				safearray_inp.GetElement(&k,rxdata+k);
			for(k=0;k<len;k++)
			{
				BYTE bt=*(char*)(rxdata+k);
				if(m_nInputMode==2)
					strtemp.Format("%02X",bt);
				else
					strtemp.Format("%c",bt);
				m_SerialPort_StringResponse=m_SerialPort_StringResponse+strtemp;
			}
			m_SerialPort_StringResponse+="\r\n";
		}
	}
	if (m_nIndex==1)
	{
		m_SerialPort_ManualResponse=m_SerialPort_StringResponse;
	}
	else if (m_nIndex==2)
	{

	}
	UpdateData(FALSE);
}

void CLaserControl_Settings::OnEnChangeLaserpower()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_LaserSetpoint=(unsigned int)m_LaserPower*10;
	UpdateData(FALSE);
}

void CLaserControl_Settings::OnEnChangeLaserSetpoint()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_LaserPower=10*m_LaserSetpoint*m_Frequency/(double)60000000;
	UpdateData(FALSE);
}

void CLaserControl_Settings::OnEnChangeELaserFrequency()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_LaserPower=10*m_LaserSetpoint*m_Frequency/(double)60000000;
	UpdateData(FALSE);
}

void CLaserControl_Settings::SendData(void)
{
	OpenPort();

	CString strSend;
	if(m_nInputMode>1)
	{
		CByteArray hexdata;
		int len=String2Hex(m_SerialPort_StringManualSend,hexdata);
		m_Com.put_Output(COleVariant(hexdata));
	}
	else
	{
		m_Com.put_Output(COleVariant(m_SerialPort_StringManualSend));
	}

}

BOOL CLaserControl_Settings::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//laser
	m_LaserPower=CLaserScanDoc::s_LaserPower;
	m_LaserSetpoint=CLaserScanDoc::s_LaserSetpoint;
	m_Frequency=CLaserScanDoc::s_Frequency;
	//serial Port
	//m_SerialPort_Open=CLaserScanDoc::s_SerialPort_Open;
	m_SerialPort_Number=CLaserScanDoc::s_SerialPort_Number;
	m_SerialPort_Parameters=_T("57600,n,8,1");
	//strcpy(m_SerialPort_Parameters,CString CLaserScanDoc::s_SerialPort_Parameters);;
	m_nInputMode=CLaserScanDoc::s_nInputMode;
	//scan head output and input
	//m_LaserMode=CLaserScanDoc::s_LaserMode;
	m_HalfPeriod=CLaserScanDoc::s_HalfPeriod;
	m_FrequencySignal=CLaserScanDoc::s_FrequencySignal;
	m_PulseLengthSignal=CLaserScanDoc::s_PulseLengthSignal;
	m_FirstPulseKillerLengthSignal=CLaserScanDoc::s_FirstPulseKillerLengthSignal;
	m_QSwtchDelaySignal=CLaserScanDoc::s_QSwtchDelaySignal;
	//standby
	m_StandbyHalfPeriod=CLaserScanDoc::s_StandbyHalfPeriod;
	m_StandbyFrequency=CLaserScanDoc::s_StandbyFrequency;
	m_StanbyPulseLength=CLaserScanDoc::s_StanbyPulseLength;
   //other
	m_SerialPort_ManualResponse="\0";

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLaserControl_Settings::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
    if (nIDEvent==1)
    {
		CString strtemp;
		this->GetDlgItemText(IDC_EDIT_LaserSetpoint,strtemp);
		//m_LaserSetpointCom="SCS "+strtemp+"\r";
		strtemp="EMOFF \r";
		m_SerialPort_StringManualSend=strtemp;
		SendData();

		CString strtemp1;
		this->GetDlgItemText(IDC_EDIT_LaserSetpoint,strtemp1);
		//m_LaserSetpointCom="SCS "+strtemp1+"\r";
		strtemp1="SCS "+strtemp1+"\r";
		m_SerialPort_StringManualSend=strtemp1;
		SendData();

		CString strtemp2;
		this->GetDlgItemText(IDC_EDIT_LaserFrequency,strtemp2);
		//m_LaserSetpointCom="STF "+strtemp+"\r";
		strtemp2="STF "+strtemp2+"\r";
		m_SerialPort_StringManualSend=strtemp2;
		SendData();

		KillTimer(1);
		//SetTimer(2,100,NULL);	
    }
	else if (nIDEvent==2)
	{
		//CString strtemp2;
		//this->GetDlgItemText(IDC_EDIT_LaserFrequency,strtemp2);
		////m_LaserSetpointCom="STF "+strtemp+"\r";
		//strtemp2="STF "+strtemp2+"\r";
		//m_SerialPort_StringManualSend=strtemp2;
		//CString strinstead=m_SerialPort_StringResponse;
		//SendData();
		//KillTimer(2);
		//KillTimer(1);	
	}


	CDialog::OnTimer(nIDEvent);
}
