﻿
// ordersysView.h: CordersysView 类的接口
//

#pragma once


class CordersysView : public CView
{
protected: // 仅从序列化创建
	CordersysView() noexcept;
	DECLARE_DYNCREATE(CordersysView)

// 特性
public:
	CordersysDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CordersysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ordersysView.cpp 中的调试版本
inline CordersysDoc* CordersysView::GetDocument() const
   { return reinterpret_cast<CordersysDoc*>(m_pDocument); }
#endif

