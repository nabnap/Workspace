
// MFCProblem3View.cpp : implementation of the CMFCProblem3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCProblem3.h"
#endif

#include "MFCProblem3Doc.h"
#include "MFCProblem3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCProblem3View

IMPLEMENT_DYNCREATE(CMFCProblem3View, CView)

BEGIN_MESSAGE_MAP(CMFCProblem3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCProblem3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCProblem3View construction/destruction

CMFCProblem3View::CMFCProblem3View()
{
	// TODO: add construction code here

}

CMFCProblem3View::~CMFCProblem3View()
{
}

BOOL CMFCProblem3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCProblem3View drawing

void CMFCProblem3View::OnDraw(CDC* /*pDC*/)
{
	CMFCProblem3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCProblem3View printing


void CMFCProblem3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCProblem3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCProblem3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCProblem3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCProblem3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCProblem3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCProblem3View diagnostics

#ifdef _DEBUG
void CMFCProblem3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCProblem3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCProblem3Doc* CMFCProblem3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCProblem3Doc)));
	return (CMFCProblem3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCProblem3View message handlers
