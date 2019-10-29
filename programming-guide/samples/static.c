/*
 * ** static.c: Sample program for mGNCS Programming Guide
 * **      A mGNCS application for mStatic.
 * **
 * ** Copyright (C) 2009 FMSoft Technologies.
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

#define IDC_STATIC1 100
#define IDC_SATAICN 107

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


//Propties for
static NCS_PROP_ENTRY static1_props [] = {
    { NCSP_STATIC_ALIGN, NCS_ALIGN_CENTER },
    {0, 0}
};
static NCS_PROP_ENTRY static2_props [] = {
    { NCSP_STATIC_ALIGN, NCS_ALIGN_RIGHT },
    {0, 0}
};
static NCS_PROP_ENTRY static4_props [] = {
    { NCSP_STATIC_VALIGN, NCS_VALIGN_TOP },
    {0, 0}
};

static NCS_PROP_ENTRY static5_props [] = {
    { NCSP_STATIC_VALIGN, NCS_VALIGN_BOTTOM },
    {0, 0}
};

static NCS_PROP_ENTRY static6_props [] = {
    { NCSP_STATIC_AUTOWRAP, 0 },
    {0, 0}
};


//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+0,
        10, 10, 160, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Default Text",
        NULL, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+1,
        10, 50, 160, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Center Text",
        static1_props, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+2,
        10, 90, 160, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Right Text",
        static2_props, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+3,
        220, 10, 80, 120,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Defalut VCenter ",
        NULL, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+4,
        315, 10, 70, 120,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Top Text",
        static4_props, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+5,
        400, 10, 70, 120,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "Bottom Text",
        static5_props, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC ,
        IDC_STATIC1+6,
        10, 160, 220, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "This static control shows the Single Line Text",
        static6_props, //props,
        NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },

};


static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 480, 270,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "static Test ....",
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

