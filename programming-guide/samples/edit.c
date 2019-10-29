/*
** $Id$
**
** Listing P2C1.12
**
** edit.c: Sample program for mGNCS Programming Guide
**      Using edit.
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
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_NAME     104
#define ID_COUN     105
#define ID_CITY     106
#define ID_PSWD     107
#define ID_SPIN     108
#define ID_INFO     109

#define ID_REG      155
#define ID_CAN      156


static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    return TRUE;
}

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE,  mymain_onClose},
    {0, NULL}
};

static void btn_onClicked(mWidget* _this, int id, int nc, HWND hCtrl)
{
    if(nc == NCSN_WIDGET_CLICKED)
    {
        if (id == ID_CAN){
            PostMessage(GetParent(_this->hwnd), MSG_CLOSE, 0, 0);
        } else if (id == ID_REG){
            //TODO
        }

    }
};

static NCS_EVENT_HANDLER btn_handlers[] = 
{
    {NCS_NOTIFY_CODE(NCSN_WIDGET_CLICKED), btn_onClicked},
    {0, NULL}
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"fashion","fashion", NULL}
};

static NCS_PROP_ENTRY static_props[] =
{
    {NCSP_STATIC_ALIGN, NCS_ALIGN_RIGHT},
    {0, 0}
};

static NCS_PROP_ENTRY spin_props [] = 
{
	{NCSP_SPNBOX_MAXPOS, 99},
	{NCSP_SPNBOX_MINPOS, 0},
	{NCSP_SPNBOX_CURPOS, 25},
	{NCSP_SPNBOX_LINESTEP, 1},
	{0, 0}
};

#define HSTART  25
#define HSPACE  40

static NCS_WND_TEMPLATE _ctrl_templ[] = 
{
//START_OF_SLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Name :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //左对齐
        NCSCTRL_SLEDIT, 
        ID_NAME,
        100, HSTART, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LEFT,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART + HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Age :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SPINBOX, 
        ID_SPIN,
        100, HSTART + HSPACE, 70, 25,
        WS_VISIBLE | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_AUTOLOOP,
        WS_EX_NONE,
        "",
        spin_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART + 2 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Country:",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //居中对齐， 大写字母
        NCSCTRL_SLEDIT, 
        ID_COUN,
        100, HSTART + 2 * HSPACE, 130, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_CENTER | NCSS_EDIT_UPPERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART + 3 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "City :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //小写字母
        NCSCTRL_SLEDIT, 
        ID_CITY,
        100, HSTART + 3 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LOWERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART + 4 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Passwd :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //密码输入形式的edit
        NCSCTRL_SLEDIT, 
        ID_PSWD,
        100, HSTART + 4 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_SLEDIT_PASSWORD,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_SLEDIT_TEMPLATE
//START_OF_MLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC, 
        0,
        10, HSTART + 5 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Info :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //多行编辑框
        NCSCTRL_MLEDIT, 
        ID_INFO,
        100, HSTART + 5 * HSPACE, 200, 160,
        WS_BORDER | WS_VISIBLE | WS_VSCROLL | NCSS_EDIT_BASELINE, 
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_MLEDIT_TEMPLATE

    {
        NCSCTRL_BUTTON, 
        ID_REG,
        240, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Register",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON, 
        ID_CAN,
        120, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Cancel",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
};

static NCS_MNWND_TEMPLATE mymain_templ =
{
    NCSCTRL_DIALOGBOX, 
    1,
    0, 0, 360, 480,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Register",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain (int argc, const char* argv[])
{
    ncsInitialize ();

    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal (mydlg, TRUE);
 
    ncsUninitialize ();

    return 0;
}

