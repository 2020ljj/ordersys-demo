#include "pch.h"
#include "CPublic.h"
CString CPublic::m_id;
CString CPublic::m_pass;
BOOL CPublic::ismem=false;
CString CPublic::m_bid;
CString CPublic::m_ORDER;
CString CPublic::m_PRICE;
CString CPublic::m_time;
CDatabase CPublic::db;
CRecordset CPublic::rs;
CRecordset CPublic::rs2;
CPublic::CPublic()
{
}

CPublic::~CPublic()
{
}
