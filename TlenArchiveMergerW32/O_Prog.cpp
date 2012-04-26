// O_Prog.cpp : implementation file
//

#include "stdafx.h"
#include "TlenArchiveMergerW32.h"
#include "O_Prog.h"


// O_Prog dialog

IMPLEMENT_DYNAMIC(O_Prog, CDialog)

O_Prog::O_Prog(CWnd* pParent /*=NULL*/)
	: CDialog(O_Prog::IDD, pParent)
{

}

O_Prog::~O_Prog()
{
}

void O_Prog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(O_Prog, CDialog)
	ON_BN_CLICKED(IDOK, &O_Prog::OnBnClickedOk)
END_MESSAGE_MAP()


// O_Prog message handlers

void O_Prog::OnBnClickedOk()
{
	
	OnOK();
}
