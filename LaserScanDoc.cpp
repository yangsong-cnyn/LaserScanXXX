// LaserScanDoc.cpp : implementation of the CLaserScanDoc class
//

#include "stdafx.h"
#include "LaserScan.h"

#include "LaserScanDoc.h"
//Parameter Settings
double CLaserScanDoc::s_JumpSpeed=2080;                     //250*8.32
double CLaserScanDoc::s_MarkSeepd=2080;                     //250*8.32
//RTC5 calibration factor K
double CLaserScanDoc::s_FactorSpeed=8.320;                  //   bit/mm   (m to bits, mm/s to bits/ms)           
double CLaserScanDoc::s_FactorDistance=8320;                //   bit/mm   (mm to bits, mm/ms to bits/ms)
////RTC4 calibration factor
//double CLaserScanDoc::s_FactorSpeed=0.520;                  
//double CLaserScanDoc::s_FactorDistance=520; 
double CLaserScanDoc::s_JumpSpeed_Iner=250;
double CLaserScanDoc::s_MarkSeepd_Iner=250;
unsigned int CLaserScanDoc::s_LaserOnDelay=100;
unsigned int CLaserScanDoc::s_LaserOffDelay=100;
unsigned int CLaserScanDoc::s_JumpDelay=25;
unsigned int CLaserScanDoc::s_MarkDelay=10;
unsigned int CLaserScanDoc::s_PolygonDelay=5;
//laser
double CLaserScanDoc::s_LaserPower=0.6;
unsigned int CLaserScanDoc::s_LaserSetpoint=0;
unsigned int CLaserScanDoc::s_Frequency=100000;
BOOL CLaserScanDoc::s_LaserOn=FALSE;
BOOL CLaserScanDoc::s_Draw_ModulationOn=FALSE;
//serial Port
//bool CLaserScanDoc::s_SerialPort_Open=FALSE;
unsigned int CLaserScanDoc::s_SerialPort_Number=1;
CString CLaserScanDoc::s_SerialPort_Parameters=_T("57600,n,8,1");
unsigned int CLaserScanDoc::s_nInputMode=1;
//scan head output and input
unsigned int CLaserScanDoc::s_LaserMode=0;
unsigned int CLaserScanDoc::s_HalfPeriod=106;
unsigned int CLaserScanDoc::s_FrequencySignal=10;
unsigned int CLaserScanDoc::s_PulseLengthSignal=106;
unsigned int CLaserScanDoc::s_FirstPulseKillerLengthSignal=10;
unsigned int CLaserScanDoc::s_QSwtchDelaySignal=10;
//standby
unsigned int CLaserScanDoc::s_StandbyHalfPeriod=1060;
unsigned int CLaserScanDoc::s_StandbyFrequency=100;
unsigned int CLaserScanDoc::s_StanbyPulseLength=1060;
//initialize
unsigned int CLaserScanDoc::s_ErrorCodeInitRTC5=0;
unsigned int CLaserScanDoc::s_ErrorCodeLoadProgram=0;
unsigned int CLaserScanDoc::s_ErrorCodeLoadCorrection=0;

//Error
unsigned int CLaserScanDoc::s_GetError=0;
unsigned int CLaserScanDoc::s_HeadStatus=0;

//wobbel motion
unsigned int CLaserScanDoc::s_transversal=0;
unsigned int CLaserScanDoc::s_longitudinal=0;
double CLaserScanDoc::s_freq=0;
long CLaserScanDoc::s_mode=0;

//processing on the fly
double CLaserScanDoc::s_scalex=0;
double CLaserScanDoc::s_scaley=0;
long CLaserScanDoc::s_rot_x=0;
long CLaserScanDoc::s_rot_y=0;
double CLaserScanDoc::s_resolution=0;
long CLaserScanDoc::s_ret_x=0;
long CLaserScanDoc::s_ret_y=0;
int CLaserScanDoc::s_func_p=0;

//automatic
unsigned int CLaserScanDoc::s_headNo=0;
unsigned int CLaserScanDoc::s_command=0;
double CLaserScanDoc::s_gainX=0;
double CLaserScanDoc::s_gainY=0;
long CLaserScanDoc::s_offsetX=0;
long CLaserScanDoc::s_offsetY=0;
unsigned int CLaserScanDoc::s_Ecode=0;
int CLaserScanDoc::s_func_a=0;

//draw
unsigned int CLaserScanDoc::s_Draw_Option=-1;
unsigned int CLaserScanDoc::s_Line_Option=-1;
unsigned int CLaserScanDoc::s_Circle_Option=-1;
unsigned int CLaserScanDoc::s_Rec_Option=-1;
double CLaserScanDoc::s_Plot_X=0;
double CLaserScanDoc::s_Plot_Y=0;
unsigned int CLaserScanDoc::s_Plot_Duration=0;
double CLaserScanDoc::s_Line_StartX=0;
double CLaserScanDoc::s_Line_StartY=0;
double CLaserScanDoc::s_Line_EndX=0;
double CLaserScanDoc::s_Line_EndY=0;
unsigned int CLaserScanDoc::s_Line_Duration=0;
double CLaserScanDoc::s_Arc_StartX=0;
double CLaserScanDoc::s_Arc_StartY=0;
double CLaserScanDoc::s_Arc_CenterX=0;
double CLaserScanDoc::s_Arc_CenterY=0;
double CLaserScanDoc::s_Arc_Angle=0;
double CLaserScanDoc::s_Rec_StartX=0;
double CLaserScanDoc::s_Rec_StartY=0;
double CLaserScanDoc::s_Rec_EndX=0;
double CLaserScanDoc::s_Rec_EndY=0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLaserScanDoc

IMPLEMENT_DYNCREATE(CLaserScanDoc, CDocument)

BEGIN_MESSAGE_MAP(CLaserScanDoc, CDocument)
END_MESSAGE_MAP()


// CLaserScanDoc construction/destruction

CLaserScanDoc::CLaserScanDoc()

{
	// TODO: add one-time construction code here

}

CLaserScanDoc::~CLaserScanDoc()
{
}

BOOL CLaserScanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CLaserScanDoc serialization

void CLaserScanDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CLaserScanDoc diagnostics

#ifdef _DEBUG
void CLaserScanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLaserScanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLaserScanDoc commands
