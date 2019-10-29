/*
** $Id$
**
** Listing P2C1.1
**
** helloworld.c: Sample program for mGNCS Programming Guide
**      The first mGNCS application.
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

// START_OF_HANDLERS
static void mymain_onPaint (mWidget *_this, HDC hdc, const CLIPRGN* inv)
{
    RECT rt;
    GetClientRect (_this->hwnd, &rt);
    DrawText (hdc, "Hello, world!", -1, &rt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}

static BOOL mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    return TRUE;
}

static NCS_EVENT_HANDLER mymain_handlers [] = {
    {MSG_PAINT, mymain_onPaint},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};
// END_OF_HANDLERS

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;

    ncsInitialize ();
    
    mWidget* mymain = ncsCreateMainWindow (
        NCSCTRL_MAINWND, "Hello, world!",
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        1, 
        0, 0, 300,200,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        mymain_handlers,
        0);
    
// START_OF_MSGLOOP
    while (GetMessage (&Msg, mymain->hwnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }
// END_OF_MSGLOOP
    
    MainWindowThreadCleanup (mymain->hwnd);
    
    ncsUninitialize ();

    return 0;
}

