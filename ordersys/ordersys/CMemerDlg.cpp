// CMemerDlg.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "CMemerDlg.h"
#include "afxdialogex.h"


// CMemerDlg 对话框

IMPLEMENT_DYNAMIC(CMemerDlg, CDialogEx)

CMemerDlg::CMemerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CMemerDlg::~CMemerDlg()
{
}

void CMemerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMemerDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMemerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMemerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMemerDlg 消息处理程序


void CMemerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//在这里加变成会员的功能哦！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	CPublic::ismem = true;
	CString SQL22 = _T("update [Customer] set C_ismem ='是'where C_id =\'") + CPublic::m_id + _T("\'");
	CPublic::db.ExecuteSQL(SQL22);
	CDialogEx::OnOK();
}


void CMemerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
