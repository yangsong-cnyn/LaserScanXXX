// mydrawShape.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserScan.h"
#include "mydrawShape.h"
#include "RTC5impl.hpp"
#include "RectPro.h"


// CmydrawShape

CmydrawShape::CmydrawShape()
{
}

CmydrawShape::~CmydrawShape()
{
}

CmydrawShape::CmydrawShape(const CRect& position)
{
	m_position = position;
	selection =false;
	normal =false;
	m_brush=true;
	/*m_pDocument = NULL;

	m_bPen = TRUE;
	m_logpen.lopnStyle = PS_INSIDEFRAME;
	m_logpen.lopnWidth.x = 1;
	m_logpen.lopnWidth.y = 1;
	m_logpen.lopnColor = RGB(0, 0, 0);

	m_bBrush = TRUE;
	m_logbrush.lbStyle = BS_SOLID;
	m_logbrush.lbColor = RGB(192, 192, 192);
	m_logbrush.lbHatch = HS_HORIZONTAL;*/
}
void CmydrawShape::Draw(CDC* pDC)
{
	    //CDC* pDC = GetDC(); 
		CPen pen(0,1,RGB(0,0,0));
		pDC->SelectObject(&pen);
		CBrush brush(RGB(128,128,128));
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		if(m_brush)
        pDC->SelectObject(&brush);
		else
        pDC->SelectObject(pBrush);
	switch(m_nShape){
		case line:{
		pDC->SelectObject(&pen); 
		/*pDC->SetROP2(R2_XORPEN);*/
		//if(normal)
		//{pDC->MoveTo(o_position.TopLeft().x,o_position.BottomRight().y); pDC->LineTo(o_position.BottomRight().x,o_position.TopLeft().y);}
		//else
		//{
		//	pDC->MoveTo(o_position.TopLeft()); pDC->LineTo(o_position.BottomRight());} // 擦除原直线
		CRect rect=o_position;
        o_position.NormalizeRect();
		if(((m_position.BottomRight().x==rect.TopLeft().x)|| (m_position.BottomRight().y==rect.TopLeft().y))&& o_position.EqualRect(m_position) && m_position.BottomRight()!=rect.TopLeft())
			normal=!normal;
		if(normal)
		{
			pDC->MoveTo(m_position.TopLeft().x,m_position.BottomRight().y); pDC->LineTo(m_position.BottomRight().x,m_position.TopLeft().y);}
		else
		{
			//pDC->MoveTo(rect.TopLeft()); pDC->LineTo(rect.BottomRight())
			pDC->MoveTo(m_position.TopLeft()); pDC->LineTo(m_position.BottomRight()); }// 绘制新直线
		break;
	}
		case rectangle:{
		/*pDC->SelectObject(&pen);
        pDC->SelectObject(&brush);*/
		//pDC->SetROP2(R2_XORPEN); 
		//pDC->MoveTo(m_position.TopLeft()); pDC->Rectangle(o_position); // 擦除原直线
		pDC->MoveTo(m_position.TopLeft()); pDC->Rectangle( m_position); // 绘制新直线
		break;

	}
		case ellipse:{
		/*pDC->SelectObject(&pen);
        pDC->SelectObject(&brush);*/
		//pDC->SetROP2(R2_XORPEN); 
		//pDC->MoveTo(m_position.TopLeft());
		//pDC->Ellipse(o_position); //Ellipse( m_ptOrigin.x, m_ptOrigin.y, pm.x, pm.y); // 擦除原直线
		pDC->MoveTo(m_position.TopLeft());	
		pDC->Ellipse(m_position); //Ellipse( m_ptOrigin.x, m_ptOrigin.y, m_ptEnd.x, m_ptEnd.y); // 绘制新直线
		break;
			   }
		default: break;
			  }
		o_position = m_position; // 记录老终点
		//ReleaseDC(pDC);
}
void CmydrawShape::DrawTracker(CDC* pDC)                       //小黑点
{
	ASSERT_VALID(this);
			int nHandleCount = GetHandleCount();                             //return返回2或8或9
			for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
			{
				CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
				CPoint handle = GetHandle(nHandle);
				//pDC->PatBlt(handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);    //画nHandleCount个边长为7的黑色小正方形
				pDC->Ellipse(handle.x - 3, handle.y - 3,handle.x + 3, handle.y + 3);
                pDC->SelectObject(oldBrush);
			}
}
// CmydrawShape 成员函数

int CmydrawShape::GetHandleCount()                    //返回小黑点数量
{
	ASSERT_VALID(this);
	if(m_nShape==line)
		return 2;
	else
	return 8;
}

