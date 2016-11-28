
// MFCProblem3Doc.h : interface of the CMFCProblem3Doc class
//


#pragma once
#include <map>
#include "Person.h"

class CMFCProblem3Doc : public CDocument
{
protected: // create from serialization only
	CMFCProblem3Doc();
	DECLARE_DYNCREATE(CMFCProblem3Doc)

// Attributes
public:


// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCProblem3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOptionNewEntry();
	afx_msg void OnOptionsSearch();
	afx_msg void OnOptionsResults();
	static map<string, person*> people;
};
