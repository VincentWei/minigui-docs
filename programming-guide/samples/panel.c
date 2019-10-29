/*
** $Id: panel.c 594 2009-10-10 05:59:06Z xwyan $
**
** Listing P2C6.1
**
** panel.c: Sample program for mGNCS Programming Guide
**      The demo application for Panel.
**
** Copyright (C) 2009 Feynman Software.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define     ID_PANEL_GROUP1     101
#define     ID_PANEL_GROUP2     102

#define     ID_RED1             201
#define     ID_RED2             202
#define     ID_BLUE1            301
#define     ID_BLUE2            302

// START_OF_REDGROUP
static NCS_WND_TEMPLATE _ctrl_group1[] = {
	{
		NCSCTRL_BUTTON, 
		ID_RED1,
		30, 40, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"RED 1",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
	{
		NCSCTRL_BUTTON, 
		ID_RED2,
		30, 110, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"RED 2",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
};
// END_OF_REDGROUP

// START_OF_BLUEGROUP
static NCS_WND_TEMPLATE _ctrl_group2[] = {
	{
		NCSCTRL_BUTTON, 
		ID_BLUE1,
		30, 40, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"BLUE 1",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
	{
		NCSCTRL_BUTTON, 
		ID_BLUE2,
		30, 110, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"BLUE 2",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
};
// END_OF_BLUEGROUP

// START_OF_PANEL
static NCS_WND_TEMPLATE panel_tmpl[] = {
	{
		NCSCTRL_PANEL, 
		ID_PANEL_GROUP1,
		10, 10, 140, 180,
		WS_VISIBLE,
		WS_EX_NONE,
		"Red Group",
		NULL,
		NULL,
		NULL,
		_ctrl_group1, 
		sizeof(_ctrl_group1)/sizeof(NCS_WND_TEMPLATE),
		0,
        0xFF0000FF,
	},
	{
		NCSCTRL_PANEL, 
		ID_PANEL_GROUP2,
		160, 10, 140, 180,
		WS_VISIBLE,
		WS_EX_NONE,
		"Blue Group",
		NULL,
		NULL,
		NULL,
		_ctrl_group2,
		sizeof(_ctrl_group2)/sizeof(NCS_WND_TEMPLATE), 
		0,
        0xFFFF0000,
	},
};
// END_OF_PANEL

// START_OF_HANDLERS
static BOOL mainwnd_onCreate(mWidget* self, DWORD add_data)
{
    _c(self)->addChildren(self, panel_tmpl, \
		sizeof(panel_tmpl)/sizeof(NCS_WND_TEMPLATE));
	return TRUE;
}

static void mainwnd_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}


static NCS_EVENT_HANDLER mainwnd_handlers[] = {
	{MSG_CREATE, mainwnd_onCreate},
	{MSG_CLOSE, mainwnd_onClose},
	{0, NULL}
};
// END_OF_HANDLERS

int MiniGUIMain(int argc, const char* argv[])
{
    MSG Msg;

    ncsInitialize ();

    mWidget* mainwnd = ncsCreateMainWindow (
        NCSCTRL_MAINWND, "Panel Demo",
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        1, 
        0, 0, 320,240,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        mainwnd_handlers,
        0);
    
// START_OF_MSGLOOP
    while (GetMessage (&Msg, mainwnd->hwnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }
// END_OF_MSGLOOP
    
    MainWindowThreadCleanup (mainwnd->hwnd);
    ncsUninitialize ();

    return 0;
}
