// Draw.cpp : implementation file
//

#include "stdafx.h"
#include "LaserScan.h"
#include "Draw.h"
#include "Draw_TaskList.h"
#include "RTC5impl.hpp"
#include "LaserScanDoc.h"


// CDraw dialog

IMPLEMENT_DYNAMIC(CDraw, CDialog)

CDraw::CDraw(CWnd* pParent /*=NULL*/)
	: CDialog(CDraw::IDD, pParent)

	, m_Draw_Option(-1)
	, m_Line_Option(-1)
	, m_Circle_Option(-1)
	, m_Rec_Option(-1)

	, m_Plot_X(0)
	, m_Plot_Y(0)
	, m_Plot_Duration(0)

	, m_Line_StartX(0)
	, m_Line_StartY(0)
	, m_Line_EndX(0)
	, m_Line_EndY(0)
	, m_Line_Duration(0)

	, m_Arc_StartX(0)
	, m_Arc_StartY(0)
	, m_Arc_CenterX(0)
	, m_Arc_CenterY(0)
	, m_Arc_Angle(0)

	, m_Rec_StartX(0)
	, m_Rec_StartY(0)
	, m_Rec_EndX(0)
	, m_Rec_EndY(0)

	, m_SerialPort_Number(1)
	//, m_SerialPort_Parameters(_T("57600,n,8,1"))
	//, m_SerialPort_StringManualSend(_T(""))
	//, m_SerialPort_StringResponse(_T(""))
	, m_bSend(FALSE)
	, m_bReceive(1)
	, m_nInputMode(1)
	, m_nIndex(1)
	, m_Draw_LaserOn(FALSE)
	, m_Draw_ModulationOn(FALSE)
	, m_CalibrationFactor_K(8320)
{
	m_SerialPort_StringManualSend="";
	m_SerialPort_StringResponse="";
	m_SerialPort_ManualResponse="";
	m_SerialPort_Parameters="57600,n,8,1";

}

CDraw::~CDraw()
{
}

void CDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Plot_X, m_Plot_X);
	DDX_Text(pDX, IDC_Plot_Y, m_Plot_Y);
	DDX_Text(pDX, IDC_Plot_Duration, m_Plot_Duration);
	DDX_Text(pDX, IDC_Line_StartX, m_Line_StartX);
	DDX_Text(pDX, IDC_Line_StartY, m_Line_StartY);
	DDX_Text(pDX, IDC_Line_EndX, m_Line_EndX);
	DDX_Text(pDX, IDC_Line_EndY, m_Line_EndY);
	DDX_Text(pDX, IDC_Line_Duration, m_Line_Duration);
	DDX_Text(pDX, IDC_Arc_StartX, m_Arc_StartX);
	DDX_Text(pDX, IDC_Arc_StartY, m_Arc_StartY);
	DDX_Text(pDX, IDC_Arc_CenterX, m_Arc_CenterX);
	DDX_Text(pDX, IDC_Arc_CenterY, m_Arc_CenterY);
	DDX_Text(pDX, IDC_Arc_Angle, m_Arc_Angle);
	DDX_Text(pDX, IDC_Rec_StartX, m_Rec_StartX);
	DDX_Text(pDX, IDC_Rec_StartY, m_Rec_StartY);
	DDX_Text(pDX, IDC_Rec_EndX, m_Rec_EndX);
	DDX_Text(pDX, IDC_Rec_EndY, m_Rec_EndY);
	DDX_Radio(pDX, IDC_Plot, m_Draw_Option);
	DDX_Radio(pDX, IDC_Line_Jump, m_Line_Option);
	DDX_Radio(pDX, IDC_Circle_Unfilled, m_Circle_Option);
	DDX_Radio(pDX, IDC_Rectangule_Unfilled, m_Rec_Option);
	DDX_Control(pDX, IDC_Draw_MSCOMM, m_Com);
}


