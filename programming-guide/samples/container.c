/*
** $Id: container.c 596 2009-10-10 08:49:44Z xwyan $
**
** container.c: Sample program for mGNCS Programming Guide
**      The demo application for Container.
**
** Copyright (C) 2009 FMSoft Technologies.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define IDC_CONTAINER   100

#define IDC_RDOGROUP    151
#define IDC_CKGROUP     152

#define IDC_LAMIAN      101
#define IDC_CHOUDOUFU   102
#define IDC_JIANBING    103
#define IDC_MAHUA       104
#define IDC_SHUIJIAO    105
#define IDC_XIAN        110
#define IDC_LA          111
#define IDC_PROMPT      200

// START_OF_NCSCTRLS
static NCS_PROP_ENTRY radioGroup_props [] = {
    {NCSP_BUTTON_GROUPID, IDC_RDOGROUP},
    {0, 0}
};

static NCS_WND_TEMPLATE ncsCtrlYourTaste[] = {
    {
        NCSCTRL_BUTTONGROUP,
        IDC_RDOGROUP,
        16, 10, 230, 160,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        "optional snack",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_RADIOBUTTON,
        IDC_LAMIAN,
        36, 38, 200, 20,
        WS_VISIBLE | WS_TABSTOP | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "northwest pulled noodle",
        radioGroup_props,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_RADIOBUTTON,
        IDC_CHOUDOUFU,
        36, 64, 200, 20,
        WS_VISIBLE | WS_TABSTOP | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "chang sha bad smelling bean curd",
        radioGroup_props,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_RADIOBUTTON,
        IDC_JIANBING,
        36, 90, 200, 20,
        WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        WS_EX_NONE,
        "shan dong thini pancake",
        radioGroup_props,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_RADIOBUTTON,
        IDC_MAHUA,
        36, 116, 200, 20,
        WS_VISIBLE | WS_TABSTOP | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "tianjin fired dough twist",
        radioGroup_props,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_RADIOBUTTON,
        IDC_SHUIJIAO,
        36, 142, 200, 20,
        WS_VISIBLE | WS_TABSTOP | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "chengdu red oil boiled dumpling",
        radioGroup_props,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTONGROUP,
        IDC_CKGROUP,
        250, 10, 100, 160,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        "flavor",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_CHECKBUTTON,
        IDC_XIAN,
        260, 38, 80, 20,
        WS_VISIBLE | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "partial salty",
        //checkGroup_props,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_CHECKBUTTON,
        IDC_LA,
        260, 64, 80, 20,
        WS_VISIBLE | NCSS_BUTTON_AUTOCHECK,
        WS_EX_NONE,
        "partial spicy",
        //checkGroup_props,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_STATIC,
        IDC_PROMPT,
        16, 180, 360, 40,
        WS_VISIBLE,
        WS_EX_NONE,
        "northwest pulled noodle is competitive product in the wheaten food",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDOK,
        70, 230, 70, 30,
        WS_VISIBLE | WS_TABSTOP | NCSS_NOTIFY,
        WS_EX_NONE,
        "Ok",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDCANCEL,
        200, 230, 70, 30,
        WS_VISIBLE | WS_TABSTOP | NCSS_NOTIFY,
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
// END_OF_NCSCTRLS

// START_OF_INTRINSICCTRLS
static CTRLDATA CtrlYourTaste[] =
{
    {
        "static",
        WS_VISIBLE | SS_GROUPBOX,
        16, 10, 230, 160,
        IDC_STATIC,
        "optional snack",
        0,
        WS_EX_TRANSPARENT
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON | BS_CHECKED | WS_TABSTOP | WS_GROUP,
        36, 38, 200, 20,
        IDC_LAMIAN,
        "northwest pulled noodle",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36, 64, 200, 20,
        IDC_CHOUDOUFU,
        "chang sha bad smelling bean curd",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON | WS_DISABLED,
        36, 90, 200, 20,
        IDC_JIANBING,
        "shan dong thini pancake",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36, 116, 200, 20,
        IDC_MAHUA,
        "tianjin fired dough twist",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36, 142, 200, 20,
        IDC_SHUIJIAO,
        "chengdu red oil boiled dumpling",
        0
    },
    {
        "static",
        WS_VISIBLE | SS_GROUPBOX | WS_GROUP,
        250, 10, 100, 160,
        IDC_STATIC,
        "flavor",
        0,
        WS_EX_TRANSPARENT
    },
    {
        "button",
        WS_VISIBLE | BS_AUTOCHECKBOX,
        260, 38, 80, 20,
        IDC_XIAN,
        "partial salty",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTOCHECKBOX | BS_CHECKED,
        260, 64, 80, 20,
        IDC_LA,
        "partial spicy",
        0
    },
    {
        "static",
        WS_VISIBLE | SS_LEFT | WS_GROUP | WS_BORDER,
        16, 180, 360, 40,
        IDC_PROMPT,
        "northwest pulled noodle is competitive product in the wheaten food",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP | WS_BORDER ,
        70, 230, 70, 30,
        IDOK,
        "OK",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        200, 230, 70, 30,
        IDCANCEL,
        "Cancel",
        0
    },
};
// END_OF_INTRINSICCTRLS

// START_OF_HANDLERS
static void dialog_onCSizeChanged(mWidget* self, int clientWidth, int clientHeight)
{
    HWND hContainer = GetDlgItem(self->hwnd, IDC_CONTAINER);
    if (hContainer != HWND_NULL || hContainer != HWND_INVALID)
        MoveWindow(hContainer, 0, 0, clientWidth, clientHeight, TRUE);
}

static BOOL container_onCommand(mWidget* self, int id, int nc, HWND hCtrl)
{
    if (id == IDOK || id == IDCANCEL) {

        if (nc == NCSN_BUTTON_PUSHED) {
            //close dialog
            HWND hParent = GetParent(self->hwnd);
            SendNotifyMessage(hParent,
                    MSG_COMMAND, (WPARAM)MAKELONG(id, nc), (LPARAM)hCtrl);
        }

        return FALSE;
    }

    return FALSE;
}

static NCS_EVENT_HANDLER container_handlers[] = {
    {MSG_COMMAND, container_onCommand},
    {0, NULL}
};
// END_OF_HANDLERS

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize ();

    mDialogBox* dialog = (mDialogBox*)ncsCreateMainWindow (
        NCSCTRL_DIALOGBOX, "Container Demo",
        WS_CAPTION | WS_BORDER | WS_VISIBLE | NCSS_MNWND_MODE,
        WS_EX_NONE,
        1,
        0, 0, 400, 320,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        NULL,
        0);

    ncsSetComponentHandler((mComponent*)dialog,
            MSG_CSIZECHANGED, dialog_onCSizeChanged);

    mContainer *container =
        (mContainer*)ncsCreateWindow (NCSCTRL_CONTAINER,
                          "",
                          WS_BORDER | WS_VISIBLE,
                          WS_EX_NONE,
                          IDC_CONTAINER,
                          0, 0, 300, 200, dialog->hwnd,
                          NULL, NULL, container_handlers, 0);

    if (argc > 1 && strcmp(argv[1], "intrinsic") == 0) {
        _c(container)->addIntrinsicControls (container, CtrlYourTaste,
                sizeof(CtrlYourTaste)/sizeof(CTRLDATA));
    }
    else {
        _c(container)->addChildren(container, ncsCtrlYourTaste,
                sizeof(ncsCtrlYourTaste)/sizeof(NCS_WND_TEMPLATE));
    }

    _c(dialog)->doModal(dialog, TRUE);

    MainWindowThreadCleanup (dialog->hwnd);
    ncsUninitialize ();

    return 0;
}
