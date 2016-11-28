
// MFCProblem3.h : main header file for the MFCProblem3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCProblem3App:
// See MFCProblem3.cpp for the implementation of this class
//

class CMFCProblem3App : public CWinAppEx
{
public:
	CMFCProblem3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCProblem3App theApp;