BEGIN_MESSAGE_MAP(CDraw, CDialog)

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Add, &CDraw::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Implement, &CDraw::OnBnClickedImplement)
	ON_BN_CLICKED(IDC_Plot, &CDraw::OnBnClickedPlot)
	ON_BN_CLICKED(IDC_Line, &CDraw::OnBnClickedLine)
	ON_BN_CLICKED(IDC_Arc, &CDraw::OnBnClickedArc)
	ON_BN_CLICKED(IDC_Rectangle, &CDraw::OnBnClickedRectangle)
	ON_BN_CLICKED(IDC_LaserOn, &CDraw::OnLaserOn)
	ON_BN_CLICKED(IDC_Exit, &CDraw::OnExit)
	ON_BN_CLICKED(IDC_Modulation, &CDraw::OnModulation)
END_MESSAGE_MAP()


// CDraw message handlers
//#define CONVERSION 12500  refer to m_CalibrationFactor_K

HTREEITEM hItem,hSubItem;
CDraw_TaskList *pDlg;

struct Func
  {
   int FuncType;
   long ParaA;
   long ParaB;
   long ParaC;
   long ParaD;
   long  ParaE;
  };

struct Func Task[10000];
int n = 0;

BOOL CDraw::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CalibrationFactor_K=CLaserScanDoc::s_FactorDistance;
	m_Draw_ModulationOn=CLaserScanDoc::s_Draw_ModulationOn;
	m_Draw_LaserOn=CLaserScanDoc::s_LaserOn;
    pDlg = new CDraw_TaskList;
    pDlg->Create(IDD_Draw_TaskList);
    pDlg->ShowWindow(SW_SHOW);
	pDlg->n_tree.ModifyStyle(0,TVS_LINESATROOT|TVS_HASBUTTONS|TVS_HASLINES);
	hItem = pDlg->n_tree.InsertItem(_T("TaskList"),TVI_ROOT);

	return TRUE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDraw::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    ::SendMessage(pDlg->GetSafeHwnd(),WM_CLOSE,0,0);

	//UpdateData();
	//CLaserScanDoc::s_Draw_ModulationOn=m_Draw_ModulationOn;
	//CLaserScanDoc::s_LaserOn=m_Draw_LaserOn;
 //   CLaserScanDoc::s_Draw_Option = m_Draw_Option;
	//CLaserScanDoc::s_Line_Option = m_Line_Option;
	//CLaserScanDoc::s_Circle_Option = m_Circle_Option;
	//CLaserScanDoc::s_Rec_Option = m_Rec_Option;
	//CLaserScanDoc::s_Plot_X = m_Plot_X;
	//CLaserScanDoc::s_Plot_Y = m_Plot_Y;
	//CLaserScanDoc::s_Plot_Duration = m_Plot_Duration;
	//CLaserScanDoc::s_Line_StartX = m_Line_StartX;
	//CLaserScanDoc::s_Line_StartY = m_Line_StartY;
 //   CLaserScanDoc::s_Line_EndX = m_Line_EndX;
	//CLaserScanDoc::s_Line_EndY = m_Line_EndY;
	//CLaserScanDoc::s_Line_Duration = m_Line_Duration;
	//CLaserScanDoc::s_Arc_StartX = m_Arc_StartX;
	//CLaserScanDoc::s_Arc_StartY = m_Arc_StartY;
	//CLaserScanDoc::s_Arc_CenterX = m_Arc_CenterX;
	//CLaserScanDoc::s_Arc_CenterY = m_Arc_CenterY;
	//CLaserScanDoc::s_Arc_Angle = m_Arc_Angle;
 //   CLaserScanDoc::s_Rec_StartX = m_Rec_StartX;
	//CLaserScanDoc::s_Rec_StartY = m_Rec_StartY;
	//CLaserScanDoc::s_Rec_EndX = m_Rec_EndX;
	//CLaserScanDoc::s_Rec_EndY = m_Rec_EndY;
	CDialog::OnClose();
}

