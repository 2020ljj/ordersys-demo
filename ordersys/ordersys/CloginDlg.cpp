// CloginDlg.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "CloginDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>



// CloginDlg 对话框

IMPLEMENT_DYNAMIC(CloginDlg, CDialogEx)

CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CloginDlg::~CloginDlg()
{
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CloginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CloginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CloginDlg 消息处理程序


void CloginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_pwd.IsEmpty() || m_user.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	else {
		CString password;
		CString SQL = _T("SELECT * FROM Login where C_id = '")+ m_user + "' ";
		if (CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, SQL)) {
			CPublic::rs.GetFieldValue(_T("password"), password);

			if (password == m_pwd) {
				//MessageBox(SQL);
				CPublic::m_id = m_user;
				CPublic::m_pass = m_pwd;
				MessageBox(TEXT("登陆成功！"));
				CDialog::OnCancel();
			}
			else {
				//MessageBox(SQL);
				MessageBox(TEXT("登陆失败！"));
			}
		}
		else {
			MessageBox(TEXT("操作失败！"));
		}
		CPublic::rs.Close();
	}
}


BOOL CloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!CPublic::db.IsOpen())
	{
		if(CPublic::db.OpenEx(_T("DSN=DataSource64;UID=sa;PWD=*********"), CDatabase::noOdbcDialog))
			MessageBox(TEXT("连接成功！"));
		CPublic::rs.m_pDatabase = &CPublic::db;
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CloginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CloginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CloginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}
