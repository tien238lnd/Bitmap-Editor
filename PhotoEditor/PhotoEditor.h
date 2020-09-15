
// PhotoEditor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhotoEditor2App:
// See PhotoEditor.cpp for the implementation of this class
//

class CPhotoEditor2App : public CWinApp
{
public:
	CPhotoEditor2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPhotoEditor2App theApp;