void CDraw::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
    UpdateData();
	char TempA[20];
	char TempB[20];
    char TempC[20];
    char TempD[20];
	char TempE[20];

	if(m_Draw_Option == 0)
	  {
	    char ExTask[200];
	    Task[n].FuncType = 0;
        Task[n].ParaA = (long)m_Plot_X * m_CalibrationFactor_K;
		Task[n].ParaB = (long)m_Plot_Y * m_CalibrationFactor_K;
        Task[n].ParaC = 0;
        Task[n].ParaD = 0;
        Task[n].ParaE = m_Plot_Duration;
        
        sprintf_s (TempA, "%.2f", m_Plot_X);
		sprintf_s (TempB, "%.2f", m_Plot_Y);
		sprintf_s (TempC, "%.2f", 0);
		sprintf_s (TempD, "%.2f", 0);

        strcpy_s (ExTask, "");
		strcat_s (ExTask, "Plot ");
		strcat_s (ExTask, "at ");
		strcat_s (ExTask, "( ");
	    strcat_s (ExTask, TempA);
		strcat_s (ExTask, " , ");
		strcat_s (ExTask, TempB);
		strcat_s (ExTask, " )");

	    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
	    n++;
	  }
	else if(m_Draw_Option == 1)
	  {
	    char ExTask[100];
	    if(m_Line_Option == 0)
		  {
			Task[n].FuncType = 1;
			Task[n].ParaA = (long)(m_Line_StartX * m_CalibrationFactor_K);
			Task[n].ParaB = (long)(m_Line_StartY * m_CalibrationFactor_K);
			Task[n].ParaC = (long)(m_Line_EndX * m_CalibrationFactor_K);
			Task[n].ParaD = (long)(m_Line_EndY * m_CalibrationFactor_K);
			Task[n].ParaE = (long)m_Line_Duration;
	        
			sprintf_s (TempA, "%.2f", m_Line_StartX);
			sprintf_s (TempB, "%.2f", m_Line_StartY);
			sprintf_s (TempC, "%.2f", m_Line_EndX);
			sprintf_s (TempD, "%.2f", m_Line_EndY);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Jump from ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempA);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempB);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " to ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
	    else if(m_Line_Option == 1)
		  {
			Task[n].FuncType = 2;
			Task[n].ParaA = (long)(m_Line_StartX * m_CalibrationFactor_K);
			Task[n].ParaB = (long)(m_Line_StartY * m_CalibrationFactor_K);
			Task[n].ParaC = (long)(m_Line_EndX * m_CalibrationFactor_K);
			Task[n].ParaD = (long)(m_Line_EndY * m_CalibrationFactor_K);
			Task[n].ParaE = (long)m_Line_Duration;
	        
			sprintf_s (TempA, "%.2f", m_Line_StartX);
			sprintf_s (TempB, "%.2f", m_Line_StartY);
			sprintf_s (TempC, "%.2f", m_Line_EndX);
			sprintf_s (TempD, "%.2f", m_Line_EndY);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Mark from ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempA);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempB);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " to ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
		else
		  {
		    MessageBox(_T("Please select a type of Line!"));
		  }
	  }
	else if(m_Draw_Option == 2)
	  {
	    char ExTask[100];
	    if(m_Circle_Option == 0)
		  {
			Task[n].FuncType = 3;
			Task[n].ParaA = (long)(m_Arc_StartX * m_CalibrationFactor_K);
			Task[n].ParaB = (long)(m_Arc_StartY * m_CalibrationFactor_K);
			Task[n].ParaC = (long)(m_Arc_CenterX * m_CalibrationFactor_K);
			Task[n].ParaD = (long)(m_Arc_CenterY * m_CalibrationFactor_K);
			Task[n].ParaE = m_Arc_Angle;
	        
			sprintf_s (TempA, "%.2f", m_Arc_StartX);
			sprintf_s (TempB, "%.2f", m_Arc_StartY);
			sprintf_s (TempC, "%.2f", m_Arc_CenterX);
			sprintf_s (TempD, "%.2f", m_Arc_CenterY);
			sprintf_s (TempE, "%d", m_Arc_Angle);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Circular arc");
            strcat_s (ExTask, " of ");
			strcat_s (ExTask, TempE);
			strcat_s (ExTask, "°");
			strcat_s (ExTask, " centered at ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " (Unfilled)");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
	    else if(m_Circle_Option == 1)
		  {
			Task[n].FuncType = 4;
			Task[n].ParaA = (long)(m_Arc_StartX * m_CalibrationFactor_K);
			Task[n].ParaB = (long)(m_Arc_StartY * m_CalibrationFactor_K);
			Task[n].ParaC = (long)(m_Arc_CenterX * m_CalibrationFactor_K);
			Task[n].ParaD = (long)(m_Arc_CenterY * m_CalibrationFactor_K);
			Task[n].ParaE = m_Arc_Angle;
	        
			sprintf_s (TempA, "%.2f", m_Arc_StartX);
			sprintf_s (TempB, "%.2f", m_Arc_StartY);
			sprintf_s (TempC, "%.2f", m_Arc_CenterX);
			sprintf_s (TempD, "%.2f", m_Arc_CenterY);
			sprintf_s (TempE, "%d", m_Arc_Angle);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Circular arc");
            strcat_s (ExTask, " of ");
			strcat_s (ExTask, TempE);
			strcat_s (ExTask, "°");
			strcat_s (ExTask, " centered at ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " (Filled)");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
		else
		  {
		    MessageBox(_T("Please select a type of Ciecle arc!"));
		  }
	  }
	else if(m_Draw_Option == 3)
	  {
	    char ExTask[100];
	    if(m_Rec_Option == 0)
		  {
			Task[n].FuncType = 5;
			Task[n].ParaA = m_Rec_StartX * m_CalibrationFactor_K;
			Task[n].ParaB = m_Rec_StartY * m_CalibrationFactor_K;
			Task[n].ParaC = m_Rec_EndX * m_CalibrationFactor_K;
			Task[n].ParaD = m_Rec_EndY * m_CalibrationFactor_K;
			Task[n].ParaE = 0;
	        
			sprintf_s (TempA, "%.2f", m_Rec_StartX);
			sprintf_s (TempB, "%.2f", m_Rec_StartY);
			sprintf_s (TempC, "%.2f", m_Rec_EndX);
			sprintf_s (TempD, "%.2f", m_Rec_EndY);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Rectangle from ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempA);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempB);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " to ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");
            strcat_s (ExTask, " (Unfilled)");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
	    else if(m_Rec_Option == 1)
		  {
			Task[n].FuncType = 6;
			Task[n].ParaA = m_Rec_StartX * m_CalibrationFactor_K;
			Task[n].ParaB = m_Rec_StartY * m_CalibrationFactor_K;
			Task[n].ParaC = m_Rec_EndX * m_CalibrationFactor_K;
			Task[n].ParaD = m_Rec_EndY * m_CalibrationFactor_K;
			Task[n].ParaE = 0;
	        
			sprintf_s (TempA, "%.2f", m_Rec_StartX);
			sprintf_s (TempB, "%.2f", m_Rec_StartY);
			sprintf_s (TempC, "%.2f", m_Rec_EndX);
			sprintf_s (TempD, "%.2f", m_Rec_EndY);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Rectangle from ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempA);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempB);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " to ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " (X_Filled)");

		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
		else if(m_Rec_Option == 2)
		  {
			Task[n].FuncType = 7;
			Task[n].ParaA = (long)m_Rec_StartX * m_CalibrationFactor_K;
			Task[n].ParaB = (long)m_Rec_StartY * m_CalibrationFactor_K;
			Task[n].ParaC = (long)m_Rec_EndX * m_CalibrationFactor_K;
			Task[n].ParaD = (long)m_Rec_EndY * m_CalibrationFactor_K;
			Task[n].ParaE = 0;
	        
			sprintf_s (TempA, "%.2f", m_Rec_StartX);
			sprintf_s (TempB, "%.2f", m_Rec_StartY);
			sprintf_s (TempC, "%.2f", m_Rec_EndX);
			sprintf_s (TempD, "%.2f", m_Rec_EndY);

			strcpy_s (ExTask, "");
			strcat_s (ExTask, "Rectangle from ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempA);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempB);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " to ");
			strcat_s (ExTask, "( ");
			strcat_s (ExTask, TempC);
			strcat_s (ExTask, " , ");
			strcat_s (ExTask, TempD);
			strcat_s (ExTask, " )");
			strcat_s (ExTask, " (Y_Filled)");
			
		    hSubItem = pDlg->n_tree.InsertItem((LPCTSTR)CString(ExTask), hItem);
	        pDlg->n_tree.Expand(hItem,TVE_EXPAND);
		    n++;
		  }
		else
		  {
		    MessageBox(_T("Please select a type of Rectangle!"));
		  }
	  }
	else
	  {
	    MessageBox(_T("Please select a function!"));
	  }
}



void CDraw::OnBnClickedImplement()
{
	// TODO: 在此添加控件通知处理程序代码
    int taskNum = n;
	int nn=0;

	set_start_list( 1 );
    for (int i = 0; i<taskNum; i++)
	   {
		if (Task[nn].FuncType == 0)
		   {
             //timed_jump_abs( Task[n].ParaA, Task[n].ParaB, Task[n].ParaE);
		     jump_abs(Task[nn].ParaA, Task[nn].ParaB);
			 laser_on_list(Task[nn].ParaE);
 			 //laser_on_list(300000);

			 nn++;
		   }

		else if (Task[nn].FuncType == 1)
		   {
		     jump_abs( Task[nn].ParaA, Task[nn].ParaB);
             //timed_jump_abs( Task[nn].ParaC, Task[nn].ParaD, Task[nn].ParaE);

			 nn++;
		   }
		else if (Task[nn].FuncType == 2)
		   {

		     //mark_abs( Task[nn].ParaC, Task[nn].ParaD);
             //timed_mark_abs( Task[nn].ParaC, Task[nn].ParaD, Task[nn].ParaE);
	
			 for(int i=0;i<Task[nn].ParaE;i++)
			 {
   		      mark_abs( Task[nn].ParaC, Task[nn].ParaD);
    		  mark_abs( Task[nn].ParaA,Task[nn].ParaB);
			 }
			 nn++;
		   }
		else if (Task[nn].FuncType == 3)
		   {
		     jump_abs( Task[nn].ParaA, Task[nn].ParaB);
			 //for(int i=0;i<1000;i++)
			 //{
    //         arc_abs( Task[nn].ParaC, Task[nn].ParaD, Task[nn].ParaE);
			 //}
			 arc_abs( Task[nn].ParaC, Task[nn].ParaD, Task[nn].ParaE);
			 nn++;
		   }
		else if (Task[nn].FuncType == 4)
		   {
		  //   jump_abs( Task[nn].ParaA, Task[nn].ParaB);
			 //
			 //long dX = Task[nn].ParaC - Task[nn].ParaA;
			 //long dY = Task[nn].ParaD - Task[nn].ParaB;			 
			 //long unit_X = 1000*dX/(abs(dX));
			 //long unit_Y = 1000*dY/dX;
			 //long X_Radius = abs(dX);
    //     	 
			 //while ( X_Radius >= 0)
			 //   {  
			 //      arc_abs( Task[nn].ParaC, Task[nn].ParaD, Task[nn].ParaE );
				//   arc_abs( Task[nn].ParaC, Task[nn].ParaD, -Task[nn].ParaE );
				//   jump_rel(unit_X, unit_Y);
				//   X_Radius -= abs(unit_X);
			 //   }
			 //jump_abs( Task[nn].ParaC, Task[nn].ParaD);
			 //nn++;
			  for(int j=0;j<100;j++)
			  {

			   for(int i=1;i<=100;i++ )
			   {
				   jump_abs(Task[nn].ParaA-(long)((double)(Task[nn].ParaA-Task[nn].ParaC)*i/100.0)
					   ,Task[nn].ParaB-(long)((double)(Task[nn].ParaB-Task[nn].ParaD)*i/100.0));
				   arc_abs(Task[nn].ParaC,Task[nn].ParaD,Task[nn].ParaE);
				   arc_abs(Task[nn].ParaC,Task[nn].ParaD,-Task[nn].ParaE);
				   //long u=Task[nn].ParaB-(long)((double)(Task[nn].ParaB-Task[nn].ParaD)*i/100.0);
			   }

			   jump_abs(Task[nn].ParaC,Task[nn].ParaD);



			   //if (j==25)
			   //{
    		//	   set_angle(1,180,0);
			   //}


			  }

			   //set_angle(1,180,0);
			   nn++;
		   }
		else if (Task[nn].FuncType == 5)
		   {
             jump_abs( Task[nn].ParaA, Task[nn].ParaB);

			 mark_abs( Task[nn].ParaC, Task[nn].ParaB);
			 mark_abs( Task[nn].ParaC, Task[nn].ParaD);
			 mark_abs( Task[nn].ParaA, Task[nn].ParaD);
			 mark_abs( Task[nn].ParaA, Task[nn].ParaB);
			 nn++;
		   }
		else if (Task[nn].FuncType == 6)
		   {
		     jump_abs( Task[nn].ParaA, Task[nn].ParaB);

			 long dX = Task[nn].ParaC - Task[nn].ParaA;			 
			 long dY = Task[nn].ParaD - Task[nn].ParaB;

			 long unit_X = 1000*dX/(abs(dX));;
			 long X_comp = abs(dX);

		     while ( X_comp >= 0)
			    {
			       mark_rel( 0, dY );
				   jump_rel(unit_X, 0);
				   mark_rel( 0, -dY );
				   jump_rel(unit_X, 0);
				   X_comp -= abs(unit_X*2);
			    }
             
			 jump_abs( Task[nn].ParaC, Task[nn].ParaD);
			 nn++;
		   }
		 else if (Task[nn].FuncType == 7)
		   {
		     jump_abs( Task[nn].ParaA, Task[nn].ParaB);

			 long dX = Task[nn].ParaC - Task[nn].ParaA;			 
			 long dY = Task[nn].ParaD - Task[nn].ParaB;

			 long unit_Y = 1000*dY/(abs(dY));;
			 long Y_comp = abs(dY);

		     while ( Y_comp >= 0)
			    {
			       mark_rel( 0, dX );
				   jump_rel(unit_Y, 0);
				   mark_rel( 0, -dX );
				   jump_rel(unit_Y, 0);
				   Y_comp -= abs(unit_Y*2);
			    }
             
			 jump_abs( Task[nn].ParaC, Task[nn].ParaD);
			 nn++;
		   }
	   }
	set_end_of_list();
    execute_list( 1 );
}
void CDraw::OnBnClickedPlot()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_Plot_X)->EnableWindow(TRUE);
	GetDlgItem(IDC_Plot_Y)->EnableWindow(TRUE);
	GetDlgItem(IDC_Plot_Duration)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartY)->EnableWindow(FALSE);	
	GetDlgItem(IDC_Line_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_Angle)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Jump)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Mark)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_X_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Y_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Filled)->EnableWindow(FALSE);

    CheckDlgButton(IDC_Line_Jump,0); 
    CheckDlgButton(IDC_Line_Mark,0); 
    CheckDlgButton(IDC_Circle_Unfilled,0); 
	CheckDlgButton(IDC_Circle_Filled,0); 
    CheckDlgButton(IDC_Rectangule_Unfilled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
}

