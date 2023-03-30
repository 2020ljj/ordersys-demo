#pragma once


// CMemerDlg 对话框

class CMemerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMemerDlg)

public:
	CMemerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMemerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