CPoint CmydrawShape::GetHandle(int nHandle)                     //返回8个小黑点位置坐标
{
	ASSERT_VALID(this);
	int x, y, xCenter, yCenter;

	// this gets the center regardless of left/right and top/bottom ordering
	xCenter = m_position.left + m_position.Width() / 2;
	yCenter = m_position.top + m_position.Height() / 2;
	if(m_nShape==line && nHandle==2)
		nHandle=5;
	if(normal)
		nHandle+=2;

	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
		x = m_position.left;
		y = m_position.top;
		break;

	case 2:
		x = xCenter;
		y = m_position.top;
		break;

	case 3:
		x = m_position.right;
		y = m_position.top;
		break;

	case 4:
		x = m_position.right;
		y = yCenter;
		break;

	case 5:
		x = m_position.right;
		y = m_position.bottom;
		break;

	case 6:
		x = xCenter;
		y = m_position.bottom;
		break;

	case 7:
		x = m_position.left;
		y = m_position.bottom;
		break;

	case 8:
		x = m_position.left;
		y = yCenter;
		break;
	}

	return CPoint(x, y);
}

HCURSOR CmydrawShape::GetHandleCursor(int nHandle)        //鼠标光标移动到小黑点上时的变化
{
	ASSERT_VALID(this);

	LPCTSTR id;

	if(m_nShape==line && nHandle==2)
		nHandle=5;

	if(normal)
		nHandle+=2;

	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
	case 5:
		id = IDC_SIZENWSE;           //西北和东南方向的双向箭头
		break;

	case 2:
	case 6:
		id = IDC_SIZENS;            //向北和向南的双向箭头
		break;

	case 3:
	case 7:
		id = IDC_SIZENESW;         //东北和西南方向的双向箭头
		break;

	case 4:
	case 8:
		id = IDC_SIZEWE;           //向西和向东的双向箭头
		break;
	}

	return AfxGetApp()->LoadStandardCursor(id);          //载入WINDOWS.H中IDC_常量所指定的Windows预定义光标
}

int CmydrawShape::HitTest(CPoint point,BOOL bSelected)
{
	ASSERT_VALID(this);

	if (bSelected)                                                                //检测鼠标是否在小黑点上，如果在，返回在第几个小黑点上（nHandle）
	{
		int nHandleCount = GetHandleCount();
		for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
		{
			// GetHandleRect returns in logical coords
			CRect rc = GetHandleRect(nHandle);                   
			if (rc.PtInRect(point))
				return nHandle;
		}
	}
	else                                                                          
	{
		if(m_nShape==line)
		{
            CPoint m_point[4];
			int k =(GetHandle(1).x-GetHandle(2).x)*(GetHandle(1).y-GetHandle(2).y);
			if(k<0)
			{
			m_point[0]=GetHandle(1)+CPoint(5,5);
			m_point[1]=GetHandle(1)-CPoint(5,5);
			m_point[2]=GetHandle(2)-CPoint(5,5);
			m_point[3]=GetHandle(2)+CPoint(5,5);
			}
			else
			{
				m_point[0]=GetHandle(1)+CPoint(5,-5);
			m_point[1]=GetHandle(1)-CPoint(5,-5);
			m_point[2]=GetHandle(2)-CPoint(5,-5);
			m_point[3]=GetHandle(2)+CPoint(5,-5);
			}
			CRgn rgn;
            rgn.CreatePolygonRgn(m_point, 4, ALTERNATE);
		    if(rgn.PtInRegion(point))
			return 1;		
		}
		else if (m_position.PtInRect(point))
			return 1;
	}
	return 0;
}

CRect CmydrawShape::GetHandleRect(int nHandleID)                   //得到需要处理的矩形（小黑点）
{
	ASSERT_VALID(this);

	CRect rect;
	CPoint point = GetHandle(nHandleID);
	rect.SetRect(point.x-3, point.y-3, point.x+3, point.y+3);
	return rect;
}

void CmydrawShape::moveshape(CPoint point)
{
	m_position+=point;
}

