
// TlenArchiveMergerW32Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "str_arch.h"
#include "TlenArchiveMergerW32.h"
#include "TlenArchiveMergerW32Dlg.h"
#include "O_Prog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTlenArchiveMergerW32Dlg dialog

CHTDAT chat_dat;
CHTIDX chat_idx;

CArray <CHTDAT,CHTDAT> cht_dat1arr;
CArray <CHTDAT,CHTDAT> cht_dat2arr;

CArray <CHTIDX,CHTIDX> cht_idx1arr;
CArray <CHTIDX,CHTIDX> cht_idx2arr;

CArray <CHTDAT,CHTDAT> chtDAT_ret;
CArray <CHTIDX,CHTIDX> chtIDX_ret;

CArray <int,int> indeks;
CArray <int,int> testoff;




CTlenArchiveMergerW32Dlg::CTlenArchiveMergerW32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTlenArchiveMergerW32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	

}

void CTlenArchiveMergerW32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON5, BTN_MERGE);

	DDX_Control(pDX, IDC_CHECK1, CHECK_IDX_INCL);
	DDX_Control(pDX, IDC_EDIT1, EDIT_DAT1_PATH);
	DDX_Control(pDX, IDC_EDIT2, EDIT_DAT2_PATH);
	DDX_Control(pDX, IDC_PROGRESS_MERGE, ProgressMerge);
	DDX_Control(pDX, IDC_STATIC_MERGE, StaticMerge);
	DDX_Control(pDX, IDC_EDIT_ARCHRES, EditResArch);
	DDX_Text(pDX, IDC_EDIT1, arch1);
	DDX_Text(pDX, IDC_EDIT2, arch2);
	DDX_Text(pDX, IDC_EDIT_ARCHRES, arch3);

}

BEGIN_MESSAGE_MAP(CTlenArchiveMergerW32Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5, &CTlenArchiveMergerW32Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTlenArchiveMergerW32Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelectFolder1)
	ON_BN_CLICKED(IDC_BUTTON2, OnSelectFolder2)
	ON_BN_CLICKED(IDC_BUTTON3, OnSelectFolder3)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CTlenArchiveMergerW32Dlg message handlers

