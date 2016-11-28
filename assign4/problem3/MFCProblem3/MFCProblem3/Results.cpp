// Results.cpp : implementation file
//

#include "stdafx.h"
#include "MFCProblem3.h"
#include "Results.h"
#include "afxdialogex.h"
#include <string.h>


// Results dialog

IMPLEMENT_DYNAMIC(Results, CDialogEx)

Results::Results(CWnd* pParent /*=NULL*/)
	: CDialogEx(Results::IDD, pParent)
	, res(_T("RESULTS HERE"))
{

}

Results::~Results()
{
}

BOOL Results::OnInitDialog(){
	GetDlgItem(IDC_EDIT2)->SetWindowText(Results::res);
	return true;

}
void Results::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Results, CDialogEx)
	ON_BN_CLICKED(IDOK, &Results::OnBnClickedOk)
END_MESSAGE_MAP()


// Results message handlers


void Results::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
