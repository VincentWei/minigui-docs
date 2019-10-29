/*
** $Id$
**
** Listing P2C5.1
**
** button.c: Sample program for mGNCS Programming Guide
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
#define ID_BTN1 102
#define ID_BTN5 106
#define ID_BTN6 107
#define ID_BTN7 108
#define ID_BTN8 109

// START_OF_HANDLERS
static BITMAP bmp;
static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //set image
//START_SET_IMAGE
    if(LoadBitmapFromFile(HDC_SCREEN, &bmp, "icon_button.png")!=0)
    {
        printf("cannot load image file \"icon_button.png\"\n");
    }
    
    mButton *mb1 = (mButton*)ncsGetChildObj(self->hwnd, ID_BTN1);

    if(mb1)
        _c(mb1)->setProperty(mb1, NCSP_BUTTON_IMAGE, (DWORD)&bmp);
//END_STE_IMAGE
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
    {"fashion","fashion", btn_rdr_elements}
};
// END_OF_RDRINFO

// START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] = {
//START_DCL_DEF_PUSHBUTTON
    {
        NCSCTRL_BUTTON, 
        ID_BTN,
        30, 30, 80, 25,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "button",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
//END_DCL_DEF_PUSHBUTTON
//START_DCL_IMAGEBUTTON
    {
        NCSCTRL_BUTTON, 
        ID_BTN1,
        150, 30, 80, 25,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_NONE,
        "Image",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
//END_DCL_IMAGEBUTTON
//START_DCL_AUTOCHECKBTN
    {
        NCSCTRL_BUTTON, 
        ID_BTN1,
        30, 80, 80, 25,
        WS_VISIBLE  | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE,
        WS_EX_NONE,
        "Auto button",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
//END_DCL_AUTOCHECKBTN
//START_DCL_3DAUTOCHECKBTN
    {
        NCSCTRL_BUTTON, 
        ID_BTN1,
        150, 80, 80, 25,
        WS_VISIBLE | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE \
            | NCSS_BUTTON_3DCHECK,
        WS_EX_NONE,
        "3D button",
        NULL,         //props,
        btn_rdr_info, //rdr_info
        NULL,         //handlers,
        NULL,         //controls
        0,
        0             //add data
    },
//END_DCL_3DAUTOCHECKBTN
};

static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_MAINWND, 
    1,
    0, 0, 260, 180,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Push Button",
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

