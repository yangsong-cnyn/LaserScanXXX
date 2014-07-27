// LaserControl_Status.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "LaserControl_Status.h"



// CLaserControl_Status dialog

IMPLEMENT_DYNAMIC(CLaserControl_Status, CDialog)

CLaserControl_Status::CLaserControl_Status(CWnd* pParent /*=NULL*/)
	: CDialog(CLaserControl_Status::IDD, pParent)
	, m_SerialPort_Number(1)
	, m_SerialPort_Parameters(_T("57600,n,8,1"))
	, m_SerialPort_StringManualSend(_T("STA"))
	, m_SerialPort_StringResponse(_T(""))
	, m_bSend(false)
	, m_bReceive(true)
	, m_nInputMode(1)
	, m_Status_PortState(FALSE)
	, m_nCount(0)
	
	
{	
	m_StatusGroup[0]="STA";
	m_StatusGroup[1]="RCT";
	m_StatusGroup[2]="RHT";
	m_StatusGroup[3]="RLDT";
	m_StatusGroup[4]="RBR";
	m_StatusGroup[5]="RITF";
	m_StatusGroup[6]="RNTF";
	m_StatusGroup[7]="RXTF";
	m_StatusGroup[8]="RMN";
	m_StatusGroup[9]="RFV";
	m_StatusGroup[10]="STA";
	//m_StatusGroup[10]="RERR";
	//for (int i=0;i<11;i++)
	//{
	//	m_StatusResponse[i]="aaaaa";
	//}
	m_StatusResponse[0]="\0";
	m_StatusResponse[1]="\0";
	m_StatusResponse[2]="\0";
	m_StatusResponse[3]="\0";
	m_StatusResponse[4]="\0";
	m_StatusResponse[5]="\0";
	m_StatusResponse[6]="\0";
	m_StatusResponse[7]="\0";
	m_StatusResponse[8]="\0";
	m_StatusResponse[9]="\0";
	m_StatusResponse[10]="\0";


	//for (int i=0;i<11;i++)
	//{
	//	m_StatusResponseArray.Add("\0");
	//}
	//m_StatusResponseArray.SetSize(1);
}

CLaserControl_Status::~CLaserControl_Status()
{
}

void CLaserControl_Status::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SerialPort_MSCOMM_Status, m_Com);
	DDX_Text(pDX, IDC_LaserControl_StatusGeneral, m_SerialPort_StringResponse);
}


BEGIN_MESSAGE_MAP(CLaserControl_Status, CDialog)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_ResetError, &CLaserControl_Status::OnResetError)
END_MESSAGE_MAP()


// CLaserControl_Status message handlers

void CLaserControl_Status::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
	//CTime   time; 
	//time=CTime::GetCurrentTime();//获得当前时间     
	//CString   strTime=time.Format( "%Y/%m/%d   %H:%M:%S "); 
	//
	//this-> SetDlgItemText(IDC_EDIT_Time,strTime);
	//for (int i=0;i<11;i++)
	//{
		//m_SerialPort_StringManualSend=m_StatusGroup[1]+"\r";
		//OnManualsend();
		////Sleep(500);
		//m_StatusResponse[1]=m_SerialPort_StringResponse;
  //      this-> SetDlgItemText(IDC_SerialPort_MSCOMM_Status,m_StatusResponse[1]);
		//Sleep(500);
	//}
	  //m_nCount=0;
	  SetTimer(2,100,NULL);
	  if(m_Com.get_PortOpen())
	  {
		  m_Com.put_PortOpen(FALSE);
	  }
	  KillTimer(1);

	  //this-> SetDlgItemText(IDC_LaserControl_StatusGeneral,m_StatusResponseArray.GetAt(0));
	  ////this-> SetDlgItemText(IDC_Status_CaseTemp,m_StatusResponseArray.GetAt(1));
	  ////this-> SetDlgItemText(IDC_Status_HeadTemp,m_StatusResponseArray.GetAt(2));
	  ////this-> SetDlgItemText(IDC_Status_LowDeckTemp,m_StatusResponseArray.GetAt(3));
	  ////this-> SetDlgItemText(IDC_Status_BackReflection,m_StatusResponseArray.GetAt(4));
	  ////this-> SetDlgItemText(IDC_Status_InternalFrequency,m_StatusResponseArray.GetAt(5));
	  ////this-> SetDlgItemText(IDC_Status_MinFrequency,m_StatusResponseArray.GetAt(6));
	  ////this-> SetDlgItemText(IDC_Status_MaxFrequency,m_StatusResponseArray.GetAt(7));
	  //////this-> SetDlgItemText(IDC_STATIC_BackReflectinShow,m_StatusResponse[8]);
	  ////this-> SetDlgItemText(IDC_Status_ModelNumber,m_StatusResponseArray.GetAt(8));
	  ////this-> SetDlgItemText(IDC_Status_FirmwareVersion,m_StatusResponseArray.GetAt(9));

	}
	else if (nIDEvent==2)
	{
		//if(!(m_SerialPort_StringResponse==""))
		//{
		//	m_StatusResponseArray.Add(m_SerialPort_StringResponse);
		//	/*m_StatusResponseList.Add(m_nCount-1,m_SerialPort_StringResponse);*/
		//}
		if (m_nCount>=10)
		{
			KillTimer(2);
		}

		m_SerialPort_StringManualSend=m_StatusGroup[m_nCount]+"\r";
		m_SerialPort_StringResponse="";
		OnManualsend();
		//CString str1=m_StatusResponseArray.GetAt(0);

		this-> SetDlgItemText(IDC_LaserControl_StatusGeneral,m_StatusResponse[0]);
		this-> SetDlgItemText(IDC_Status_CaseTemp,m_StatusResponse[1]);
		this-> SetDlgItemText(IDC_Status_HeadTemp,m_StatusResponse[2]);
		this-> SetDlgItemText(IDC_Status_LowDeckTemp,m_StatusResponse[3]);
		this-> SetDlgItemText(IDC_Status_BackReflection,m_StatusResponse[4]);
		this-> SetDlgItemText(IDC_Status_InternalFrequency,m_StatusResponse[5]);
		this-> SetDlgItemText(IDC_Status_MinFrequency,m_StatusResponse[6]);
		this-> SetDlgItemText(IDC_Status_MaxFrequency,m_StatusResponse[7]);
		this-> SetDlgItemText(IDC_Status_ModelNumber,m_StatusResponse[8]);
		this-> SetDlgItemText(IDC_Status_FirmwareVersion,m_StatusResponse[9]);
		//this-> SetDlgItemText(IDC_Status_Error,m_StatusResponse[10]);
		if (m_nCount<10)
		{
			m_nCount++;
		}


	}
	CDialog::OnTimer(nIDEvent);
}

