// SearchEntries.cpp : implementation file
//

#include "stdafx.h"
#include "MFCProblem3.h"
#include "SearchEntries.h"
#include "afxdialogex.h"
#include "MFCProblem3Doc.h"
#include "Results.h"
#include "Windows.h"


// SearchEntries dialog

IMPLEMENT_DYNAMIC(SearchEntries, CDialogEx)

SearchEntries::SearchEntries(CWnd* pParent /*=NULL*/)
	: CDialogEx(SearchEntries::IDD, pParent)
{

}

SearchEntries::~SearchEntries()
{
}

void SearchEntries::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SearchEntries, CDialogEx)
	ON_BN_CLICKED(IDOK, &SearchEntries::OnBnClickedOk)
END_MESSAGE_MAP()


// SearchEntries message handlers

string convertToString(CString s) {
	string ret = "";
	for (int i = 0; i < s.GetLength(); i++){
		ret += s.GetAt(i);
	}
	return ret;
}

void SearchEntries::OnBnClickedOk()
{
	CString pName;
	GetDlgItemText(IDC_EDIT1, pName);
	string pn = convertToString(pName);

	Results *dialog = new Results();
	dialog->DoModal();
	
	delete dialog;
	/*string msg="";

	map<string, person* > ::iterator iter = CMFCProblem3Doc::people.find(pn);
	if (iter != CMFCProblem3Doc::people.end()) {
		msg=iter->second->printRecord();
	}
	else {
		msg="That person is not in the records\n";
	}*/
	

	CDialogEx::OnOK();
}



