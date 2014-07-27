#pragma once

// CmydrawShape ÃüÁîÄ¿±ê
#include <list>

class CmydrawShape : public CObject
{
public:
	CmydrawShape();
	virtual ~CmydrawShape();
public:
	CRect m_position;
	CRect o_position;
	bool m_brush;
	bool selection;
	bool normal;
	virtual void Draw(CDC* pDC);
	CmydrawShape(const CRect& position);
    enum Shape {line , rectangle, ellipse,polygon};
	Shape m_nShape;
	void DrawTracker(CDC* pDC);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual CRect GetHandleRect(int nHandleID);
	virtual int HitTest(CPoint point,BOOL bSelected);
	virtual void moveshape(CPoint point);
	virtual void MoveHandle(int nHandle,CPoint point);
	virtual void Implement();
	virtual void ChangeRectPro();
	long chg(long length);
};

typedef std::list<CmydrawShape*> ShapeList;
typedef ShapeList::iterator ShpIt;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
class CmydrawPoly : public CmydrawShape
{


public:
	CmydrawPoly();
	virtual ~CmydrawPoly();
	CmydrawPoly(const CRect& position);
	void AddPoint(const CPoint& point);
	BOOL RecalcBounds();

public:
	virtual void Draw(CDC* pDC);
	virtual void moveshape(CPoint point);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandle(int nHandle, CPoint point);
	virtual int HitTest(CPoint point,BOOL bSelected);
	virtual void Implement();
	int m_nPoints;
	
	//virtual BOOL Intersects(const CRect& rect);
	//virtual CDrawObj* Clone(CDrawDoc* pDoc);

protected:
	CPoint* m_points;
	int m_nAllocPoints;
	CmydrawPoly* m_pDrawObj;

};


