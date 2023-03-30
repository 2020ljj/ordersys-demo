// CChosMenu.cpp: 实现文件
//

#include "pch.h"
#include "ordersys.h"
#include "CChosMenu.h"
#include "afxdialogex.h"
#include"CPublic.h"


// CChosMenu 对话框

IMPLEMENT_DYNAMIC(CChosMenu, CDialogEx)

CChosMenu::CChosMenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_Mname(_T(""))
	, m_Mprice(_T(""))
	, m_num(_T(""))
{

}

CChosMenu::~CChosMenu()
{
}

void CChosMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Mname);
	DDX_Text(pDX, IDC_EDIT2, m_Mprice);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_COMBO1, m_cbox);
}


BEGIN_MESSAGE_MAP(CChosMenu, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChosMenu::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CChosMenu::OnDeltaposSpin1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChosMenu::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CChosMenu 消息处理程序


void CChosMenu::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CChosMenu::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CChosMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_spin.SetRange32(0, 10);
	//设置数据的进制
	m_spin.SetBase(10);
	//设置伙伴控件
	m_spin.SetBuddy(GetDlgItem(IDC_EDIT3));
	//设置默认显示
	m_spin.SetPos(0);
	if (m_Mname == TEXT("薯条"))
	{
		m_cbox.EnableWindow(TRUE);
		m_cbox.Clear();
		m_cbox.AddString(TEXT("小"));
		m_cbox.AddString(TEXT("大"));
	}
	else if (m_Mname == TEXT("可乐"))
	{
		m_cbox.EnableWindow(TRUE);
		m_cbox.Clear();
		m_cbox.AddString(TEXT("中"));
		m_cbox.AddString(TEXT("大"));
	}else
	{
		m_cbox.EnableWindow(FALSE);
	}
	m_cbox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChosMenu::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cbox.GetCurSel();
	CString str;

	m_cbox.GetLBText(index, str);
	if (m_Mname == TEXT("薯条"))
	{
		if (str == TEXT("小"))
		{
			if (CPublic::ismem)
			{
				m_Mprice = TEXT("7.5");
			}
			else
			{
				m_Mprice = TEXT("9");
			}
		}
		else
		{
			if (CPublic::ismem)
			{
				m_Mprice = TEXT("10");
			}
			else
			{
				m_Mprice = TEXT("12");
			}
		}
	}
	else if (m_Mname == TEXT("可乐"))
	{
		if (str == TEXT("中"))
		{
			if (CPublic::ismem)
			{
				m_Mprice = TEXT("5");
			}
			else
			{
				m_Mprice = TEXT("7");
			}
		}
		else
		{
			if (CPublic::ismem)
			{
				m_Mprice = TEXT("8");
			}
			else
			{
				m_Mprice = TEXT("10");
			}
		}
	}
	UpdateData(FALSE);
}