BOOL CTlenArchiveMergerW32Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CTlenArchiveMergerW32Dlg::ButtonsInitialize();
	this->ProgressMerge.SetRange(0,10);
	/*RECT rct;
	rct.top = 23;
	rct.left = 7;
	rct.right = 298;
	rct.bottom = 14;
	CDialog::MapDialogRect(&rct);
	this->EDIT_DAT1_PATH.Create(WS_CHILD | WS_VISIBLE,rct,this,1001);
	rct.top = 47;
	rct.left = 7;
	rct.right = 298;
	rct.bottom = 14;
	CDialog::MapDialogRect(&rct);
	this->EDIT_DAT2_PATH.Create(WS_CHILD | WS_VISIBLE,rct,this,1002);
	rct.top = 98;
	rct.left = 7;
	rct.right = 298;
	rct.bottom = 14;
	CDialog::MapDialogRect(&rct);
	this->EditResArch.Create(WS_CHILD | WS_VISIBLE,rct,this,1003);*/
	/*EDIT_DAT1_PATH.EnableFolderBrowseButton();
	EDIT_DAT2_PATH.EnableFolderBrowseButton();
	EditResArch.EnableFolderBrowseButton();*/
	/*UpdateData(FALSE);*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTlenArchiveMergerW32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTlenArchiveMergerW32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTlenArchiveMergerW32Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here

	CFile fs_cht_dat1 = NULL, fs_cht_dat2 = NULL, fs_cht_idx1 = NULL, fs_cht_idx2 = NULL; 
	CFileStatus stat;
	// progress bar initialize

	wchar_t dat1[256], dat2[256], idx1[256], idx2[256], dir1[256], dir2[256];
	wchar_t res_dat[256], res_idx[256], res_dir[256];
	if (this->EDIT_DAT1_PATH.GetWindowTextLength() > 0)
	{
		EDIT_DAT1_PATH.GetWindowText(dir1,256);
	}
	else
	{
		return;
	}
	if (this->EDIT_DAT2_PATH.GetWindowTextLength() > 0)
	{
		EDIT_DAT2_PATH.GetWindowText(dir2,256);
	}
	else
	{
		return;
	}
	if (this->EditResArch.GetWindowTextLength() > 0)
	{
		this->EditResArch.GetWindowText(res_dir,256);
	}
	else
	{
		return;
	}
	
	if (res_dir[_tcslen(res_dir)] == '\\')
	{
		_tcscpy(res_dat,res_dir);
		_tcscat(res_dat,_T("chats.dat"));
		_tcscpy(res_idx,res_dir);
		_tcscat(res_idx,_T("chats.idx"));
	}
	else
	{
		_tcscpy(res_dat,res_dir);
		_tcscat(res_dat,_T("\\chats.dat"));
		_tcscpy(res_idx,res_dir);
		_tcscat(res_idx,_T("\\chats.idx"));

	}

	if (dir1[_tcslen(dir1)] == '\\')
	{
		_tcscpy(dat1,dir1);
		_tcscat(dat1,_T("chats.dat"));
		_tcscpy(idx1,dir1);
		_tcscat(idx1,_T("chats.idx"));
	}
	else
	{
		_tcscpy(dat1,dir1);
		_tcscat(dat1,_T("\\chats.dat"));
		_tcscpy(idx1,dir1);
		_tcscat(idx1,_T("\\chats.idx"));

	}

	if (dir2[_tcslen(dir2)] == '\\')
	{
		_tcscpy(dat2,dir2);
		_tcscat(dat2,_T("chats.dat"));
		_tcscpy(idx2,dir2);
		_tcscat(idx2,_T("chats.idx"));
	}
	else
	{
		_tcscpy(dat2,dir2);
		_tcscat(dat2,_T("\\chats.dat"));
		_tcscpy(idx2,dir2);
		_tcscat(idx2,_T("\\chats.idx"));
	}

	this->ProgressMerge.SetPos(1);
	this->StaticMerge.SetWindowText(_T("Postêp operacji ... 10%"));

	if ((fs_cht_dat1.GetStatus(dat1,stat)) & (fs_cht_dat2.GetStatus(dat2,stat)))
	{
		fs_cht_dat1.Open(dat1,CFile::modeRead | CFile::shareDenyNone);
		fs_cht_dat2.Open(dat2,CFile::modeRead | CFile::shareDenyNone);
		this->ProgressMerge.SetPos(2);
		this->StaticMerge.SetWindowText(_T("Postêp operacji ... 20%"));
		if ((fs_cht_idx1.GetStatus(idx1,stat)) & (fs_cht_idx2.GetStatus(idx2,stat)) || CHECK_IDX_INCL.GetCheck() == BST_UNCHECKED )
		{
			fs_cht_idx1.Open(idx1,CFile::modeRead | CFile::shareDenyNone);
			fs_cht_idx2.Open(idx2,CFile::modeRead | CFile::shareDenyNone);
			this->ProgressMerge.SetPos(3);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 30%"));

			Fill_idx1(&fs_cht_idx1);
			Fill_idx2(&fs_cht_idx2);
			this->ProgressMerge.SetPos(4);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 40%"));
			Fill_dat1_idx(&fs_cht_dat1);
			Fill_dat2_idx(&fs_cht_dat2);
			this->ProgressMerge.SetPos(5);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 50%"));

			IDX_FIX();
			this->ProgressMerge.SetPos(6);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 60%"));

			Fill_tmp_idx();
			Fill_tmpdat_idx();
			this->ProgressMerge.SetPos(7);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 70%"));
			Generuj_out(res_idx,res_dat);
			this->ProgressMerge.SetPos(10);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 100%"));
			MessageBox(_T("Operacja ³¹czenia zakoñczona sukcesem !"),_T("Tlen Archive Merger"),MB_OK);
			this->ProgressMerge.SetPos(0);
			this->StaticMerge.SetWindowText(_T("Postêp operacji"));
			
			fs_cht_idx1.Close();
            fs_cht_idx2.Close();
            fs_cht_dat1.Close();
            fs_cht_dat2.Close();  

			cht_dat1arr.RemoveAll();
			cht_dat2arr.RemoveAll();
			cht_idx1arr.RemoveAll();
			cht_idx2arr.RemoveAll();

			chtDAT_ret.RemoveAll();
			chtIDX_ret.RemoveAll();

		}
		else
		{
			Fill_dat1(&fs_cht_dat1);
			Fill_dat2(&fs_cht_dat2);
			this->ProgressMerge.SetPos(5);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 50%"));
			ID_fix_dat();
			this->ProgressMerge.SetPos(6);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 60%"));
            Fill_tmpdat();
			this->ProgressMerge.SetPos(7);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 70%"));
			GenerujIDX_dat(res_idx,res_dat);
			this->ProgressMerge.SetPos(10);
			this->StaticMerge.SetWindowText(_T("Postêp operacji ... 100%"));
			MessageBox(_T("Operacja ³¹czenia archiwów zakoñczona sukcesem !"),_T("Tlen Archive Merger"),MB_OK);
			this->ProgressMerge.SetPos(0);
			this->StaticMerge.SetWindowText(_T("Postêp operacji"));

			fs_cht_dat1.Close();
            fs_cht_dat2.Close();

			cht_dat1arr.RemoveAll();
			cht_dat2arr.RemoveAll();
			chtDAT_ret.RemoveAll();
			chtIDX_ret.RemoveAll(); 

		}
	}
	else
	{
		MessageBox(_T("Nie wskazano plików rozmów - program nie mo¿e kontynuowaæ"),_T("Tlen Archive Merger"),MB_OK);

	}
	
}

void CTlenArchiveMergerW32Dlg::Fill_dat1(CFile *fs)
{
	int bad_off = 0;
	
	for (long i =0; i < fs->GetLength(); )
	{
		try
		{
			
			fs->Seek(i,CFile::begin);
			fs->Read(&chat_dat.time,sizeof(double));
			fs->Read(&chat_dat.flags,sizeof(int));
			fs->Read(&chat_dat.size,sizeof(int));
			fs->Read(&chat_dat.ID,sizeof(int));
			fs->Read(&chat_dat.unknown,sizeof(int));

			if ((chat_dat.time < 0) || (chat_dat.flags < 0) || (chat_dat.size < 0) || (chat_dat.ID <= 0) || (chat_dat.unknown < 0))
			{
			
				AfxThrowFileException(CFileException::genericException,-1,NULL);
				
			}
			else
			{

				
				char* ch = new char[chat_dat.size];
				fs->Read(ch,chat_dat.size);
				chat_dat.msg = ch;
				delete [] ch;
				cht_dat1arr.Add(chat_dat);

				i = i + 24 + chat_dat.size;
			}
		}
		catch (CMemoryException *e)
		{
			
			e->Delete(); 

		}
		catch (CFileException *e)
		{
			i = i + 1;
			bad_off = bad_off + 1;
			if (bad_off == 1)
			{
					CString err_flags, err_size, err_id;
					wchar_t tmp_str[100];
					_itow(chat_dat.flags,tmp_str,10);
					err_flags = tmp_str;
					_itow(chat_dat.size,tmp_str,10);
					err_size = tmp_str;
					_itow(chat_dat.ID,tmp_str,10);
					err_id = tmp_str;

					MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.dat!. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
					
				
			}
			//MessageBox("Wyst¹pi³ b³¹d odczytu pliku ! Plik prawdopodobnie jest uszkodzony","Tlen Archive Merger",MB_OK);
			e->Delete(); 
			break;

		}
	}
}

void CTlenArchiveMergerW32Dlg::Fill_dat2(CFile *fs)
{
	int bad_off = 0;
	
	for (long i = 0; i <fs->GetLength(); )
	{
		try
		{
			
			fs->Seek(i,CFile::begin);
			fs->Read(&chat_dat.time,sizeof(double));
			fs->Read(&chat_dat.flags,sizeof(int));
			fs->Read(&chat_dat.size,sizeof(int));
			fs->Read(&chat_dat.ID,sizeof(int));
			fs->Read(&chat_dat.unknown,sizeof(int));

			if ((chat_dat.time < 0) || (chat_dat.flags < 0) || (chat_dat.size < 0) || (chat_dat.ID <= 0) || (chat_dat.unknown < 0))
			{
				
				AfxThrowFileException(CFileException::genericException,-1,NULL);
				
			}
			else
			{

				char* ch = new char[chat_dat.size];
				fs->Read(ch,chat_dat.size);
				chat_dat.msg = ch;
				delete [] ch;
				cht_dat2arr.Add(chat_dat);

				i = i + 24 + chat_dat.size;
			}
		}
		catch (CMemoryException *e)
		{
			
			//i++;
			e->Delete(); 
		}
		catch (CFileException *e)
		{

			i = i + 1;
			bad_off = bad_off + 1;
			if (bad_off == 1)
			{
					CString err_flags, err_size, err_id;
					wchar_t tmp_str[100] ;
					_itow(chat_dat.flags,tmp_str,10);
					err_flags = tmp_str;
					_itow(chat_dat.size,tmp_str,10);
					err_size = tmp_str;
					_itow(chat_dat.ID,tmp_str,10);
					err_id = tmp_str;

					MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.dat !. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
					
				
			}
			//MessageBox("Wyst¹pi³ b³¹d odczytu pliku ! Plik prawdopodobnie jest uszkodzony","Tlen Archive Merger",MB_OK);
			e->Delete(); 
			break;

		}


	}


}

void CTlenArchiveMergerW32Dlg::Fill_idx1(CFile *fs)
{
	for (long i = 0; i <fs->GetLength(); )
	{
		try
		{
			fs->Seek(i,CFile::begin);
			fs->Read(&chat_idx,sizeof(chat_idx));
		
			if (chat_idx.count != -1)
			{
				cht_idx1arr.Add(chat_idx);
			}

			i = i + 56;
		}
		catch (CFileException *e)
		{
			CString err_flags, err_size, err_id;
			wchar_t tmp_str[100];
			_itow(chat_idx.flags,tmp_str,10);
			err_flags = tmp_str;
			_itow(chat_idx.offset,tmp_str,10);
			err_size = tmp_str;
			_itow(chat_idx.ID,tmp_str,10);
			err_id = tmp_str;

			MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.idx!. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
			e->Delete(); 
			break;
		}

	}


}

void CTlenArchiveMergerW32Dlg::Fill_idx2(CFile *fs)
{
	for (long i = 0; i <fs->GetLength(); )
	{
		try
		{
			fs->Seek(i, CFile::begin);
			fs->Read(&chat_idx,sizeof(chat_idx));

			if (chat_idx.count != -1)
			{
				cht_idx2arr.Add(chat_idx);
			}

			i = i + 56;
		}
		catch (CFileException *e)
		{
			CString err_flags, err_size, err_id;
			wchar_t tmp_str[100];
			_itow(chat_idx.flags,tmp_str,10);
			err_flags = tmp_str;
			_itow(chat_idx.offset,tmp_str,10);
			err_size = tmp_str;
			_itow(chat_idx.ID,tmp_str,10);
			err_id = tmp_str;

			MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.idx !. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
			e->Delete(); 
			break;		
		}
	}

}

void CTlenArchiveMergerW32Dlg::Fill_dat1_idx(CFile *fs)
{
	int bad_off = 0;
	
	long y = 0;
	for (long i = 0; i < cht_idx1arr.GetSize(); i++ )
	{
		bad_off = 0;
		y = cht_idx1arr[i].offset; 
		for (int x = 0; x <cht_idx1arr[i].count; x++)
		{
			try
			{
				
				fs->Seek(y,CFile::begin); 
				fs->Read(&chat_dat.time,sizeof(double));
				fs->Read(&chat_dat.flags,sizeof(int));
				fs->Read(&chat_dat.size,sizeof(int));
				fs->Read(&chat_dat.ID,sizeof(int));
				fs->Read(&chat_dat.unknown,sizeof(int));

				if ((chat_dat.time < 0) || (chat_dat.flags < 0) || (chat_dat.size < 0) || (chat_dat.ID <= 0) || (chat_dat.unknown < 0))
				{
					AfxThrowFileException(CFileException::genericException,-1,NULL);
					
				}
				else
				{


					char* ch = new char[chat_dat.size];
					fs->Read(ch,chat_dat.size);
					chat_dat.msg = ch;
					delete [] ch;
		
					if (cht_idx1arr[i].ID == chat_dat.ID)
					{
						cht_dat1arr.Add(chat_dat); 
					}
					else
					{
						x = x -1;
					}
					y = y + 24 + chat_dat.size;
				}
			}
			catch (CMemoryException *e)
			{
				//x = x - 1;
				//y++;
				e->Delete(); 
			}
			catch (CFileException *e)
			{
				
				x = x - 1;
				y = y + 1;
				bad_off = bad_off + 1;
				if (bad_off == 1)
				{
					CString err_flags, err_size, err_id;
					wchar_t tmp_str[100];
					_itow(chat_dat.flags,tmp_str,10);
					err_flags = tmp_str;
					_itow(chat_dat.size,tmp_str,10);
					err_size = tmp_str;
					_itow(chat_dat.ID,tmp_str,10);
					err_id = tmp_str;

					MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.dat!. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
					
				}
				//char str_buff[100];
				//str_buff = "Wyst¹pi³ b³¹d odczytu pliku !" ;
				//ltoa(y,str_buff,10);
				//MessageBox(str_buff ,"Tlen Archive Merger",MB_OK);
				e->Delete(); 
				break;
			}
		}
	}
	

}

void CTlenArchiveMergerW32Dlg::Fill_dat2_idx(CFile *fs)
{
	int bad_off = 0;
	
	long y = 0;
	for (long i = 0; i < cht_idx2arr.GetSize(); i++ )
	{
		bad_off = 0;
		y = cht_idx2arr[i].offset; 
		for (int x = 0; x <cht_idx2arr[i].count; x++)
		{
			try
			{
				
				fs->Seek(y,CFile::begin); 
				fs->Read(&chat_dat.time,sizeof(double));
				fs->Read(&chat_dat.flags,sizeof(int));
				fs->Read(&chat_dat.size,sizeof(int));
				fs->Read(&chat_dat.ID,sizeof(int));
				fs->Read(&chat_dat.unknown,sizeof(int));

				if ((chat_dat.time < 0) || (chat_dat.flags < 0) || (chat_dat.size < 0) || (chat_dat.ID <= 0) || (chat_dat.unknown < 0))
				{
					AfxThrowFileException(CFileException::genericException,-1,NULL);
					
				}
				else
				{
					
					char* ch = new char[chat_dat.size];
					fs->Read(ch,chat_dat.size);
					chat_dat.msg = ch;
					delete [] ch;
					if (cht_idx2arr[i].ID == chat_dat.ID)
					{
						cht_dat2arr.Add(chat_dat); 
					}
					else
					{
						x = x -1;
					}
					y = y + 24 + chat_dat.size;
				}

			}
			catch (CMemoryException *e)
			{
				//x = x - 1;
				//y++;
				e->Delete(); 
			}
			catch (CFileException *e)
			{
				x = x - 1;
				y = y + 1;
				bad_off = bad_off + 1;
				if (bad_off == 1)
				{
					CString err_flags, err_size, err_id;
					wchar_t tmp_str[100];
					_itow(chat_dat.flags,tmp_str,10);
					err_flags = tmp_str;
					_itow(chat_dat.size,tmp_str,10);
					err_size = tmp_str;
					_itow(chat_dat.ID,tmp_str,10);
					err_id = tmp_str;

					MessageBox(_T("Wyst¹pli³ b³¹d w pliku chats.dat !. Flagi : ") + err_flags + _T(" Rozmiar : ") + err_size + _T(" ID : ") + err_id,_T("Tlen Archive Merger"),MB_OK);
					

				}
				//MessageBox("Wyst¹pi³ b³¹d odczytu pliku !","Tlen Archive Merger",MB_OK);
				e->Delete(); 
				break;
			}
		}
	}
	
}

bool CTlenArchiveMergerW32Dlg::Check_idx1(int id) 
{
	for (long i = 0; i < cht_idx1arr.GetCount(); i++) 
	{
		if (cht_idx1arr.ElementAt(i).ID == id)
		{
			return true;
		}
	}
	return false;
}

bool CTlenArchiveMergerW32Dlg::Check_idx2(int id) 
{
	for (long i = 0; i < cht_idx2arr.GetCount(); i++) 
	{
		if (cht_idx2arr.ElementAt(i).ID == id)
		{
			return true;
		}
	}
	return false;
}

void CTlenArchiveMergerW32Dlg::IDX_FIX(void)
{
	int hi_id = 0;
 // TODO: Tutaj jest b³¹d poprawiania w drugim pliku rozmów, kiedy w archiwum sa usuniete rozmowy
	hi_id = cht_idx1arr.GetAt(cht_idx1arr.GetUpperBound()).ID;

	int id_tmp = 0;
	int new_id = 0;
	
	for (int i = 0; i< cht_idx2arr.GetSize(); i++)
	{
		id_tmp = cht_idx2arr[i].ID; 
		new_id = id_tmp + hi_id; 
		// poprawianie ID rozmowy w pliku indeksu
		cht_idx2arr[i].ID = new_id;
	
	}
	new_id = 0;
	for (int x = 0; x< cht_dat2arr.GetSize(); x++)
	{
		id_tmp = cht_dat2arr[x].ID; 
		new_id = id_tmp + hi_id;
		cht_dat2arr[x].ID = new_id;  
				// poprawianie ID rozmowy w 2 pliku rozmów w zwi¹zku ze zmian¹ ID w 2 pliku indeksu
			

	}
}

void CTlenArchiveMergerW32Dlg::Fill_tmp_idx(void) 
{
	for (long i = 0; i < cht_idx1arr.GetSize(); i++)
	{
		chtIDX_ret.Add(cht_idx1arr.GetAt(i));  
	}
	for (long i = 0; i < cht_idx2arr.GetSize(); i++)
	{
		chtIDX_ret.Add(cht_idx2arr.GetAt(i));  
	}

}

void CTlenArchiveMergerW32Dlg::Fill_tmpdat_idx(void)
{
	for (long i = 0; i< cht_dat1arr.GetSize(); i++)
	{
		chtDAT_ret.Add(cht_dat1arr.GetAt(i));  
	}
	for (long i = 0; i < cht_dat2arr.GetSize(); i++)
	{
		chtDAT_ret.Add(cht_dat2arr.GetAt(i));  
	}

}

void CTlenArchiveMergerW32Dlg::Generuj_out(wchar_t* idx, wchar_t* dat)
{
	CFile fs_dat, fs_idx;
	int testid = 0, testdatid = 0;
	ULONGLONG pos = 0;
	
	
	fs_dat.Open(dat,CFile::modeCreate);
	fs_dat.Close();
	fs_dat.Open(dat,CFile::modeWrite | CFile::shareDenyNone);  

	fs_idx.Open(idx,CFile::modeCreate);
	fs_idx.Close();
	fs_idx.Open(idx,CFile::modeWrite | CFile::shareDenyNone);
	
	
	for (long i = 0; i < chtDAT_ret.GetSize(); i++)
	{
		testdatid = chtDAT_ret[i].ID;
		fs_dat.Seek(pos,CFile::begin);
		for (long x = 0 ; x < chtIDX_ret.GetSize(); x++)
		{
			testid = chtIDX_ret[x].ID;
			if (chtIDX_ret[x].ID == chtDAT_ret[i].ID)
			{
				if (ChkOff(chtIDX_ret[x].ID) == false)
				{
				
					chtIDX_ret[x].offset = pos;
					testoff.Add(chtIDX_ret[x].ID);  
				}
			}
		}
	
		fs_dat.Write(&chtDAT_ret.GetAt(i).time,sizeof(double));
		fs_dat.Write(&chtDAT_ret.GetAt(i).flags,sizeof(int));
		fs_dat.Write(&chtDAT_ret.GetAt(i).size,sizeof(int));
		fs_dat.Write(&chtDAT_ret.GetAt(i).ID,sizeof(int));
		fs_dat.Write(&chtDAT_ret.GetAt(i).unknown,sizeof(int));
		
		CStringA str;
		str = chtDAT_ret[i].msg;
		
		char* ch = new char[str.GetLength()];
		strcpy(ch,str);
		fs_dat.Write(ch, str.GetLength());
		delete [] ch;
		pos = pos + 24 + chtDAT_ret[i].size; 
		
		

	}
	
	for (long i = 0; i< chtIDX_ret.GetSize(); i++)
	{
		fs_idx.Write(&chtIDX_ret.GetAt(i),56); // TODO : zmienic offset na nowy po po³aczeniu pliku dla rekordów z drugiego archiwum

	}
	
	fs_dat.Close();
	fs_idx.Close(); 
}

void CTlenArchiveMergerW32Dlg::ID_fix_dat(void)
{
	
	for (long i = 0; i <cht_dat1arr.GetSize(); i++) 
	{
		if (CheckInd(cht_dat1arr.GetAt(i).ID) == false)
		{
			indeks.Add(cht_dat1arr.GetAt(i).ID);   
		}

	}
	int hi_id = indeks[indeks.GetUpperBound()];
	for (long x = 0; x < cht_dat2arr.GetSize(); x++)
	{
		cht_dat2arr[x].ID = cht_dat2arr[x].ID + hi_id;

	}


}

bool CTlenArchiveMergerW32Dlg::CheckInd(int id) 
{
	for (int i = 0;i< indeks.GetSize(); i++)
	{
		if (indeks[i] == id)
		{
			return true;
		}

	}
	return false;

}



void CTlenArchiveMergerW32Dlg::Fill_tmpdat(void) 
{
	for (long i = 0;i< cht_dat1arr.GetSize();i++)
	{
		chtDAT_ret.Add(cht_dat1arr.GetAt(i));  
	}
	for (long x = 0;x < cht_dat2arr.GetSize(); x++)
	{
		chtDAT_ret.Add(cht_dat2arr.GetAt(x));  
	}

}

void CTlenArchiveMergerW32Dlg::GenerujIDX_dat(wchar_t *idx, wchar_t *dat) 
{
	CFile fs_dat, fs_idx;
	CFileStatus fs_stat;
	ULONGLONG pos = 0;
	if (!((fs_dat.GetStatus(dat,fs_stat)) & (fs_idx.GetStatus(idx,fs_stat))))
	{
		fs_dat.Open(dat,CFile::modeCreate);
		fs_dat.Close();
		fs_dat.Open(dat,CFile::modeWrite | CFile::shareDenyNone);

		fs_idx.Open(idx,CFile::modeCreate);
		fs_idx.Close();
		fs_idx.Open(idx,CFile::modeWrite | CFile::shareDenyNone);  

		
		for (long i = 0; i < chtDAT_ret.GetSize(); i++)
		{
			fs_dat.Seek(pos,CFile::begin);  
			if (!(ChkIdx(chtDAT_ret.GetAt(i).ID)))
			{
				strcpy(chat_idx.name,Kto_pisze(chtDAT_ret.GetAt(i).flags));
				strcpy(chat_idx.network,"NNNNNN");
				chat_idx.time = chtDAT_ret.GetAt(i).time;
				chat_idx.flags = 0;
				chat_idx.offset = pos;
				chat_idx.count = 999999;
				chat_idx.ID = chtDAT_ret.GetAt(i).ID;

				chtIDX_ret.Add(chat_idx); 

			}
			fs_dat.Write(&chtDAT_ret[i].time,sizeof(double));
			fs_dat.Write(&chtDAT_ret[i].flags,sizeof(int));
			fs_dat.Write(&chtDAT_ret[i].size,sizeof(int));
			fs_dat.Write(&chtDAT_ret[i].ID,sizeof(int));
			fs_dat.Write(&chtDAT_ret[i].unknown,sizeof(int));
			
			char* ch = new char[chtDAT_ret[i].size];
			CStringA str = chtDAT_ret[i].msg; 
			strcpy(ch,str);
			fs_dat.Write(ch, str.GetLength());
			delete [] ch;
			pos = pos + 24 + chtDAT_ret[i].size; 
			
		}
		for (long i = 0; i <chtIDX_ret.GetSize(); i++)
		{
			fs_idx.Write(&chtIDX_ret.GetAt(i),56);  
		}
		
		fs_dat.Close();
		fs_idx.Close(); 
	}
	
	
}

bool CTlenArchiveMergerW32Dlg::ChkIdx(int id)
{
	for (long i = 0; i <chtIDX_ret.GetSize(); i++)
	{
		if (chtIDX_ret.GetAt(i).ID == id)
		{
			return true;
		}
	}
	return false;
}

char* CTlenArchiveMergerW32Dlg::Kto_pisze(int flag)
{
	char tmp[100];
	CStringA test;
	_itoa(flag,tmp,10);
	test = tmp;
	if ((test.Find("1",test.GetLength() - 1) != -1) || (test.Find("3",test.GetLength() - 1) != -1) || (test.Find("5",test.GetLength() - 1) != -1) || (test.Find("7",test.GetLength() - 1) != -1) || (test.Find("9", test.GetLength() - 1) != -1))
	{
		return "JA                        ";
	}
	else
	{
		return "NIE-JA                    ";
	}
}

void CTlenArchiveMergerW32Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here

	// Wyœwietl okno - O programie.
	O_Prog prg;
	prg.DoModal(); 
}

bool CTlenArchiveMergerW32Dlg::ChkOff(int id) 
{
	for (int i =0; i < testoff.GetSize(); i++)
	{
		if (testoff[i] == id)
		{
			return true;
		}

	}
	return false;

}

void CTlenArchiveMergerW32Dlg::ButtonsInitialize(void) 
{
	/*
	RECT rct;
	rct.left = 7;
	rct.top = 22;
	rct.right = 291 + rct.left;
	rct.bottom = 14 + rct.top;
	
	EDIT_DAT1_PATH.Create(WS_CHILD, rct, this,1009); 
	
	EDIT_DAT1_PATH.EnableFolderBrowseButton();
	
	rct.left = 7;
	rct.top = 45;
	rct.right = 291 + rct.left;
	rct.bottom = 14 + rct.top; 
	EDIT_DAT2_PATH.Create(WS_CHILD, rct, this, 1010);
	
	EDIT_DAT2_PATH.EnableFolderBrowseButton();  
	*/

}
void CTlenArchiveMergerW32Dlg::OnSelectFolder1()
{
	if (theApp.GetShellManager()->BrowseForFolder(arch1, this, _T("c:\\")))
	{
		UpdateData(FALSE);
	}
}
void CTlenArchiveMergerW32Dlg::OnSelectFolder2()
{
	if (theApp.GetShellManager()->BrowseForFolder(arch2, this, _T("c:\\")))
	{
		UpdateData(FALSE);
	}
}
void CTlenArchiveMergerW32Dlg::OnSelectFolder3()
{
	if (theApp.GetShellManager()->BrowseForFolder(arch3, this, _T("c:\\")))
	{
		UpdateData(FALSE);
	}
}
