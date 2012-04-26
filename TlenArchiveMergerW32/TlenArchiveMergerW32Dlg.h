
// TlenArchiveMergerW32Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"


// CTlenArchiveMergerW32Dlg dialog
class CTlenArchiveMergerW32Dlg : public CDialog
{
// Construction
public:
	CTlenArchiveMergerW32Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TLENARCHIVEMERGERW32_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton BTN_MERGE;
	afx_msg void OnBnClickedButton5();
	void Fill_dat1(CFile* fs);
	void Fill_dat2(CFile* fs);
	void Fill_idx1(CFile* fs);
	void Fill_idx2(CFile* fs);
	void Fill_dat1_idx(CFile* fs);
	void Fill_dat2_idx(CFile* fs);
	bool Check_idx1(int id);
	bool Check_idx2(int id);
	void IDX_FIX(void);
	void Fill_tmp_idx(void);
	void Fill_tmpdat_idx(void);
	void Generuj_out(wchar_t *idx, wchar_t* dat);
	void ID_fix_dat(void);
	bool CheckInd(int id);
	void Fill_tmpdat(void);
	void GenerujIDX_dat(wchar_t *idx, wchar_t *dat);
	bool ChkIdx(int id);
	char* Kto_pisze(int flag);
	afx_msg void OnBnClickedButton6();
	bool ChkOff(int id);
	CButton CHECK_IDX_INCL;
	void ButtonsInitialize(void);
	
	CEdit EDIT_DAT1_PATH;
	CEdit EDIT_DAT2_PATH;
	CProgressCtrl ProgressMerge;
	CStatic StaticMerge;
	CEdit EditResArch;
	CString arch1, arch2, arch3;
	afx_msg void OnSelectFolder1();
	afx_msg void OnSelectFolder2();
	afx_msg void OnSelectFolder3();



};
