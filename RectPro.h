#pragma once


// CRectPro 对话框

class CRectPro : public CDialog
{
	DECLARE_DYNAMIC(CRectPro)

public:
	CRectPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRectPro();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Fill;
};
