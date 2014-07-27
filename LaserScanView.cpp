// LaserScanView.cpp : implementation of the CLaserScanView class
//

#include "stdafx.h"
#include "LaserScan.h"

#include "LaserScanDoc.h"
#include "LaserScanView.h"
#include "RTC5impl.hpp"
#include "MainFrm.h"
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLaserScanView

IMPLEMENT_DYNCREATE(CLaserScanView, CView)

BEGIN_MESSAGE_MAP(CLaserScanView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(ID_DRAW_LINE, &CLaserScanView::OnDrawLine)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CLaserScanView::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CLaserScanView::OnDrawEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_32788, &CLaserScanView::OnDraw32788)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CLaserScanView::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CLaserScanView::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CLaserScanView::OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_32788, &CLaserScanView::OnUpdateDraw32788)
	ON_COMMAND(ID_DRAW_POLYGON, &CLaserScanView::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CLaserScanView::OnUpdateDrawPolygon)
	ON_COMMAND(ID_LASER_IMPLEMENT, &CLaserScanView::OnLaserImplement)
	ON_WM_SIZE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID__PROPERTIES, &CLaserScanView::OnProperties)
	ON_COMMAND(ID_FILE_OPEN, &CLaserScanView::OnFileOpen)
END_MESSAGE_MAP()

// CLaserScanView construction/destruction

CLaserScanView::CLaserScanView()
: m_drawtype(0)
, m_ptOrigin(0)
, m_LineStyle(0)
, m_Drawing(false)
, m_ptOld(0)
, size(false)
, test(false)
, Polgon(false)
, DrawPolygon(false)
, downmove(false)
{
	// TODO: add construction code here

}

CLaserScanView::~CLaserScanView()
{
}

BOOL CLaserScanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CLaserScanView drawing
void CLaserScanView::DrawGrid(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	COLORREF backColor = RGB(255, 255, 255);
	CBrush brush(backColor);
	pDC->FillRect(rect, &brush);

	 if (0 == extname.Compare(_T("bmp")))
    {
		//GetBitmap(strPicPath);
        ShowBitmap(pDC,strPicPath);
    }
    else
    {
        if (0 == extname.Compare(_T("jpg"))||0 == extname.Compare(_T("jpeg"))||0 == extname.Compare(_T("gif")))
        {
            ShowPic(pDC,strPicPath);
        }
    }


	CPen* pOldPen;
	CPen penDot,penSolid;
	penDot.CreatePen(PS_DOT, 1, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&penDot);
	
	for (int x = -64*5; x + 356 < rect.right; x += 64)
	{
		pDC->MoveTo(x +356, rect.top);
		pDC->LineTo(x+356, rect.bottom);
	}
	
	for (int y = -64*4; y +306 < rect.bottom; y += 64)
	{
		pDC->MoveTo(rect.left, y+306);
		pDC->LineTo(rect.right, y+306);
	}
	penSolid.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	 pOldPen = pDC->SelectObject(&penSolid);
	    pDC->MoveTo(100,50);
		pDC->LineTo(612,50);
        //pDC->MoveTo(100,);
		pDC->LineTo(612,562);
		//pDC->MoveTo(100,50);
		pDC->LineTo(100,562);
		//pDC->MoveTo(100,50);
		pDC->LineTo(100,50);
		pDC->MoveTo(356, rect.top);
		pDC->LineTo(356, rect.bottom);
		pDC->MoveTo(rect.left, 306);
		pDC->LineTo(rect.right, 306);	
    	pDC->SelectObject(pOldPen);
}

void CLaserScanView::OnDraw(CDC* /*pDC*/)
{
	CLaserScanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
CDC* pDC = GetDC();
		CRect rc;

CDC dcMem;

GetClientRect(rc);

CBitmap bmp; //内存中承载临时图象的位图


dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC

bmp.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());

//创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)

CBitmap *pOldBit=dcMem.SelectObject(&bmp);
//dcMem.FillSolidRect(rc,RGB(255,255,255));
dcMem.IntersectClipRect(rc);

