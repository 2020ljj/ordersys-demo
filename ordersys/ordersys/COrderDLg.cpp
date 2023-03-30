// COrderDLg.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "COrderDLg.h"
#include"CChosMenu.h"
#include"CBillDlg.h"
#include "CPublic.h"
#include<string>
#include<stdlib.h>
// COrderDLg
using namespace std;
IMPLEMENT_DYNCREATE(COrderDLg, CFormView)

COrderDLg::COrderDLg()
	: CFormView(DIALOG_ORDER)
	, m_order(_T(""))
	, m_price(_T(""))
{
	m_all = 0;
	suanP = 0.0f;
	M_kind = _T("");
	O_id = _T("");
}

COrderDLg::~COrderDLg()
{
}

void COrderDLg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_menu);
	DDX_Text(pDX, IDC_EDIT2, m_order);
	DDX_Text(pDX, IDC_EDIT3, m_price);
}

BEGIN_MESSAGE_MAP(COrderDLg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &COrderDLg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &COrderDLg::OnBnClickedButton2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &COrderDLg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// COrderDLg 诊断

#ifdef _DEBUG
void COrderDLg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderDLg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderDLg 消息处理程序


void COrderDLg::OnBnClickedButton1()
{
	//结算
	// TODO: 在此添加控件通知处理程序代码
	CString str;

	CPublic::m_ORDER = m_order;
	CPublic::m_time = getcurtime();
	if (!CPublic::db.IsOpen())
	{
		CPublic::db.OpenEx(_T("DSN = DataSource64; UID = sa; PWD = 741852Ljj"), CDatabase::noOdbcDialog);
		CPublic::rs.m_pDatabase = &CPublic::db;
	}
	CString aa;
	CString sql2 = _T("select B_id from Bill");
	CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql2);
	while (!CPublic::rs.IsEOF()) {
		CPublic::rs.GetFieldValue(_T("B_id"), aa);
		CPublic::rs.MoveNext();		//查询下一条记录
	}
	//MessageBox(aa);
	string aaa = CT2A(aa.GetString());
	bid = strtoull(aaa.c_str(), NULL, 10);
	bid++;
	str.Format(_T("%I64d"), bid);
	CPublic::m_bid = str;
	CString sql1 = _T("insert into Bill values(\'") + CPublic::m_bid + _T("\',\'") + CPublic::m_id + _T("\',\'") + CPublic::m_PRICE + _T("\',\'") + CPublic::m_time
		+ _T("\')");
	CPublic::db.ExecuteSQL(_T("insert into Bill values(\'") + CPublic::m_bid + _T("\',\'") + CPublic::m_id + _T("\',\'") + CPublic::m_PRICE + _T("\',\'") + CPublic::m_time
		+ _T("\')"));
	CPublic::rs.Close();
	sql2 = _T("select * from [Order]");
	CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql2);

	if (!CPublic::rs.IsEOF()) {
		CPublic::rs.MoveLast();
	}
	for (int ii = 1; ii <= m_all; ii++) {
		CString ooid;
		CPublic::rs.GetFieldValue(_T("O_id"), ooid);
		MessageBox(ooid);
		CString SQL222 = _T("update [Order] set O_time='") + CPublic::m_time +_T("'where O_id =\'") + ooid + _T("\'");
		CPublic::db.ExecuteSQL(SQL222);
		CPublic::rs.MovePrev();
	}
	CPublic::rs.Close(); 
	MessageBox(TEXT("已完成结算。"));
	suanP = 0;
	m_all = 0;
	m_price = CPublic::m_PRICE;
	UpdateData(TRUE);
	m_order.Empty();
	m_price.Empty();
	UpdateData(FALSE);
}


void COrderDLg::OnBnClickedButton2()
{
	//清除
	// TODO: 在此添加控件通知处理程序代码
	suanP = 0;
	UpdateData(TRUE);
	m_order.Empty();
	m_price.Empty();
	UpdateData(FALSE);
}