void CDraw::OnBnClickedLine()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_Plot_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_StartY)->EnableWindow(TRUE);	
	GetDlgItem(IDC_Line_EndX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_EndY)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_Duration)->EnableWindow(TRUE);
	GetDlgItem(IDC_Arc_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_Angle)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Jump)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_Mark)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rectangule_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_X_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Y_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Filled)->EnableWindow(FALSE);

	CheckDlgButton(IDC_Line_Jump,1); 
    CheckDlgButton(IDC_Line_Mark,0); 
    CheckDlgButton(IDC_Circle_Unfilled,0); 
	CheckDlgButton(IDC_Circle_Filled,0); 
    CheckDlgButton(IDC_Rectangule_Unfilled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
}

void CDraw::OnBnClickedArc()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_Plot_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartY)->EnableWindow(FALSE);	
	GetDlgItem(IDC_Line_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Arc_StartY)->EnableWindow(TRUE);
	GetDlgItem(IDC_Arc_CenterX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Arc_Angle)->EnableWindow(TRUE);
	GetDlgItem(IDC_Arc_CenterY)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rec_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Jump)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Mark)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_X_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Y_Filled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Unfilled)->EnableWindow(TRUE);
	GetDlgItem(IDC_Circle_Filled)->EnableWindow(TRUE);

	CheckDlgButton(IDC_Line_Jump,0); 
    CheckDlgButton(IDC_Line_Mark,0); 
    CheckDlgButton(IDC_Circle_Unfilled,1); 
	CheckDlgButton(IDC_Circle_Filled,0); 
    CheckDlgButton(IDC_Rectangule_Unfilled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
}

