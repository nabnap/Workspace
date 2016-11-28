#pragma once


// Results dialog

class Results : public CDialogEx
{
	DECLARE_DYNAMIC(Results)
	virtual BOOL OnInitDialog();

public:
	Results(CWnd* pParent = NULL);   // standard constructor
	virtual ~Results();

// Dialog Data
	enum { IDD = IDD_RESULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString res;
};