DrawGrid(&dcMem);
    if(!m_ShapeList.empty()){
		

		//dcMem.SetROP2(R2_XORPEN);
		if(m_drawtype!=0)
		{
			m_ShapeList.front()->m_position=CRect(m_ptOrigin,m_ptEnd);
			if(!m_Drawing)
			{
                m_ShapeList.front()->o_position=m_ShapeList.front()->m_position;
				m_ShapeList.front()->m_position.NormalizeRect();
			}
			m_ShapeList.front()->selection=true;
		}
		else{

			if(m_ShapeList.front()->selection)
			{
			    //int HandleID=m_ShapeList.front()->HitTest(testpt,true);
				nHandle=size ? nHandle:m_ShapeList.front()->HitTest(testpt,true);
				if(nHandle>0||(test&&!size)/*||size*/)
				{
					//nHandle=HandleID>0 ? HandleID:nHandle;
				//CRect rect=m_ShapeList.front()->m_position;
				//switch(nHandle)
				//{
				//case 1:
				//	rect=CRect(m_ptEnd,rect.BottomRight());
				//	break;
				//case 2:
				//	rect=CRect(CPoint(rect.TopLeft().x,m_ptEnd.y),rect.BottomRight());
				//	break;
    //            case 3:
				//	rect=CRect(CPoint(rect.TopLeft().x,m_ptEnd.y),CPoint(m_ptEnd.x,rect.BottomRight().y));
				//	//rect.NormalizeRect();
				//	break;
				//case 4:
				//	rect=CRect(rect.TopLeft(),CPoint(m_ptEnd.x,rect.BottomRight().y));
				//	break;
				//case 5:
				//	rect=CRect(rect.TopLeft(),m_ptEnd);
				//	break;
				//case 6:
				//	rect=CRect(rect.TopLeft(),CPoint(rect.BottomRight().x,m_ptEnd.y));
    //                break;	
				//case 7:
				//	rect=CRect(CPoint(m_ptEnd.x,rect.TopLeft().y),CPoint(rect.BottomRight().x,m_ptEnd.y));
				//	break;
				//case 8:
				//	rect=CRect(CPoint(m_ptEnd.x,rect.TopLeft().y),rect.BottomRight());
				//}
				    //rect.NormalizeRect();
				  // m_ShapeList.front()->m_position=rect;
					m_ShapeList.front()->MoveHandle(nHandle,m_ptEnd);
				   if(!m_Drawing)
				         m_ShapeList.front()->m_position.NormalizeRect();
				   else
					   size=true;
					m_ptOld=m_ptEnd;
					testpt=m_ptEnd;              
					//test=size;
				}
			}
			if(!size&&!test)
			{
			ShpIt it = m_ShapeList.begin();
			ShpIt select= m_ShapeList.begin();
			//for(; it != m_ShapeList.end(); it++)
			//{
			//	if((*it)->selection=true)
			//	{
			//		(*it)->DrawTracker(pDC);
			//	}
			//}
			selectnum=0;
			for(; it != m_ShapeList.end(); it++)
			{
				if(((*it)->HitTest(testpt,false)>0)!=(*it)->selection)
				{
					if(selectnum==0||(*it)->selection)
					{
					(*it)->selection=!(*it)->selection;
					}
				}
	            if((*it)->selection)
				{selectnum++;
				select=it;
				}
				if(m_Drawing && /*((*it)->HitTest(m_ptEnd,false)||*/(*it)->selection/*)*/)
				{
					CPoint delta=m_ptEnd-m_ptOld;
					(*it)->moveshape(delta);
				    (*it)->Draw(&dcMem);
					m_ptOld=m_ptEnd;
					testpt=m_ptEnd;
				}

			}
			m_ShapeList.push_front(*select);
			m_ShapeList.erase(select);}
		}
		DrawShape(&dcMem);
		if(m_ShapeList.front()->selection)
			m_ShapeList.front()->DrawTracker(&dcMem);
		
		test=size;
	}
	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&dcMem,0,0,SRCCOPY);

