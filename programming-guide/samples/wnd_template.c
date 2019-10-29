/*
** $Id$
**
** Listing P2C1.3
**
** wnd_template.c: Sample program for mGNCS Programming Guide
**      Using window template.
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
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_BTN  101
#define ID_PROG 200

// START_OF_HANDLERS
static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    SetTimer (_this->hwnd, 100, 20);
    return TRUE;
}

// START_OF_ONTIMER
static void mymain_onTimer (mWidget *_this, int id, DWORD count)
{
    static int pb_pos = 0;
    mProgressBar *pb = (mProgressBar*)ncsGetChildObj (_this->hwnd, ID_PROG);
    if (pb)
        _c(pb)->setProperty(pb, NCSP_PROG_CURPOS, pb_pos++);
}
// END_OF_ONTIMER

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {MSG_TIMER, mymain_onTimer},
    {0, NULL}
};
// END_OF_HANDLERS

// START_OF_RDRINFO
static NCS_RDR_ELEMENT btn_rdr_elements[] = 
{
    { NCS_MODE_USEFLAT, 1},
    { -1, 0 }
};

static NCS_RDR_INFO btn1_rdr_info[] =
{
    {"fashion","fashion", btn_rdr_elements}
};

static NCS_RDR_INFO btn2_rdr_info[] =
{
    {"flat", "flat", NULL}
};
// END_OF_RDRINFO

// START_OF_PROPERTIES
static NCS_PROP_ENTRY progress_props [] = {
    {NCSP_PROG_MAXPOS, 100},
    {NCSP_PROG_MINPOS, 0 },
    {NCSP_PROG_LINESTEP, 1},
    {NCSP_PROG_CURPOS, 0 },
    { 0, 0 }
};
// END_OF_PROPERTIES

// START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_PROGRESSBAR, 
        ID_PROG,
        10, 10, 290, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "",
        progress_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON, 
        ID_BTN,
        10, 50, 100, 25,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "button1",
        NULL,
        btn1_rdr_info,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON, 
        ID_BTN,
        200, 50, 100, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "button2",
        NULL,
        btn2_rdr_info,
        NULL, NULL, 0, 0
    },
    
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX, 
    1,
    0, 0, 320, 110,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Window Template",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};
// END_OF_TEMPLATE

int MiniGUIMain (int argc, const char* argv[])
{
    ncsInitialize ();

    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal (mydlg, TRUE);
 
    ncsUninitialize ();

    return 0;
}

