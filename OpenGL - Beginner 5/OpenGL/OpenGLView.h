
// OpenGLView.h : interface of the COpenGLView class
//

#pragma once
#include "GLRenderer.h"

#include <memory>

class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	CGLRenderer m_glRenderer;
	std::unique_ptr<CDC> m_dc;

	enum Timings {
		TIMER_REDRAW = 1000,
		REDRAW_TIME = 200
	};
};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument() const
   { return reinterpret_cast<COpenGLDoc*>(m_pDocument); }
#endif

