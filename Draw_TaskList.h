#pragma once
#include "afxcmn.h"


// CDraw_TaskList 对话框

class CDraw_TaskList : public CDialog
{
	DECLARE_DYNAMIC(CDraw_TaskList)

public:
	CDraw_TaskList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDraw_TaskList();

// 对话框数据
	enum { IDD = IDD_Draw_TaskList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl n_tree;
};