void CmydrawShape::MoveHandle(int nHandle,CPoint point)
{
	if(m_nShape==line && nHandle==2)
		nHandle=5;

	if(normal)
		nHandle+=2;

	switch(nHandle)
				{
				case 1:
					m_position=CRect(point,m_position.BottomRight());
					break;
				case 2:
					m_position=CRect(CPoint(m_position.TopLeft().x,point.y),m_position.BottomRight());
					break;
                case 3:
					m_position=CRect(CPoint(m_position.TopLeft().x,point.y),CPoint(point.x,m_position.BottomRight().y));
					//rect.NormalizeRect();
					break;
				case 4:
					m_position=CRect(m_position.TopLeft(),CPoint(point.x,m_position.BottomRight().y));
					break;
				case 5:
					m_position=CRect(m_position.TopLeft(),point);
					break;
				case 6:
					m_position=CRect(m_position.TopLeft(),CPoint(m_position.BottomRight().x,point.y));
                    break;	
				case 7:
					m_position=CRect(CPoint(point.x,m_position.TopLeft().y),CPoint(m_position.BottomRight().x,point.y));
					break;
				case 8:
					m_position=CRect(CPoint(point.x,m_position.TopLeft().y),m_position.BottomRight());
				}
}

long CmydrawShape::chg(long length)
{
	return (long)((((double) length) - 356) / 128 * 30*8320);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CmydrawShape::Implement() 
{
	//set_start_list(1);
	switch(m_nShape)
	{
	case line:
		if (normal)
		{
			jump_abs(chg(m_position.right),chg(m_position.top));
			mark_abs(chg(m_position.left),chg(m_position.bottom));
		}
		else
		{
			jump_abs(chg(m_position.left),chg(m_position.top));
			mark_abs(chg(m_position.right),chg(m_position.bottom));
		}
		break;
	case rectangle:
		jump_abs(chg(m_position.right),chg(m_position.top));
		mark_abs(chg(m_position.right),chg(m_position.bottom));
		mark_abs(chg(m_position.left ),chg(m_position.bottom));
		mark_abs(chg(m_position.left ),chg(m_position.top));
		mark_abs(chg(m_position.right),chg(m_position.top));
		break;
	case ellipse:
			  ////////////////////////////////////////////////椭圆没有做
		break;
	default:
		break;

	//set_end_of_list();
	//execute_list(1);
	}
}


CmydrawPoly::CmydrawPoly()                                         //初始化
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
}

CmydrawPoly::CmydrawPoly(const CRect& position)
	: CmydrawShape(position)
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
	m_brush=false;
	//m_bPen = TRUE;
	//m_bBrush = FALSE;
}

CmydrawPoly::~CmydrawPoly()
{
	if (m_points != NULL)
		delete[] m_points;
}
//
//void CmydrawPoly::Serialize( CArchive& ar )                 
//{
//	int i;
//	CDrawObj::Serialize( ar );
//	if( ar.IsStoring() )                         //复制剪切
//	{
//		ar << (WORD) m_nPoints;
//		ar << (WORD) m_nAllocPoints;
//		for (i = 0;i< m_nPoints; i++)
//			ar << m_points[i];
//	}
//	else                                         //粘贴
//	{
//		WORD wTemp;
//		ar >> wTemp; m_nPoints = wTemp;
//		ar >> wTemp; m_nAllocPoints = wTemp;
//		m_points = new CPoint[m_nAllocPoints];
//		for (i = 0;i < m_nPoints; i++)
//			ar >> m_points[i];
//	}
//}

void CmydrawPoly::Draw(CDC* pDC)                      //画多边形
{
	ASSERT_VALID(this);

	CPen pen(0,1,RGB(0,0,0));
	CPen *pOldBrush=pDC->SelectObject(&pen);
	
	/*CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldPen=pDC->SelectObject(pBrush);*/
     CBrush brush(RGB(128,128,128));
	CBrush *pOldPen;
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		if(m_brush)
        pOldPen=pDC->SelectObject(&brush);
		else
        pOldPen=pDC->SelectObject(pBrush);
	pDC->Polygon(m_points, m_nPoints);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

// position must be in logical coordinates
void CmydrawPoly::moveshape(CPoint point)      //移动多边形
{
	ASSERT_VALID(this);

	for (int i = 0; i < m_nPoints; i += 1)
	{
		m_points[i] += point;
	}
}

int CmydrawPoly::GetHandleCount()                     //返回小黑点数           
{
	return m_nPoints;
}

CPoint CmydrawPoly::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	ASSERT(nHandle >= 1 && nHandle <= m_nPoints);
	return m_points[nHandle - 1];
}

HCURSOR CmydrawPoly::GetHandleCursor(int nHandle)
{
	return AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}

// point is in logical coordinates
void CmydrawPoly::MoveHandle(int nHandle, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(nHandle >= 1 && nHandle <= m_nPoints);
	if (m_points[nHandle - 1] == point)
		return;

	m_points[nHandle - 1] = point;
	RecalcBounds();
		//Invalidate();

}

