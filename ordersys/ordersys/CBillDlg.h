#pragma once



// CBillDlg 窗体视图

class CBillDlg : public CFormView
{
	DECLARE_DYNCREATE(CBillDlg)

protected:
	CBillDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CBillDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_BILL };
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
public:
	CListCtrl m_list;
	virtual void OnInitialUpdate();
	void OnShowBill();		//展示订单
	CString getOrderInfo(CString time);				//根据时间和Cid得到用户点的餐品名：以name* number的形式返回
	int m_i=0;
	int m_column=1;
private:
	CString text=TEXT("4000000002");
};


