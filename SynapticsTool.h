
// SynapticsTool.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSynapticsToolApp:
// See SynapticsTool.cpp for the implementation of this class
//

class CSynapticsToolApp : public CWinApp
{
public:
	CSynapticsToolApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSynapticsToolApp theApp;