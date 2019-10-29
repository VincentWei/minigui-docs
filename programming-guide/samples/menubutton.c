/*
** $Id$
**
** Listing P2C5.4
**
** menubutton.c: Sample program for mGNCS Programming Guide
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
static void menubutton_onitemchanged(mMenuButton *self, int id, int nc, 
                                     DWORD add_data)
{
    char szText[100];
    sprintf(szText,"id=%d",id);
    MessageBox(self->hwnd, szText,"Menu ID",0);
}

static NCS_EVENT_HANDLER menubutton_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_MNUBTN_ITEMCHANGED, menubutton_onitemchanged),
    {0, NULL}
};

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    mPopMenuMgr * popmenu = NEW(mPopMenuMgr);

    _c(popmenu)->addItem(popmenu,0, "menuitem 1", NULL, 200, 0, NULL, 0);
    _c(popmenu)->addItem(popmenu,0, "menuitem 2", NULL, 201, 0, NULL, 0);
    _c(popmenu)->addItem(popmenu,0, "menuitem 3", NULL, 202, 0, NULL, 0);

    mButton *mb1 = (mButton*)ncsGetChildObj(self->hwnd, ID_BTN);
    if(mb1)
    {
        _c(mb1)->setProperty(mb1, NCSP_MNUBTN_POPMENU, (DWORD)popmenu);
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
NCS_RDR_ELEMENT btn_rdr_elements[] = 
{
    { NCS_MODE_USEFLAT, 1},
    { -1, 0 }
};
static NCS_RDR_INFO btn_rdr_info[] =
{
    {"skin", "skin", NULL},
};
// END_OF_RDRINFO

// START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_MENUBUTTON, 
        ID_BTN,
        40, 40, 100, 30,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "menu button",
        NULL,                //props,
        btn_rdr_info,        //rdr_info
        menubutton_handlers, //handlers,
        NULL,                //controls
        0,
        0                    //add data
    },
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX, 
    1,
    0, 0, 260, 180,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Menu button",
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