//将内存DC上的图象拷贝到前台

//绘图完成后的清理
		dcMem.SelectObject(pOldBit);
		ReleaseDC(pDC);
	// TODO: add draw code for native data here
}


// CLaserScanView printing

BOOL CLaserScanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLaserScanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLaserScanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLaserScanView diagnostics

#ifdef _DEBUG
void CLaserScanView::AssertValid() const
{
	CView::AssertValid();
}

void CLaserScanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLaserScanDoc* CLaserScanView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaserScanDoc)));
	return (CLaserScanDoc*)m_pDocument;
}
#endif //_DEBUG


// CLaserScanView message handlers

int CLaserScanView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CLaserScanDoc *pDoc=this->GetDocument();

	pDoc->s_ErrorCodeInitRTC5=init_rtc5_dll();
	set_rtc5_mode();
	stop_execution();
	pDoc->s_ErrorCodeLoadProgram = load_program_file( 0 );     //  path = current working path
	//ErrorCode = load_correction_file( 0,   // initialize like "D2_1to1.ct5",
	//                                  1,   // table; #1 is used by default
	//                                  2 ); // use 2D only
	pDoc->s_ErrorCodeLoadCorrection= load_correction_file( "D2_647.ct5",   // initialize like "D2_1to1.ct5",
		1,   // table; #1 is used by default
		2 ); // use 2D only
	select_cor_table( 1, 0 );   //  table #1 at primary connector (default)
	//  stop_execution might have created an RTC5_TIMEOUT error
	reset_error( -1 );    //  Clear all previous error codes

	config_list( -1,                  //  use the list space as a single list
		0 );                
	set_laser_mode( pDoc->s_LaserMode);
	set_laser_control( 0x10 );
	set_start_list( 1 );
	set_laser_pulses( pDoc->s_HalfPeriod, pDoc->s_PulseLengthSignal );
	set_scanner_delays( pDoc->s_JumpDelay, pDoc->s_MarkDelay,pDoc->s_PolygonDelay);
	set_laser_delays(pDoc->s_LaserOnDelay,pDoc->s_LaserOffDelay);
	set_jump_speed( pDoc->s_JumpSpeed_Iner);
	set_mark_speed( pDoc->s_MarkSeepd_Iner);
	pDoc->s_GetError=get_error();
	pDoc->s_HeadStatus=get_head_status(1);
	set_end_of_list();
	execute_list( 1 );
	return 0;
}

// CLaserScanView 消息处理程序

void CLaserScanView::OnDraw32788()
{
	// TODO: 在此添加命令处理程序代码
    m_drawtype=0;
}

void CLaserScanView::OnDrawDot()
{
	// TODO: 在此添加命令处理程序代码
	m_drawtype=1;
}

void CLaserScanView::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_drawtype=2;
}

void CLaserScanView::OnDrawRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_drawtype=3;
}

void CLaserScanView::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_drawtype=4;
}

void CLaserScanView::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	m_drawtype=5;
}


