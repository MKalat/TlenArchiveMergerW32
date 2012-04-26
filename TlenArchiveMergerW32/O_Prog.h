#pragma once


// O_Prog dialog

class O_Prog : public CDialog
{
	DECLARE_DYNAMIC(O_Prog)

public:
	O_Prog(CWnd* pParent = NULL);   // standard constructor
	virtual ~O_Prog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
