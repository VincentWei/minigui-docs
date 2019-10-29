/*
** $Id: resmgr_main.c 534 2009-09-22 05:37:46Z xwyan $
**
** Listing P2C2.2
**
** resmgr_main.c: Sample program for mGNCS Programming Guide
**      The application entry of resource managerment.
**
** Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>

#include "resource.h"
#include "ncs-windows.h"

HPACKAGE hPackage = HPACKAGE_NULL;

int MiniGUIMain(int argc, const char* argv[])
{
#ifdef ntStartWindowEx
	MSG Msg;
	char f_package[MAX_PATH];
	mMainWnd *mWin;

	ncsInitialize();
// START_OF_LOADRESPKG
	sprintf(f_package, "%s", "resmgr_demo.res");
	SetResPath("./");

	hPackage = ncsLoadResPackage (f_package);
	if (hPackage == HPACKAGE_NULL) {
		printf ("load resource package:%s failure.\n", f_package);
		return 1;
	}
// END_OF_LOADRESPKG

// START_OF_GETSTRING
	SetDefaultWindowElementRenderer(ncsGetString(hPackage, NCSRM_SYSSTR_DEFRDR));
// END_OF_GETSTRING

	mWin = ntStartWindowEx(hPackage, HWND_DESKTOP, (HICON)0, (HMENU)0, (DWORD)0);

	while(GetMessage(&Msg, mWin->hwnd))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(mWin->hwnd);
// START_OF_UNLOADPKG
	ncsUnloadResPackage(hPackage);
// END_OF_UNLOADPKG
	ncsUninitialize();
#endif

	return 0;
}
