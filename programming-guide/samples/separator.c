/*
 * ** separator.c: Sample program for mGNCS Programming Guide
 * **      A mGNCS application for mSeparator.
 * **
 * ** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <mgncs/mgncs.h>

#define ID_GROUP  101

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //TODO : initialize
    return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_SEPARATOR ,
        ID_GROUP,
        10, 10, 280, 5,
        WS_VISIBLE,
        WS_EX_NONE,
        "groupbox",
        NULL, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_SEPARATOR ,
        ID_GROUP,
        100, 20, 5, 200,
        WS_VISIBLE|NCSS_SPRTR_VERT,
        WS_EX_NONE,
        "groupbox",
        NULL, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate },
    {MSG_CLOSE, mymain_onClose },
    {0, NULL }
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 320, 240,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Separator Test ....",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);


    MainWindowThreadCleanup(mydlg->hwnd);
    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

