/*
** $Id$
**
** Listing P2C5.3
**
** radiogroup.c: Sample program for mGNCS Programming Guide
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

#define ID_GROUP 200
#define ID_BTN1  101
#define ID_BTN2  102

// START_OF_HANDLERS
static BOOL mymain_onRadioChanged(mMainWnd* self, mButtonGroup* sender, 
                                  int event_id, DWORD param)
{
    mWidget* sel = (mWidget*)_c(sender)->getProperty(sender, NCSP_BTNGRP_SELOBJ);

    if(sel)
    {
        MessageBox(self->hwnd, (const char*)_c(sel)->getProperty(sel, 
            NCSP_WIDGET_TEXT), "Info", 0);
    }

    return TRUE;
}

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //connect
    ncsAddEventListener((mObject*)(_c(self)->getChild(self, ID_GROUP)), 
        (mObject*)self, (NCS_CB_ONOBJEVENT)mymain_onRadioChanged, 
        NCSN_BTNGRP_SELCHANGED);
    return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE,mymain_onCreate},
    {MSG_CLOSE,mymain_onClose},
    {0, NULL}
};
// END_OF_HANDLERS

// START_OF_RDRINFO
static NCS_RDR_INFO btn_rdr_info[] =
{
    {"skin", "skin", NULL},
};
// END_OF_RDRINFO

// START_OF_TEMPLATE
static NCS_PROP_ENTRY radioGroup_props [] = {
    {NCSP_BUTTON_GROUPID, 200},
    {0, 0}
};

static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_BUTTONGROUP , 
        ID_GROUP,
        5, 10, 200, 120,
        WS_VISIBLE|NCSS_NOTIFY,
        WS_EX_NONE,
        "Button Group",
        NULL,          //props,
        btn_rdr_info,  //rdr_info
        NULL,          //handlers,
        NULL,          //controls
        0,
        0              //add data
    },
    {
        NCSCTRL_RADIOBUTTON, 
        ID_BTN1,
        20, 30, 80, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "option1",
        radioGroup_props, //props,
        btn_rdr_info,     //rdr_info
        NULL,             //handlers,
        NULL,             //controls
        0,
        0                 //add data
    },
    {
        NCSCTRL_RADIOBUTTON, 
        ID_BTN2,
        20, 60, 80, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "option2",
        radioGroup_props, //props,
        btn_rdr_info,     //rdr_info
        NULL,             //handlers,
        NULL,             //controls
        0,
        0                 //add data
    },
    {
        NCSCTRL_RADIOBUTTON, 
        ID_BTN2,
        20, 90, 80, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "option3",
        radioGroup_props, //props,
        btn_rdr_info,     //rdr_info
        NULL,             //handlers,
        NULL,             //controls
        0,
        0                 //add data
    },
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX, 
    1,
    0, 0, 260, 180,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Radio button",
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

