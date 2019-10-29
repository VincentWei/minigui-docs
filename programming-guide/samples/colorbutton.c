/*
** $Id$
**
** Listing P2C5.5
**
** colorbutton.c: Sample program for mGNCS Programming Guide
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

#define ID_BTN  101

// START_OF_HANDLERS
static BOOL mymain_oncolorchanged(mMainWnd* self, mColorButton *sender, 
        int id, DWORD param)
{
    SetWindowBkColor(self->hwnd, DWORD2PIXEL(HDC_SCREEN, param));
    InvalidateRect(self->hwnd, NULL, TRUE);

    return FALSE;
}

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    mColorButton *btn = (mColorButton*)_c(self)->getChild(self, ID_BTN);
    if(btn)
    {
        _c(btn)->setProperty(btn, NCSP_CLRBTN_CURCOLOR, PIXEL2DWORD(HDC_SCREEN,
            GetWindowBkColor(self->hwnd)));
        ncsAddEventListener((mObject*)btn, (mObject*)self, 
            (NCS_CB_ONPIECEEVENT)mymain_oncolorchanged, 
            NCSN_CLRBTN_COLORCHANGED);
    }
    
    return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};
// END_OF_HANDLERS

// START_OF_RDRINFO
static NCS_RDR_INFO btn_rdr_info[] =
{
      {"fashion", "fashion", NULL},
};
// END_OF_RDRINFO

// START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_COLORBUTTON, 
        ID_BTN,
        40, 40, 80, 30,
        WS_VISIBLE|NCSS_NOTIFY,
        WS_EX_NONE,
        "button",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    }
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_MAINWND, 
    1,
    0, 0, 180, 140,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Color button",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};
// END_OF_TEMPLATE

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();

    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);

    ncsUninitialize ();
 
    return 0;
}