void CLaserScanView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_Drawing=true;// TODO: Add your message handler code here and/or call default
	testpt=point;
	if(m_drawtype==0)
	{
   /*  ShpIt it = m_ShapeList.begin();
	for(; it != m_ShapeList.end(); it++)
	{
		if((*it)->HitTest(point,false)>0)
		{
			(*it)->selection=true;}
		else
		{
			(*it)->selection=false;}
	}*/
		//testpt=point;
		m_ptOld=point;
		m_ptEnd=point;
	}
	else{
		if(!m_ShapeList.empty()&&m_ShapeList.front()->selection)
		{
            CDC* pDC = GetDC();
			m_ShapeList.front()->selection=false;
			ReleaseDC(pDC);
		}
	m_ptOrigin=point;
	m_ptOld=point;
	m_ptEnd=point;
	if(m_drawtype==5)
	{
		if(!Polgon)
		{
		CmydrawPoly* pObj = new CmydrawPoly(CRect(point, CSize(0, 0)));
		pObj->m_nShape = CmydrawShape::polygon;
		pObj->AddPoint(point);
		m_ShapeList.push_front(pObj);
	  m_ShapeList.front()->o_position=CRect(point, CSize(0, 0));
	    Polgon=true;
		}
		else
		{
			dynamic_cast<CmydrawPoly*>(m_ShapeList.front())->m_nPoints--;
			dynamic_cast<CmydrawPoly*>(m_ShapeList.front())->AddPoint(point);
			DrawPolygon=false;
		}
	}
	else{
	CmydrawShape* pObj = new CmydrawShape(CRect(point, CSize(0, 0)));
	switch (m_drawtype)
	{
	default:
		ASSERT(FALSE); // unsuported shape!

	case 2:
		pObj->m_nShape = CmydrawShape::line;
		break;

	case 3:
		pObj->m_nShape = CmydrawShape::rectangle;
		break;

	case 4:
		pObj->m_nShape = CmydrawShape::ellipse;
		break;
	}
	m_ShapeList.push_front(pObj);
	m_ShapeList.front()->o_position=CRect(point, CSize(0, 0));
	}
	/*m_ShapeList.push_front(pObj);
	m_ShapeList.front()->o_position=CRect(point, CSize(0, 0));*/

	//pView->Select(pObj);
	//selectMode = size;
	//nDragHandle = 1;
	//lastPoint = local;
}
	CView::OnLButtonDown(nFlags, point);
}

void   CLaserScanView::OnMouseMove(UINT   nFlags,   CPoint   point)   
{ 
	CString str;
	double x = (((double) point.x) - 356) / 128 * 30;
	double y = (((double) point.y) - 306) / 128 * 30;
	str.Format(_T("x=%f mm,y=%f mm"),x,y);
	//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);
	((CMainFrame*)GetParent())->GetMessageBar()->SetWindowText(str);
	
	//if (m_Drawing) { 
	//	CDC* pDC = GetDC(); 
	//	CPen pen(0,1,RGB(128,128,128));
	//	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	//switch(m_drawtype){
	//	case 2:{
	//	pDC->SelectObject(&pen); 
	//	pDC->SetROP2(R2_XORPEN);
	//	pDC->MoveTo(m_ptOrigin); pDC->LineTo(m_ptOld); // 擦除原直线
	//	pDC->MoveTo(m_ptOrigin); pDC->LineTo(point); // 绘制新直线
	//	break;
	//}
	//	case 3:{
	//	pDC->SelectObject(&pen);
 //       pDC->SelectObject(pBrush);
	//	pDC->SetROP2(R2_XORPEN); 
	//	pDC->MoveTo(m_ptOrigin); pDC->Rectangle( m_ptOrigin.x, m_ptOrigin.y, m_ptOld.x, m_ptOld.y); // 擦除原直线
	//	pDC->MoveTo(m_ptOrigin); pDC->Rectangle( m_ptOrigin.x, m_ptOrigin.y, point.x, point.y); // 绘制新直线
	//	break;

	//}
	//	case 4:{
	//	pDC->SelectObject(&pen);
 //       pDC->SelectObject(pBrush);
	//	pDC->SetROP2(R2_XORPEN); 
	//	pDC->MoveTo(m_ptOrigin);
	//	pDC->Ellipse(CRect(m_ptOrigin,m_ptOld)); //Ellipse( m_ptOrigin.x, m_ptOrigin.y, pm.x, pm.y); // 擦除原直线
	//	pDC->MoveTo(m_ptOrigin);	
	//	pDC->Ellipse(CRect(m_ptOrigin,point)); //Ellipse( m_ptOrigin.x, m_ptOrigin.y, point.x, point.y); // 绘制新直线
	//	break;
	//		   }
	//	default: break;
	//		  }
	//	m_ptOld = point; // 记录老终点
	//	ReleaseDC(pDC); // 释放设备上下文
	//}
	/*ShpIt it = m_ShapeList.begin();
	for(; it != m_ShapeList.end(); it++)
	{

		if(m_Drawing && ((*it)->HitTest(m_ptEnd,false)||(*it)->HitTest(testpt,false))&&m_drawtype==0)
		{
			CPoint delta=m_ptEnd-testpt;
			(*it)->moveshape(delta);
		    }
            Invalidate(0);
	}*/
	if(m_Drawing) { 
		m_ptEnd=point;
		//InvalidateRect(CRect(point, m_ptOrigin),0); 
		downmove=true;
		Invalidate(0);
	}
	if(!m_ShapeList.empty()&&m_ShapeList.front()->selection&&m_drawtype==0)
	{
		int HandleID=m_ShapeList.front()->HitTest(point,true);
		if(HandleID>0)
		SetCursor(m_ShapeList.front()->GetHandleCursor(HandleID));
	}
	if(size)
	{SetCursor(m_ShapeList.front()->GetHandleCursor(nHandle));}
	if(Polgon)
	{
		if(DrawPolygon)
			dynamic_cast<CmydrawPoly*>(m_ShapeList.front())->m_nPoints--;
		dynamic_cast<CmydrawPoly*>(m_ShapeList.front())->AddPoint(point);
		Invalidate(0);
		DrawPolygon=true;	
	}
	CView::OnMouseMove(nFlags, point);
}




