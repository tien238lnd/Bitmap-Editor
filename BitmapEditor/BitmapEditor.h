
// BitmapEditor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBitmapEditor2App:
// See BitmapEditor.cpp for the implementation of this class
//

class CBitmapEditor2App : public CWinApp
{
public:
	CBitmapEditor2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBitmapEditor2App theApp;
