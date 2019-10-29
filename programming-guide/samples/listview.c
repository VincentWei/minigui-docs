/**
 * listview.c: Sample program for mGNCS Programming Guide
 *      The demo application for ListView.
 *
 * Copyright (C) 2009 ~ 2019 FMSoft Technologies.
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

#define IDC_LISTVIEW    100
#define IDC_BTN1        101
#define IDC_SLEDIT      102

#define COL_NR       TABLESIZE(caption)
#define SCORE_NUM    TABLESIZE(scores)
#define CLASS_NUM    TABLESIZE(classes)
#define SUB_NUM      3

typedef struct _SCORE
{
    char *name;
    int scr[SUB_NUM];
} SCORE;
static char * caption [] =
{
    "Name", "Chinese", "Math", "English"
};

static char *classes [] =
{
    "Grade 1", "Grade 3", "Grade 2"
};

static SCORE scores[] =
{
    {"Tom",     {81, 96, 75}},
    {"Jack",    {98, 62, 84}},
    {"Merry",   {79, 88, 89}},
    {"Bob",     {79, 88, 89}},
};

static NCS_RDR_INFO rdr_info = {
    "classic","classic",NULL
};

static void btn_notify(mWidget *button, int id, int nc, DWORD add_data)
{
    mListView *lstvObj;
    mSlEdit *sleObj;
    HITEM   gradeItem, hItem;
    int     i, j, score;
    float   average = 0;
    char    buff[20];

    lstvObj = (mListView *)ncsGetChildObj(GetParent(button->hwnd), IDC_LISTVIEW);
    sleObj    = (mSlEdit *)ncsGetChildObj(GetParent(button->hwnd), IDC_SLEDIT);
    if (!lstvObj)
        return;


    gradeItem = _c(lstvObj)->getChildItem(lstvObj, 0, 0);
    for (i = 0; i < SCORE_NUM; i++) {
        hItem = _c(lstvObj)->getChildItem(lstvObj, gradeItem, i);

        for (j = 0; j < SUB_NUM; j++) {
            sscanf(_c(lstvObj)->getItemText(lstvObj, hItem, 0, j+1), "%d", &score);
            average += score;
        }
    }
    average = average / (SCORE_NUM * SUB_NUM);

    sprintf (buff, "%4.1f", average);

    _c(sleObj)->setContent(sleObj, buff, 0, strlen(buff));
}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, btn_notify),
    {0, NULL}
};

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
    {
        NCSCTRL_LISTVIEW,
        IDC_LISTVIEW,
        10, 10, 320, 220,
        WS_BORDER | WS_VISIBLE | NCSS_LISTV_SORT | NCSS_LISTV_LOOP,
        WS_EX_NONE,
        "score table",
        NULL,
        &rdr_info,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN1,
        240, 255, 80, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "everage score",
        NULL,
        NULL,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_SLEDIT,
        IDC_SLEDIT,
        100, 256, 80, 28,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
};

static NCS_EVENT_HANDLER mainwnd_handlers[] = {
    {0, NULL}
};

static NCS_MNWND_TEMPLATE mainwnd_tmpl = {
    NCSCTRL_DIALOGBOX,
    7,
    0, 0, 350, 340,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "ListView Demo",
    NULL,
    &rdr_info,
    mainwnd_handlers,
    _ctrl_tmpl,
    sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

static HITEM add_class_item (mListView *self, NCS_LISTV_ITEMINFO *info)
{
// START_OF_ADDITEMS
    NCS_LISTV_ITEMDATA subdata;
    HITEM   hItem;

    subdata.row = info->index;
    subdata.col = 0;
    subdata.text= classes[info->index];
    subdata.textColor = 0;
    subdata.flags = 0;
    subdata.image = 0;

    info->dataSize = 1;
    info->data = &subdata;

    hItem = _c(self)->addItem (self, info);
// END_OF_ADDITEMS

    return hItem;
}

static HITEM add_score_item (mListView *self, NCS_LISTV_ITEMINFO *info)
{
    char    buff[3][20];
    HITEM   hItem;
    int     i = info->index, j;

// START_OF_ADDSUBITEMS
    NCS_LISTV_ITEMDATA subdata[4];

    for (j = 0; j < SCORE_NUM; j ++) {
        subdata[j].flags = 0;
        subdata[j].image = 0;
        subdata[j].row = info->index;
        subdata[j].col = j;
        if (j == 0) {
            subdata[j].text = scores[i].name;
            subdata[j].textColor = 0;
        }
        else {
            sprintf (buff[j-1], "%d", scores[i].scr[j-1]);
            subdata[j].text = buff[j-1];
            if (scores[i].scr[j-1] > 90)
                subdata[j].textColor = 0x0000FF;
            else
                subdata[j].textColor = 0;
        }
    }

    info->dataSize = SCORE_NUM;
    info->data = subdata;

    hItem = _c(self)->addItem (self, info);
// END_OF_ADDSUBITEMS

    if (!hItem)
        return 0;

    return hItem;
}

static BOOL lstv_init(mDialogBox* self)
{
    int     i, j;
    int     color;
    HITEM   hItem = 0, subItem;
    HWND    lstvWnd = GetDlgItem (self->hwnd, IDC_LISTVIEW);
    mListView *lstvObj;
    NCS_LISTV_ITEMINFO  info;
    NCS_LISTV_CLMINFO   lstv_clminfo;

    lstvObj = (mListView*)ncsObjFromHandle(lstvWnd);

    if (!lstvObj)
        return FALSE;

    _c(lstvObj)->freeze(lstvObj, TRUE);
    //add column

// START_OF_ADDCLMS
    for (i = 0; i < COL_NR; i++) {
        lstv_clminfo.index  = i;
        lstv_clminfo.text   = caption[i];
        lstv_clminfo.width  = 74;
        lstv_clminfo.pfnCmp = NULL;
        lstv_clminfo.flags  = NCSF_LSTCLM_CENTERALIGN | NCSF_LSTHDR_CENTERALIGN;
        _c(lstvObj)->addColumn(lstvObj, &lstv_clminfo);
    }
// END_OF_ADDCLMS

    info.height     = 25;
    info.flags      = 0;
    info.foldIcon   = 0;
    info.unfoldIcon = 0;
    for (i = 0; i < CLASS_NUM; i++) {
        info.parent = 0;
        info.index = i;
        hItem = add_class_item (lstvObj, &info);

        for (j = 0; j < SCORE_NUM; j++) {
            info.parent = hItem;
            info.index = j;
            subItem = add_score_item (lstvObj, &info);
        }

    }

// START_OF_SETBGCLR
    color = 0xFFFF00;
    _c(lstvObj)->setBackground(lstvObj, 1, 1, &color);
    color = 0xFF0000;
    _c(lstvObj)->setBackground(lstvObj, 3, 2, &color);
    color = 0x007777;
    _c(lstvObj)->setBackground(lstvObj, 5, -1, &color);
// END_OF_SETBGCLR

    _c(lstvObj)->freeze(lstvObj, FALSE);

    return TRUE;
}

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();
    mDialogBox* dialog =
        (mDialogBox *)ncsCreateMainWindowIndirect (&mainwnd_tmpl, HWND_DESKTOP);

    lstv_init(dialog);
    _c(dialog)->doModal(dialog, TRUE);

    MainWindowThreadCleanup(dialog->hwnd);
    ncsUninitialize();

    return 0;
}
