
// TlenArchiveMergerW32.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTlenArchiveMergerW32App:
// See TlenArchiveMergerW32.cpp for the implementation of this class
//

class CTlenArchiveMergerW32App : public CWinAppEx
{
public:
	CTlenArchiveMergerW32App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTlenArchiveMergerW32App theApp;