void CDraw::OnBnClickedRectangle()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_Plot_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_Plot_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_StartY)->EnableWindow(FALSE);	
	GetDlgItem(IDC_Line_EndX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_EndY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Duration)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_StartY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterX)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_Angle)->EnableWindow(FALSE);
	GetDlgItem(IDC_Arc_CenterY)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rec_StartX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rec_StartY)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rec_EndX)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rec_EndY)->EnableWindow(TRUE);
	GetDlgItem(IDC_Line_Jump)->EnableWindow(FALSE);
	GetDlgItem(IDC_Line_Mark)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangule_Unfilled)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rectangule_X_Filled)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rectangule_Y_Filled)->EnableWindow(TRUE);
	GetDlgItem(IDC_Circle_Unfilled)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle_Filled)->EnableWindow(FALSE);

	CheckDlgButton(IDC_Line_Jump,0); 
    CheckDlgButton(IDC_Line_Mark,0); 
    CheckDlgButton(IDC_Circle_Unfilled,0); 
	CheckDlgButton(IDC_Circle_Filled,0); 
    CheckDlgButton(IDC_Rectangule_Unfilled,1); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
    CheckDlgButton(IDC_Rectangule_X_Filled,0); 
}
//Serial Port

void CDraw::SendData(void)
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
void CDraw::OpenPort(void)
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
int CDraw::String2Hex(CString str, CByteArray& senddata)
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

