
// MFCProblem3View.h : interface of the CMFCProblem3View class
//

#pragma once


class CMFCProblem3View : public CView
{
protected: // create from serialization only
	CMFCProblem3View();
	DECLARE_DYNCREATE(CMFCProblem3View)

// Attributes
public:
	CMFCProblem3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCProblem3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCProblem3View.cpp
inline CMFCProblem3Doc* CMFCProblem3View::GetDocument() const
   { return reinterpret_cast<CMFCProblem3Doc*>(m_pDocument); }
#endif

