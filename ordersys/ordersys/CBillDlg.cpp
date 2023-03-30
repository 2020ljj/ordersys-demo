// CBillDlg.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "CBillDlg.h"
#include"CPublic.h"


// CBillDlg

IMPLEMENT_DYNCREATE(CBillDlg, CFormView)

CBillDlg::CBillDlg()
	: CFormView(DIALOG_BILL)
{

	m_i = 0;
	m_column = 0;
}

CBillDlg::~CBillDlg()
{
}

void CBillDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CBillDlg, CFormView)
END_MESSAGE_MAP()


// CBillDlg 诊断

#ifdef _DEBUG
void CBillDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBillDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBillDlg 消息处理程序


void CBillDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if (!CPublic::db.IsOpen())	//如果数据源未打开
	{
		CPublic::db.OpenEx(_T("DSN=DataSource64;UID=sa;PWD=741852Ljj"), CDatabase::noOdbcDialog);
		CPublic::rs.m_pDatabase = &CPublic::db;
		CPublic::rs2.m_pDatabase = &CPublic::db;
	}
	OnShowBill();//展示当前用户拥有的全部订单
}

CString CBillDlg::getOrderInfo(CString time1) {
	CString SQL = _T("SELECT M_name,O_number FROM Menu,[Order] where C_id = '") + CPublic::m_id + "'and O_time = '"+ time1+
		"'and Menu.M_id = [Order].M_id";
	CPublic::rs2.Open(AFX_DB_USE_DEFAULT_TYPE, SQL);
	CString Orderinfo;
	CString Mname,Onumber;
	while (!CPublic::rs2.IsEOF()) {
		CString Bid, Cid, Bprice, Btime;
		CPublic::rs2.GetFieldValue(_T("M_name"), Mname);
		CPublic::rs2.GetFieldValue(_T("O_number"), Onumber);
		CPublic::rs2.MoveNext();		//查询下一条记录
		Orderinfo += Mname;
		Orderinfo += "×";
		Orderinfo += Onumber;
		Orderinfo += " ";
	}
	CPublic::rs2.Close();
	return Orderinfo;
}

void CBillDlg::OnShowBill() {
	CString SQL = _T("SELECT * FROM Bill where C_id = '") + CPublic::m_id + "'";
	CPublic::rs.Open(AFX_DB_USE_DEFAULT_TYPE, SQL);
	int column;// 显示界面中的列序号
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString field[] = { _T("订单编号"),_T("订单内容"),_T("订单价格"),_T("订单时间") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		if (!(i == 1 || i == 3))
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
		}
		else
		{
			m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 180);
		}
	}
	if (CPublic::rs.IsEOF()) {
		MessageBox(TEXT("当前无订单！"));
	}
	else {
		while (!CPublic::rs.IsEOF()) {
			int column = 1;
			CString info;
			CString Bid, Cid, Bprice, Btime;
			CPublic::rs.GetFieldValue(_T("B_id"), Bid);
			CPublic::rs.GetFieldValue(_T("C_id"), Cid);
			CPublic::rs.GetFieldValue(_T("B_price"), Bprice);
			CPublic::rs.GetFieldValue(_T("B_time"), Btime);
			info = getOrderInfo(Btime);
			CPublic::rs.MoveNext();		//查询下一条记录
			m_list.InsertItem(m_i, Bid);
			m_list.SetItemText(m_i, column++, info);
			m_list.SetItemText(m_i, column++, Bprice);
			m_list.SetItemText(m_i, column++, Btime);
			m_i++;
		}
	}
	m_i = 0;
	CPublic::rs.Close();
}