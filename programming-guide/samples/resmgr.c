/*
** $Id: resmgr.c 534 2009-09-22 05:37:46Z xwyan $
**
** Listing P2C2.3
**
** resmgr.c: Sample program for mGNCS Programming Guide
**      Create main window by resource managerment.
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

static NCS_EVENT_HANDLER_INFO mainwnd_Mainwnd1_handlers[] = {

	{-1, NULL}
};

NCS_WND_EXPORT mMainWnd* ntCreateMainwnd1Ex(HPACKAGE package, HWND hParent, HICON h_icon, HMENU h_menu, DWORD user_data)
{
// START_OF_UIWINDOW
	return ncsCreateMainWindowIndirectFromID(package,
		ID_MAINWND1, 
		hParent,
		h_icon,
		h_menu,
		mainwnd_Mainwnd1_handlers,
		NULL,
		user_data);
// END_OF_UIWINDOW
}
