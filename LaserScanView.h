// LaserScanView.h : interface of the CLaserScanView class
//


#pragma once
#include "atltypes.h"
#include "mydrawShape.h"
#include "atlimage.h"


class CLaserScanView : public CView
{
protected: // create from serialization only
	CLaserScanView();
	DECLARE_DYNCREATE(CLaserScanView)

// Attributes
public:
	CLaserScanDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLaserScanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	protected:

// 生成的消息映射函数
public:
	afx_msg void OnDrawDot();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT   nFlags,   CPoint   point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void DrawShape(CDC* pDC);
private:
	UINT m_drawtype;
	CPoint m_ptOrigin;
	UINT m_LineStyle;
	ShapeList m_ShapeList;
public:
	afx_msg void OnStyleSolid();
	afx_msg void OnStyleDash();
	afx_msg void OnStyleDot();
private:
	void DrawGrid(CDC* pDC);
	bool m_Drawing;
	CPoint m_ptOld;
	CPoint m_ptEnd;
	CPoint testpt;
	int selectnum;
	bool size;
	bool test;
	bool downmove;
	bool Polgon;
	bool DrawPolygon;
	int nHandle;
	ShpIt RPro;
public:
    CString strPicPath;    //打开的图片文件文件名
    CString extname;    //打开的图片文件的扩展名
    CBitmap m_bitmap;    //创建位图对象
    CImage m_MyImage;    //用于读取与显示jpg等格式的图像文件
	//void GetBitmap(CString strPicPath);
    void ShowBitmap(CDC* pDC,CString strPicPath);    //用来显示指定位图的函数
    void ShowPic(CDC* pDC,CString picName);
public:
	afx_msg void OnDraw32788();
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDraw32788(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnLaserImplement();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // debug version in LaserScanView.cpp
inline CLaserScanDoc* CLaserScanView::GetDocument() const
   { return reinterpret_cast<CLaserScanDoc*>(m_pDocument); }
#endif

