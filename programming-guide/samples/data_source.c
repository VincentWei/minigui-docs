/*
** data_source.c: Sample program for mGNCS Programming Guide
**      Using static data source.
**
** Copyright (C) 2009 FMSoft Technologies.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>

#define IDC_LISTVIEW 100

// START_OF_DEFINEDS
static const NCS_LISTV_CLMRD _header[] = {
    {"Name", "", 100, NCSF_LSTCLM_LEFTALIGN},
    {"Sex", "", 80, NCSF_LSTCLM_LEFTALIGN},
    {"Age", "", 80, NCSF_LSTCLM_LEFTALIGN}
};

static const char* _content[][3] = {
    {"Jime", "Male", "15"},
    {"Lily", "Female", "12"},
    {"Tom", "Male", "11"}
};
// END_OF_DEFINEDS

// START_OF_SETDATA
static BOOL mymain_onCreate (mWidget* self, DWORD add_data)
{
    mListView *lv = (mListView*)_c(self)->getChild (self, IDC_LISTVIEW);

    if (lv) {
        mRecordSet *rs;
        rs = _c(g_pStaticDS)->selectRecordSet (g_pStaticDS, 
                    "/listview/header", NCS_DS_SELECT_READ);
        _c(lv)->setSpecial (lv, NCSID_LISTV_HDR, (DWORD)rs, NULL);
        rs = _c(g_pStaticDS)->selectRecordSet (g_pStaticDS, 
                    "/listview/content", NCS_DS_SELECT_READ);
        _c(lv)->setSpecial (lv, NCS_CONTENT, (DWORD)rs, NULL);
    }
    
    return TRUE;
}
// END_OF_SETDATA

static void mymain_onClose (mWidget* self, int message)
{
    DestroyMainWindow (self->hwnd);
    PostQuitMessage (self->hwnd);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};

static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_LISTVIEW, 
        IDC_LISTVIEW,
        10, 10, 320, 190,
        WS_BORDER | WS_VISIBLE | NCSS_LISTV_SORT 
            | NCSS_LISTV_LOOP,
        WS_EX_NONE,
        "",
        NULL, NULL, NULL, NULL, 0, 0
    }
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_MAINWND, 
    1,
    0, 0, 350, 240,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Data Source ....",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0, 0, 0,
};

int MiniGUIMain (int argc, const  char* argv[])
{
    mDialogBox* mydlg;

    ncsInitialize ();

// START_OF_REGDS
    ncsRegisterStaticData ("/listview/header", (void*)_header, 3, 
            sizeof(NCS_LISTV_CLMRD)/sizeof(DWORD), sizeof(DWORD), 
            gListVColumnRecordTypes);
    ncsRegisterStaticData ("/listview/content", (void*)_content, 3,  
            3, sizeof(char*), NULL);
// END_OF_REGDS

    mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
                                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal (mydlg, TRUE);

    MainWindowThreadCleanup (mydlg->hwnd);

    ncsUninitialize ();

    return 0;
}