// rect must be in logical coordinates
//BOOL CmydrawPoly::Intersects(const CRect& rect)
//{
//	ASSERT_VALID(this);
//	CRgn rgn;
//	rgn.CreatePolygonRgn(m_points, m_nPoints, ALTERNATE);
//	return rgn.RectInRegion(rect);
//}
//
//CDrawObj* CmydrawPoly::Clone(CDrawDoc* pDoc)
//{
//	ASSERT_VALID(this);
//
//	CmydrawPoly* pClone = new CmydrawPoly(m_position);
//	pClone->m_bPen = m_bPen;
//	pClone->m_logpen = m_logpen;
//	pClone->m_bBrush = m_bBrush;
//	pClone->m_logbrush = m_logbrush;
//	pClone->m_points = new CPoint[m_nAllocPoints];
//	memcpy(pClone->m_points, m_points, sizeof(CPoint) * m_nPoints);
//	pClone->m_nAllocPoints = m_nAllocPoints;
//	pClone->m_nPoints = m_nPoints;
//	ASSERT_VALID(pClone);
//
//	if (pDoc != NULL)
//		pDoc->Add(pClone);
//
//	ASSERT_VALID(pClone);
//	return pClone;
//}

// point is in logical coordinates
void CmydrawPoly::AddPoint(const CPoint& point)
{
	ASSERT_VALID(this);
	if (m_nPoints == m_nAllocPoints)
	{
		CPoint* newPoints = new CPoint[m_nAllocPoints + 10];
		if (m_points != NULL)
		{
			memcpy(newPoints, m_points, sizeof(CPoint) * m_nAllocPoints);
			delete[] m_points;
		}
		m_points = newPoints;
		m_nAllocPoints += 10;
	}

	if (m_nPoints == 0 || m_points[m_nPoints - 1] != point)
	{
		m_points[m_nPoints++] = point;
		if (!RecalcBounds())
		{
				//Invalidate();		
		}

	}
}

int CmydrawPoly::HitTest(CPoint point,BOOL bSelected)
{
	ASSERT_VALID(this);

	if (bSelected)                                                                //检测鼠标是否在小黑点上，如果在，返回在第几个小黑点上（nHandle）
	{
		int nHandleCount = GetHandleCount();
		for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
		{
			// GetHandleRect returns in logical coords
			CRect rc = GetHandleRect(nHandle);                   
			if (rc.PtInRect(point))
				return nHandle;
		}
	}
	else                                                                          
	{
		CRgn rgn;
        rgn.CreatePolygonRgn(m_points, m_nPoints, ALTERNATE);
		if(rgn.PtInRegion(point))
			return 1;
	}
	return 0;
}
BOOL CmydrawPoly::RecalcBounds()
{
	ASSERT_VALID(this);

	if (m_nPoints == 0)
		return FALSE;

	CRect bounds(m_points[0], CSize(0, 0));
	for (int i = 1; i < m_nPoints; ++i)
	{
		if (m_points[i].x < bounds.left)
			bounds.left = m_points[i].x;
		if (m_points[i].x > bounds.right)
			bounds.right = m_points[i].x;
		if (m_points[i].y < bounds.top)
			bounds.top = m_points[i].y;
		if (m_points[i].y > bounds.bottom)
			bounds.bottom = m_points[i].y;
	}

	if (bounds == m_position)
		return FALSE;

	m_position = bounds;

	return TRUE;
}



void CmydrawPoly::Implement ()
{
	jump_abs(chg(m_points->x),chg(m_points->y));
	for	(int i=0;i<m_nPoints;i++)
	{
		mark_abs(chg((m_points+i)->x),chg((m_points+i)->y));
	}
	mark_abs(chg(m_points->x),chg(m_points->y));
}

void CmydrawShape::ChangeRectPro()
{
	CRectPro dlg;
	dlg.m_Fill = !m_brush;
	//dlg.m_penSize = m_bPen ? m_logpen.lopnWidth.x : 0;
	
	//sheet.AddPage( &dlg );
	if (dlg.DoModal() != IDOK)
		return;
	m_brush = !dlg.m_Fill;
	//m_bPen = dlg.m_penSize > 0;
	/*if (m_bPen)
	{
		m_logpen.lopnWidth.x = dlg.m_penSize;
		m_logpen.lopnWidth.y = dlg.m_penSize;
	}*/

	//Invalidate();
	//m_pDocument->SetModifiedFlag();
}

