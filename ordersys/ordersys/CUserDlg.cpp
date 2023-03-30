// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "CUserDlg.h"
#include"CMemerDlg.h"



// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_ismem(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ismem);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CUserDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if (!CPublic::db.IsOpen())
	{
		CPublic::db.OpenEx(_T("DSN=DataSource64;UID=sa;PWD=741852Ljj"), CDatabase::noOdbcDialog);
		CPublic::rs.m_pDatabase = &CPublic::db;
	}
	CString SQL = _T("SELECT * FROM Customer WHERE C_id = '")+ CPublic::m_id+"'";
	if (CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, SQL)) {
		CString  Cid, Cname, Cismem;
		CPublic::rs.GetFieldValue(_T("C_name"), Cname);
		CPublic::rs.GetFieldValue(_T("C_ismem"), Cismem);
		CPublic::ismem = Cismem == "是" ? true : false;
		m_name = Cname;
		if (Cismem == "否")
			m_ismem = TEXT("食客");
		else if (Cismem == "是")
			m_ismem = TEXT("会员");

		CPublic::rs.Close();
	}
	else {
		MessageBox(TEXT("操作失败"));
	}
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("密码不一致！"));
		return;
	}
	else {
		CString SQL = _T("update Login set password = '")+ m_surePwd+"' where C_id = '" + CPublic:: m_id+"'";
		CPublic::db.ExecuteSQL(SQL);
		CPublic::m_pass = m_newPwd;
		//MessageBox(SQL);
		CPublic::rs.Close();
		MessageBox(TEXT("修改成功！"));
		UpdateData(TRUE);
		m_newPwd.Empty();
		m_surePwd.Empty();
		UpdateData(FALSE);
	}
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMemerDlg mem;
	mem.DoModal();
}


void CUserDlg::OnBnClickedCancel()
{
	UpdateData(TRUE);
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);

}
