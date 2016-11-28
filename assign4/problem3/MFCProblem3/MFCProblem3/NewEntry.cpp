// NewEntry.cpp : implementation file
//

#include "stdafx.h"
#include "MFCProblem3.h"
#include "NewEntry.h"
#include "afxdialogex.h"
#include "Person.h"
#include "Results.h"
#include "MFCProblem3Doc.h"

using namespace std;
// NewEntry dialog

IMPLEMENT_DYNAMIC(NewEntry, CDialogEx)

NewEntry::NewEntry(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewEntry::IDD, pParent)
{

}

NewEntry::~NewEntry()
{
}

void NewEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, person_name);
}


BEGIN_MESSAGE_MAP(NewEntry, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewEntry::OnBnClickedOk)
END_MESSAGE_MAP()


// NewEntry message handlers

string NewEntry::convertToString(CString s) {
	string ret = "";
	for (int i = 0; i < s.GetLength(); i++){
		ret += s.GetAt(i);
	}
	return ret;
}
void NewEntry::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString pName;
	GetDlgItemText(IDC_NAME, pName);
	string pn =convertToString(pName);
	
	CString stnum;
	GetDlgItemText(IDC_STNUM, stnum);
	string stn = convertToString(stnum);

	CString stname;
	GetDlgItemText(IDC_STNAME, stname);
	string stna = convertToString(stname);
	
	CString city;
	GetDlgItemText(IDC_CITY, city);
	string ci = convertToString(city);
	
	CString state;
	GetDlgItemText(IDC_STATE, state);
	string sta = convertToString(state);
	
	CString zip;
	GetDlgItemText(IDC_ZIP, zip);
	string z = convertToString(zip);

	person *p = new person(pn);
	p->set_values(stn,stna,ci,sta,z);
	//CMFCProblem3Doc::people[pn] = p;
	CDialogEx::OnOK();
}