void COrderDLg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	if (!CPublic::db.IsOpen())
	{
		CPublic::db.OpenEx(_T("DSN=test;UID=sa;PWD=wc64779380"), CDatabase::noOdbcDialog);
		CPublic::rs.m_pDatabase = &CPublic::db;
	}
	suanP = 0;
	HICON icon[4];
	icon[0] = AfxGetApp()->LoadIconW(IDI_HAMBURGER);
	icon[1] = AfxGetApp()->LoadIconW(IDI_fries);
	icon[2] = AfxGetApp()->LoadIconW(IDI_ALL);
	icon[3] = AfxGetApp()->LoadIconW(IDI_ICON4);
	list.Create(30, 30, ILC_COLOR32, 4, 4);
	for (int i = 0; i < 4; i++)
	{
		list.Add(icon[i]);
	}
	m_menu.SetImageList(&list, TVSIL_NORMAL);
	HTREEITEM hamburger = m_menu.InsertItem(TEXT("汉堡"), 0, 0, NULL);
	HTREEITEM snacks = m_menu.InsertItem(TEXT("小食"), 1, 1, NULL);
	HTREEITEM drink = m_menu.InsertItem(TEXT("饮料"), 2, 2, NULL);
	HTREEITEM all = m_menu.InsertItem(TEXT("套餐"), 3, 3, NULL);
	HTREEITEM cham = m_menu.InsertItem(TEXT("鸡腿堡"), 4, 4, hamburger);
	HTREEITEM bham = m_menu.InsertItem(TEXT("牛肉堡"), 4, 4, hamburger);
	HTREEITEM fries = m_menu.InsertItem(TEXT("薯条"), 4, 4, snacks);
	HTREEITEM pie = m_menu.InsertItem(TEXT("菠萝派"), 4, 4, snacks);
	HTREEITEM cola = m_menu.InsertItem(TEXT("可乐"), 4, 4, drink);
	HTREEITEM t1 = m_menu.InsertItem(TEXT("鸡腿堡+薯条小+可乐中"), 4, 4, all);
	HTREEITEM t2 = m_menu.InsertItem(TEXT("牛肉堡+菠萝派+可乐中"), 4, 4, all);
}


void COrderDLg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CChosMenu chose;
	HTREEITEM item = m_menu.GetSelectedItem();
	CString name = m_menu.GetItemText(item);
	CString name1;
	CString mem;
	chose.m_Mname = name;
	int num = 0;
	float price = 0;
	if (!(name == TEXT("汉堡") || name == TEXT("小食") || name == TEXT("饮料") || name == TEXT("套餐")))
	{
		//m_all++;
		name1 = name;
		//MessageBox(name1);
		mem = CPublic::ismem == true ? "是" : "否";
		//CString m_price;
		CString SQL1 = _T("SELECT * FROM Menu where M_name = '") + name + _T("' AND M_ismem = '") + mem + " '";
		//MessageBox(SQL1);
		if (CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, SQL1)) {
			if (CPublic::rs.GetRecordCount() == 0)
				m_price = "无法购买";
			else {
				CPublic::rs.GetFieldValue(_T("M_price"), m_price);
			}
			chose.m_Mprice = m_price;
		}
		else {
			MessageBox(TEXT("操作失败！"));
		}
		CPublic::rs.Close();
		chose.DoModal();
		num = _ttoi(chose.m_num);
		price = _tstof(chose.m_Mprice);
		
		
		
		if (num != 0)
		{
		m_all++;
		CString aa;
		CString sql2 = _T("select O_id from [Order]");
		CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql2);
		while (!CPublic::rs.IsEOF()) {
			CPublic::rs.GetFieldValue(_T("O_id"), aa);
			CPublic::rs.MoveNext();		//查询下一条记录
		}
		string aaa = CT2A(aa.GetString());
		long long ss;
		ss = strtoull(aaa.c_str(), NULL, 10);
		ss++;
		aa.Format(_T("%I64d"), ss);
		O_id = aa;
		//MessageBox(O_id);
		CPublic::rs.Close();
		CString sql3 = _T("SELECT M_id FROM Menu where M_name = '") + name + _T("' AND M_ismem = '") + mem + " '";
		CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql3);
		while (!CPublic::rs.IsEOF()) {
			CPublic::rs.GetFieldValue(_T("M_id"), M_kind);
			CPublic::rs.MoveNext();		//查询下一条记录
		}
		//MessageBox(M_kind);
		CPublic::rs.Close();

			CPublic::db.ExecuteSQL(_T("insert into [Order] values(\'") + O_id + _T("\',\'") + CPublic::m_id + _T("\',\'") + M_kind + _T("\',\'") + chose.m_num +
			+_T("\',\'") + CPublic::m_time + _T("\')"));
			suanP = suanP + num * price;
			window(chose.m_Mname);
			window(TEXT("×"));
			window(chose.m_num);
			winendl();
			m_price.Format(_T("%.2f"), suanP);
			UpdateData(FALSE);
			//MessageBox(m_price);
			CPublic::m_PRICE = m_price;
		}
	}


}


void COrderDLg::window(CString m_log)
{

	UpdateData(TRUE);
	m_order += m_log;
	UpdateData(FALSE);
}


void COrderDLg::winendl(){

	UpdateData(TRUE);
	//m_window += m_log;
	m_order += "\r\n";
	UpdateData(FALSE);
}


CString COrderDLg::getcurtime()
{
	// TODO: 在此处添加实现代码.
	CTime timeNow;
	CString strTime;

	timeNow = CTime::GetCurrentTime();
	strTime = timeNow.Format("%Y-%m-%d %H:%M:%S");
	return strTime;
	return CString();
}
