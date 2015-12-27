
// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL.h"
#endif

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// COpenGLView construction/destruction

COpenGLView::COpenGLView()
{
}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.SendMoreData();
	m_glRenderer.DrawScene(m_dc.get());
}


// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


void COpenGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_glRenderer.PrepareScene();
}

void COpenGLView::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMER_REDRAW:
		m_glRenderer.SendMoreData();
		m_glRenderer.DrawScene(m_dc.get());
		break;
	default:
		break;
	}
}

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_dc.reset(new CClientDC(this));
	m_glRenderer.CreateGLContext(m_dc.get());
	SetTimer(TIMER_REDRAW, REDRAW_TIME, 0);

	return 0;
}


void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	m_glRenderer.DestroyScene();
	KillTimer(TIMER_REDRAW);
}


void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_glRenderer.Reshape(cx, cy);
}


BOOL COpenGLView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