int CLaserControl_Status::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
     /*SetTimer(1,400,NULL);*/
	return 0;
}

void CLaserControl_Status::OnResetError()
{
	// TODO: Add your control notification handler code here
	//m_StatusGroup[10]="RERR";
	//SetTimer(1,100,NULL);

	//m_SerialPort_StringManualSend=m_StatusGroup[10]+"\r";
	//m_SerialPort_StringResponse="";
	//OnManualsend();

	//CString str1=m_StatusResponseArray.GetAt(0);

	//this-> SetDlgItemText(IDC_LaserControl_StatusGeneral,m_StatusResponse[0]);
	//OnManualsend();
	//this-> SetDlgItemText(IDC_Status_Error,m_StatusResponse[10]);
	//this-> SetDlgItemText(IDC_EDIT_Time,m_SerialPort_StringResponse); 

}

char CLaserControl_Status::ConverHexChar(char ch)
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
int CLaserControl_Status::String2Hex(CString str, CByteArray& senddata)
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
void CLaserControl_Status::OpenPort(void)
{
	//	BOOL kp;
	//CLaserControl *pDlg=(CLaserControl*)AfxGetMainWnd();
	//int sp=pDlg->m_LaserControl_Status.m_Settings_PortState;

	if(m_Com.get_PortOpen() )
		m_Com.put_PortOpen(FALSE);
	m_Com.put_CommPort(m_SerialPort_Number);
	if(!m_Com.get_PortOpen())
	{	m_Com.put_PortOpen(TRUE);
	int kp=m_Com.get_PortOpen();
	}
	else
		AfxMessageBox(_T("cannot open serial port"));
	m_Com.put_Settings(m_SerialPort_Parameters);
	m_Com.put_RThreshold(1);
	m_Com.put_InputMode(1);
	m_Com.put_InputLen(0);
	m_Com.get_Input();
}
void CLaserControl_Status::OnManualsend()
{
	// TODO: Add your control notification handler code here
	//m_SerialPort_StringResponse="";
	//UpdateData(FALSE);
	//UpdateData(TRUE);
	//m_SerialPort_StringManualSend=m_SerialPort_StringManualSend+"\r";
	OpenPort();
	//m_Com.get_Input();

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
BEGIN_EVENTSINK_MAP(CLaserControl_Status, CDialog)
	ON_EVENT(CLaserControl_Status, IDC_SerialPort_MSCOMM_Status, 1, CLaserControl_Status::OnCommResponse, VTS_NONE)
END_EVENTSINK_MAP()

void CLaserControl_Status::OnCommResponse()
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
			m_SerialPort_StringResponse+="\r";
		}
	}
	//UpdateData(FALSE);
	m_StatusResponse[m_nCount-1]=m_SerialPort_StringResponse;

	//if(!(m_SerialPort_StringResponse==""))
	//{
	//	m_StatusResponseArray.Add(m_SerialPort_StringResponse);
	//	/*m_StatusResponseList.Add(m_nCount-1,m_SerialPort_StringResponse);*/
	//}


}