void CLaserScanView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!downmove&&!Polgon)
	{
        m_drawtype=0;
		if(!m_ShapeList.empty())
		{
		if(m_ShapeList.front()->m_position.Width()==0&&m_ShapeList.front()->m_position.Height()==0&&m_ShapeList.front()->m_nShape != CmydrawShape::polygon)
			m_ShapeList.erase(m_ShapeList.begin());
		}
	}
	if(m_drawtype==0)
	{
		if(size)
		{
        m_ptEnd=point;
		size=false;
		}
	}
	else{
	m_ptEnd=point;
	}
	/*if(!m_ShapeList.empty()&&m_ShapeList.front()->selection)
		m_ShapeList.front()->m_position.NormalizeRect();*/
	
	m_Drawing=false;
	downmove=false;
	Invalidate(0);
	CView::OnLButtonUp(nFlags, point);
}

void CLaserScanView::OnStyleSolid()
{
	// TODO: 在此添加命令处理程序代码
	m_LineStyle=0;
}

void CLaserScanView::OnStyleDash()
{
	// TODO: 在此添加命令处理程序代码
	m_LineStyle=1;
}

void CLaserScanView::OnStyleDot()
{
	// TODO: 在此添加命令处理程序代码
	m_LineStyle=2;
}


void CLaserScanView::DrawShape(CDC* pDC)
{
	ShapeList::reverse_iterator it = m_ShapeList.rbegin();
	for(; it != m_ShapeList.rend(); it++)
	{
		(*it)->Draw(pDC);
	}
}
void CLaserScanView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_drawtype==2)
	pCmdUI->SetCheck(1);
	else
    pCmdUI->SetCheck(0);
}

void CLaserScanView::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_drawtype==3)
	pCmdUI->SetCheck(1);
	else
    pCmdUI->SetCheck(0);
}

void CLaserScanView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_drawtype==4)
	pCmdUI->SetCheck(1);
	else
    pCmdUI->SetCheck(0);
}

void CLaserScanView::OnUpdateDraw32788(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_drawtype==0)
	pCmdUI->SetCheck(1);
	else
    pCmdUI->SetCheck(0);
}

void CLaserScanView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(!Polgon&&!m_ShapeList.empty())
	{
		ShpIt it = m_ShapeList.begin();
			ShpIt select= m_ShapeList.begin();
			selectnum=0;
			for(; it != m_ShapeList.end(); it++)
			{
				if(((*it)->HitTest(testpt,false)>0)!=(*it)->selection)
				{
					if(selectnum==0||(*it)->selection)
					{
					(*it)->selection=!(*it)->selection;
					}
				}
	            if((*it)->selection)
				{selectnum++;
				select=it;
				(*it)->ChangeRectPro();
				}
			}
			m_ShapeList.push_front(*select);
			m_ShapeList.erase(select);
			Invalidate(0);

	}
	else
	{
		m_drawtype=0;
		Polgon=false;
	}
}


