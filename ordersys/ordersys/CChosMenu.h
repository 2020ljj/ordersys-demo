#pragma once


// CChosMenu 对话框

class CChosMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CChosMenu)

public:
	CChosMenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChosMenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	
public:
	CString m_Mname;
	CString m_Mprice;
	CString m_num;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl m_spin;
	virtual BOOL OnInitDialog();
	CComboBox m_cbox;
	afx_msg void OnCbnSelchangeCombo1();
private:
	CString m_size;
};