char CDraw::ConverHexChar(char ch)
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

BEGIN_EVENTSINK_MAP(CDraw, CDialog)
	ON_EVENT(CDraw, IDC_Draw_MSCOMM, 1, CDraw::OnCommResponse, VTS_NONE)
END_EVENTSINK_MAP()

void CDraw::OnCommResponse()
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
	//UpdateData(FALSE);
}
void CDraw::OnLaserOn()
{
	// TODO: Add your control notification handler code here
	if (m_Draw_LaserOn)
	{
		m_SerialPort_StringResponse="";
		CString strtemp1="EMOFF \r";
		m_SerialPort_StringManualSend=strtemp1;
		SendData();
		m_Draw_LaserOn=FALSE;
	}
	else
	{
	    m_SerialPort_StringResponse="";
		CString strtemp2="EMON \r";
		m_SerialPort_StringManualSend=strtemp2;
		SendData();
		m_Draw_LaserOn=TRUE;
	}
}

void CDraw::OnExit()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CLaserScanDoc::s_Draw_ModulationOn=m_Draw_ModulationOn;
	CLaserScanDoc::s_LaserOn=m_Draw_LaserOn;
	CLaserScanDoc::s_Draw_Option = m_Draw_Option;
	CLaserScanDoc::s_Line_Option = m_Line_Option;
	CLaserScanDoc::s_Circle_Option = m_Circle_Option;
	CLaserScanDoc::s_Rec_Option = m_Rec_Option;
	CLaserScanDoc::s_Plot_X = m_Plot_X;
	CLaserScanDoc::s_Plot_Y = m_Plot_Y;
	CLaserScanDoc::s_Plot_Duration = m_Plot_Duration;
	CLaserScanDoc::s_Line_StartX = m_Line_StartX;
	CLaserScanDoc::s_Line_StartY = m_Line_StartY;
	CLaserScanDoc::s_Line_EndX = m_Line_EndX;
	CLaserScanDoc::s_Line_EndY = m_Line_EndY;
	CLaserScanDoc::s_Line_Duration = m_Line_Duration;
	CLaserScanDoc::s_Arc_StartX = m_Arc_StartX;
	CLaserScanDoc::s_Arc_StartY = m_Arc_StartY;
	CLaserScanDoc::s_Arc_CenterX = m_Arc_CenterX;
	CLaserScanDoc::s_Arc_CenterY = m_Arc_CenterY;
	CLaserScanDoc::s_Arc_Angle = m_Arc_Angle;
	CLaserScanDoc::s_Rec_StartX = m_Rec_StartX;
	CLaserScanDoc::s_Rec_StartY = m_Rec_StartY;
	CLaserScanDoc::s_Rec_EndX = m_Rec_EndX;
	CLaserScanDoc::s_Rec_EndY = m_Rec_EndY;
	CDialog::OnOK();
}

void CDraw::OnModulation()
{
	// TODO: Add your control notification handler code here
	if (!m_Draw_ModulationOn)
	{
		laser_signal_on();
		m_Draw_ModulationOn=TRUE;
	}
	else
	{
		laser_signal_off();
		m_Draw_ModulationOn=FALSE;
	}

}
