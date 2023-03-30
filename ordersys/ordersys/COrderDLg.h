#pragma once



// COrderDLg 窗体视图

class COrderDLg : public CFormView
{
	DECLARE_DYNCREATE(COrderDLg)

protected:
	COrderDLg();           // 动态创建所使用的受保护的构造函数
	virtual ~COrderDLg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ORDER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl m_menu;
	CImageList list;
public:
	CString m_order;
	CString m_price;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void window(CString m_log);
	void winendl();
private:
	float suanP;
public:
	CString getcurtime();
private:
	unsigned long long  bid=4000000003;
public:
	CString M_kind;
	CString O_id;
	int m_all;
};


