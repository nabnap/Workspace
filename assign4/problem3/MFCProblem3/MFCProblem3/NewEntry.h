#pragma once
#include "afxwin.h"
#include <string>


// NewEntry dialog

class NewEntry : public CDialogEx
{
	DECLARE_DYNAMIC(NewEntry)

public:
	NewEntry(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewEntry();
	

// Dialog Data
	enum { IDD = IDD_NEWENTRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
protected:
	CEdit person_name;
public:
	std::string convertToString(CString s);
};
