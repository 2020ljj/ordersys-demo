#pragma once

#include <atlstr.h>
#include <afxdb.h>
class CPublic
{
public:
	CPublic();
	~CPublic();
public:
	static CString m_id;//人
	static CString m_pass;
	static BOOL ismem;
	static CString m_bid;
	static CString m_ORDER;
	static CString m_PRICE;
	static CString m_time;
public:
	static CDatabase db;
	static CRecordset rs;
	static CRecordset rs2;
};

