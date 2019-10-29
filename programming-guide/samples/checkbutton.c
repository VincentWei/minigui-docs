/*
** $Id$
**
** Listing P2C5.2
**
** checkbutton.c: Sample program for mGNCS Programming Guide
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
static BOOL mymain_onCreate(mWidget* _this, DWORD add_data)
{
    return TRUE;
}

static void mymain_onClose(mWidget* _this, int message)
{
    DestroyMainWindow(_this->hwnd);
    PostQuitMessage(0);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};
// END_OF_HANDLERS

// START_OF_RDRINFO
NCS_RDR_ELEMENT btn_rdr_elements[] = 
{
    { NCS_MODE_USEFLAT, 1},
    { -1, 0 }
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"flat","flat", btn_rdr_elements}
};
// END_OF_RDRINFO

// START_OF_TEMPLATE
#define ID_BTN  101
#define ID_BTN1 102
#define ID_BTN2 103
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_CHECKBUTTON, 
        ID_BTN,
        20, 30, 120, 25,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "option1",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
    {
        NCSCTRL_CHECKBUTTON, 
        ID_BTN1,
        20, 60, 120, 25,
        WS_BORDER | WS_VISIBLE | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "option2",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
    {
        NCSCTRL_CHECKBUTTON, 
        ID_BTN2,
        20, 90, 120, 25,
        WS_BORDER | WS_VISIBLE |NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_3DCHECK,
        WS_EX_NONE,
        "option3",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    }
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX, 
    1,
    0, 0, 260, 180,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Check button",
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

    ncsUninitialize ();

    return 0;
}

