/**
 * $Id: listbox.c 595 2009-10-10 08:19:47Z xwyan $
 *
 * listbox.c: Sample program for mGNCS Programming Guide
 *      The demo application for ListBox.
 *
 * Copyright (C) 2009 FMSoft Technologies.
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

#define IDC_LIST    100
#define IDC_DELETE  200

static char* items[] = {
    "Apples",
    "Apricots",
    "Bananas",
    "Grapefruit",
    "Kiwi",
    "Oranges",
    "Peaches",
    "The Longest String"
};

static void lstbox_init(mDialogBox *dialog)
{
    NCS_LSTBOX_ITEMINFO iteminfo;
    mListBox *lstboxObj;
    int i;

    lstboxObj = (mListBox *)ncsGetChildObj(dialog->hwnd, IDC_LIST);

// START_OF_ADDITEMS
    iteminfo.flag = NCSF_LSTBOX_CMBLANK;
    iteminfo.image = 0;
    for (i = 0; i < TABLESIZE(items); i++) {
        iteminfo.string = items[i];
        _c(lstboxObj)->addString (lstboxObj, &iteminfo);
    }
// END_OF_ADDITEMS
}

// START_OF_BTNHANDLERS
static void btn_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    mListBox    *lstboxObj =
        (mListBox *)ncsGetChildObj(GetParent(self->hwnd), IDC_LIST);
// START_OF_DELITEMS
    int sel     = _c(lstboxObj)->getCurSel(lstboxObj);
    int count   = _c(lstboxObj)->getItemCount(lstboxObj);

    if (sel >= 0) {
        _c(lstboxObj)->delString(lstboxObj, sel);

        if (sel == count -1)
            sel --;

        _c(lstboxObj)->setCurSel(lstboxObj, sel);
    }
// END_OF_DELITEMS
}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
    {0, NULL}
};
// END_OF_BTNHANDLERS
static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
    {
        NCSCTRL_LISTBOX,
        IDC_LIST,
        20, 15, 170, 200,
        WS_BORDER | WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_DELETE,
        15, 230, 80, 30,
        WS_VISIBLE | WS_TABSTOP,
        WS_EX_NONE,
        "Delete",
        NULL,
        NULL,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDCANCEL,
        115, 230, 80, 30,
        WS_VISIBLE | WS_TABSTOP,
        WS_EX_NONE,
        "Cancel",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
};


static NCS_MNWND_TEMPLATE mainwnd_tmpl = {
    NCSCTRL_DIALOGBOX,
    1,
    100, 100, 220, 300,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "ListBox Demo",
    NULL,
    NULL,
    NULL,
    _ctrl_tmpl,
    sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();

    mDialogBox* dialog =
        (mDialogBox *)ncsCreateMainWindowIndirect (&mainwnd_tmpl, HWND_DESKTOP);

    lstbox_init(dialog);
    _c(dialog)->doModal(dialog, TRUE);

    MainWindowThreadCleanup(dialog->hwnd);
    ncsUninitialize();
    return 0;
}
