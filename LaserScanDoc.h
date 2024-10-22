// LaserScanDoc.h : interface of the CLaserScanDoc class
//


#pragma once


class CLaserScanDoc : public CDocument
{
protected: // create from serialization only
	CLaserScanDoc();
	DECLARE_DYNCREATE(CLaserScanDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CLaserScanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

//for data saving
public:
//parameter
	static double s_JumpSpeed;
	static double s_MarkSeepd;
	static double s_FactorSpeed;
	static double s_FactorDistance;
	static double s_JumpSpeed_Iner;
	static double s_MarkSeepd_Iner;
	static unsigned int s_LaserOnDelay;
	static unsigned int s_LaserOffDelay;
	static unsigned int s_JumpDelay;
	static unsigned int s_MarkDelay;
	static unsigned int s_PolygonDelay;
//laser
	static double s_LaserPower;
    static unsigned int s_LaserSetpoint;
	static unsigned int s_Frequency;
	static BOOL s_LaserOn;
	static BOOL s_Draw_ModulationOn;
//serial Port
    //static bool s_SerialPort_Open;
    static unsigned int s_SerialPort_Number;
	static CString s_SerialPort_Parameters;
	static unsigned int s_nInputMode;
//scan head output and input
    static unsigned int s_LaserMode;
	static unsigned int s_HalfPeriod;
    static unsigned int s_FrequencySignal;
	static unsigned int s_PulseLengthSignal;
	static unsigned int s_FirstPulseKillerLengthSignal;
	static unsigned int s_QSwtchDelaySignal;
//standby
	static unsigned int s_StandbyHalfPeriod;
	static unsigned int s_StandbyFrequency;
	static unsigned int s_StanbyPulseLength;
//initialize
	static unsigned int s_ErrorCodeInitRTC5;
	static unsigned int s_ErrorCodeLoadProgram;
	static unsigned int s_ErrorCodeLoadCorrection;
//Error
	static unsigned int s_GetError;
	static unsigned int s_HeadStatus;
//wobbel motion
	static unsigned int s_transversal;
	static unsigned int s_longitudinal;
	static double s_freq;
	static long s_mode;
//processing on the fly
	static double s_scalex;
	static double s_scaley;
	static long s_rot_x;
	static long s_rot_y;
	static double s_resolution;
	static long s_ret_x;
	static long s_ret_y;
	static int s_func_p;
//automatic
	static unsigned int s_headNo;
	static unsigned int s_command;
	static double s_gainX;
	static double s_gainY;
	static long s_offsetX;
	static long s_offsetY;
	static unsigned int s_Ecode;
	static int s_func_a;
//draw
	static unsigned int s_Draw_Option;
	static unsigned int s_Line_Option;
	static unsigned int s_Circle_Option;
	static unsigned int s_Rec_Option;
	static double s_Plot_X;
	static double s_Plot_Y;
	static unsigned int s_Plot_Duration;
	static double s_Line_StartX;
	static double s_Line_StartY;
	static double s_Line_EndX;
	static double s_Line_EndY;
	static unsigned int s_Line_Duration;
	static double s_Arc_StartX;
	static double s_Arc_StartY;
	static double s_Arc_CenterX;
	static double s_Arc_CenterY;
	static double s_Arc_Angle;
	static double s_Rec_StartX;
	static double s_Rec_StartY;
	static double s_Rec_EndX;
	static double s_Rec_EndY;
};


