
// MFCProblem3Doc.cpp : implementation of the CMFCProblem3Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCProblem3.h"
#endif

#include "MFCProblem3Doc.h"

#include <propkey.h>
#include "NewEntry.h"
#include "SearchEntries.h"
#include "Results.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCProblem3Doc

IMPLEMENT_DYNCREATE(CMFCProblem3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCProblem3Doc, CDocument)
	ON_COMMAND(ID_OPTION_NEW_ENTRY, &CMFCProblem3Doc::OnOptionNewEntry)
	ON_COMMAND(ID_OPTIONS_SEARCH, &CMFCProblem3Doc::OnOptionsSearch)
	ON_COMMAND(ID_OPTIONS_RESULTS, &CMFCProblem3Doc::OnOptionsResults)
END_MESSAGE_MAP()


// CMFCProblem3Doc construction/destruction

CMFCProblem3Doc::CMFCProblem3Doc()
{
	// TODO: add one-time construction code here

}

CMFCProblem3Doc::~CMFCProblem3Doc()
{
}

BOOL CMFCProblem3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCProblem3Doc serialization

void CMFCProblem3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCProblem3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCProblem3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCProblem3Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCProblem3Doc diagnostics

#ifdef _DEBUG
void CMFCProblem3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCProblem3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCProblem3Doc commands


void CMFCProblem3Doc::OnOptionNewEntry()
{
	NewEntry *dialog = new NewEntry();
	dialog->DoModal();

	delete dialog;
}


void CMFCProblem3Doc::OnOptionsSearch()
{
	SearchEntries *dialog = new SearchEntries();
	dialog->DoModal();

	delete dialog;
}


void CMFCProblem3Doc::OnOptionsResults()
{
	Results *dialog = new Results();
	dialog->DoModal();

	delete dialog;
}