void CLaserScanView::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_drawtype==5)
	pCmdUI->SetCheck(1);
	else
    pCmdUI->SetCheck(0);
}

void CLaserScanView::OnLaserImplement()
{
	// TODO: 在此添加命令处理程序代码

	ShpIt it = m_ShapeList.begin();
	set_start_list(1);
	for(; it != m_ShapeList.end(); it++) {(*it)->Implement();}
	set_end_of_list();
	execute_list(1);
}

void CLaserScanView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	Invalidate(0);

	// TODO: 在此处添加消息处理程序代码
}



void CLaserScanView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!m_ShapeList.empty())
	{
	ShpIt it = m_ShapeList.begin();
			ShpIt select= m_ShapeList.begin();
			selectnum=0;
			for(; it != m_ShapeList.end(); it++)
			{
				if(((*it)->HitTest(point,false)>0)&&selectnum==0)
				{
                selectnum++;
				select=it;
				CMenu menu,*pSubMenu;//定义下面要用到的cmenu对象 
                menu.LoadMenu(IDR_MENU1);//装载自定义的右键菜单 
                pSubMenu=menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单 
                CPoint oPoint;//定义一个用于确定光标位置的位置 
                GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标 
                pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);  
				//(*it)->ChangeRectPro();
				RPro=it;
				}
			}
			Invalidate(0);
	}
	CView::OnRButtonUp(nFlags, point);
}



void CLaserScanView::OnProperties()
{
	// TODO: 在此添加命令处理程序代码
	(*RPro)->ChangeRectPro();
    Invalidate(0);
}

void CLaserScanView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	//CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP;*.jpg)|*.BMP;*.jpg|"));
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("图片文件(*.jpg;*.jpeg;*.gif;*.bmp)|*.jpg;*.jpeg;*.gif;*.bmp|位图文件(*.BMP)|*.BMP||"));
    if (IDOK==dlg.DoModal())
    {
        strPicPath.Format(_T("%s"),dlg.GetPathName());
        extname = dlg.GetFileExt();             //返回选定文件的扩展文件名
        extname.MakeLower();        //将后缀名变成小写的
        Invalidate();
    }

}

/*void CLaserScanView::GetBitmap(CString strPicPath)
{
	HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,strPicPath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
    m_bitmap.Detach();
    m_bitmap.Attach(hBitmap);
    DeleteObject(hBitmap);
}*/

void CLaserScanView::ShowBitmap(CDC* pDC,CString strPicPath)
{        
	HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,strPicPath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
    m_bitmap.Detach();
    m_bitmap.Attach(hBitmap);
    CRect rect;
    GetClientRect(&rect);
    CDC dcImage;
    if (!dcImage.CreateCompatibleDC(pDC))
    {
        return;
    }
    BITMAP bm;
    m_bitmap.GetBitmap(&bm);
    dcImage.SelectObject(&m_bitmap);
	pDC->SetStretchBltMode(STRETCH_HALFTONE); 
    //pDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcImage,0,0,SRCCOPY); //图片保留原始大小
    pDC->StretchBlt(0,0,rect.right,rect.bottom,&dcImage,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY); //图片拉伸显示，填满整个客户区
	dcImage.DeleteDC();
	DeleteObject(hBitmap);
}

void CLaserScanView::ShowPic(CDC* pDC,CString strPicPath)
{        
    if(!m_MyImage.IsNull())
        m_MyImage.Destroy();
    HRESULT hResult=m_MyImage.Load(strPicPath);
    int iWidth=m_MyImage.GetWidth();
    int iHeight=m_MyImage.GetHeight();
	//pDC->SetStretchBltMode(STRETCH_HALFTONE); 

    m_MyImage.Draw(pDC->m_hDC,0,0,iWidth,iHeight);
}
