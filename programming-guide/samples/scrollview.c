/*
** scrollview.c: Sample program for mGNCS Programming Guide
**      The demo application for ScrollView.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
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

#define IDC_SCROLLVIEW  100

static const char *people[] =
{
    "cao cao",
    "sun quan",
    "liu bei",
    "zhu ge liang",
    "guan yu",
    "pang tong",
    "si ma yu",
};

static NCS_RDR_INFO rdr_info = {
    "classic","classic",NULL
};

// START_OF_HANDLERS
static void scrlv_notify (mWidget *self, int id, int nc, DWORD add_data)
{
    if (nc == NCSN_SCRLV_CLICKED)
    {
        if (self) {
            const char* info;
            mIconView *cls = (mIconView*)self;

            info = (const char*)_c(cls)->getAddData(cls, (HITEM)add_data);

            fprintf (stderr, "current item's data %s \n", info);
        }
    }
}

static NCS_EVENT_HANDLER scrlv_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_SCRLV_CLICKED, scrlv_notify),
    {0, NULL }
};
// END_OF_HANDLERS

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
    {
        NCSCTRL_SCROLLVIEW,
        IDC_SCROLLVIEW,
        10, 10, 320, 150,
        WS_BORDER | WS_VISIBLE | NCSS_NOTIFY | NCSS_SCRLV_SORT,
        WS_EX_NONE,
        "",
        NULL,
        &rdr_info,
        scrlv_handlers,
        NULL,
        0,
        0
    },
};

static BOOL dialog_onKeyDown(mWidget* self,
        int message, int code, DWORD key_status)
{
    if (message == MSG_KEYDOWN) {
        if (code == SCANCODE_REMOVE) {
            mScrollView *scrlvObj;
            int         curSel, count;
            HITEM       delItem;

            scrlvObj =
                (mScrollView*)ncsObjFromHandle(GetDlgItem(self->hwnd, IDC_SCROLLVIEW));
            count = _c(scrlvObj)->getItemCount(scrlvObj);

            if (scrlvObj) {
                curSel = _c(scrlvObj)->getCurSel(scrlvObj);

                if (curSel >= 0) {
                    delItem = _c(scrlvObj)->getItem(scrlvObj, curSel);
                    _c(scrlvObj)->removeItem(scrlvObj, delItem);
                    if (curSel == count -1)
                        curSel--;
                    _c(scrlvObj)->setCurSel(scrlvObj, curSel);
                }
            }
        }
    }
    return FALSE;
}

static NCS_EVENT_HANDLER dialog_handlers[] = {
    {MSG_KEYDOWN, dialog_onKeyDown},
    {0, NULL }
};

static NCS_MNWND_TEMPLATE dialog_tmpl = {
    NCSCTRL_DIALOGBOX,
    7,
    0, 0, 350, 200,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "ScrollView Demo",
    NULL,
    &rdr_info,
    dialog_handlers,
    _ctrl_tmpl,
    sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

// START_OF_ITEMFUNCS
static int scrlv_cmp_item (mItemManager *manager, HITEM hItem1, HITEM hItem2)
{
    mScrollView *scrlvObj = (mScrollView*)manager->obj;
    const char *name1;
    const char *name2;

    if (scrlvObj) {
        name1 = (const char*)_c(scrlvObj)->getAddData(scrlvObj, hItem1);
        name2 = (const char*)_c(scrlvObj)->getAddData(scrlvObj, hItem2);
        return strcmp (name1, name2);
    }
    return 0;
}

static void scrlv_draw_item (mItemView *self, HITEM hItem, HDC hdc, RECT *rcDraw)
{
    const char  *name = (const char*)_c(self)->getAddData(self, hItem);
    gal_pixel   oldBrushClr = 0, oldTextClr = 0;
    BOOL        isHilite = FALSE;
    int         top;
    RECT        rcText;

    SetBkMode (hdc, BM_TRANSPARENT);

    top = rcDraw->top;
    if (_c(self)->indexOf(self, hItem) > 0) {
        top --;
    }

    if (_c(self)->isHilight(self, hItem)) {
        isHilite = TRUE;
        oldBrushClr = SetBrushColor (hdc, PIXEL_blue);
        FillBox (hdc, rcDraw->left + 1,
                top + 1, RECTWP(rcDraw) - 2, RECTHP(rcDraw) - 1);
        oldTextClr = SetTextColor (hdc, PIXEL_lightwhite);
    }

    Rectangle (hdc, rcDraw->left, top, rcDraw->right - 1, rcDraw->bottom - 1);

    CopyRect(&rcText, rcDraw);
    rcText.left += 5;
    DrawText(hdc, name, -1, &rcText, DT_VCENTER | DT_SINGLELINE);

    if (isHilite) {
        SetBrushColor (hdc, oldBrushClr);
        SetTextColor (hdc, oldTextClr);
    }
}
// END_OF_ITEMFUNCS

static BOOL scrlv_init(mDialogBox* self)
{
    int     i;
    HWND    scrlvWnd;
    mScrollView *scrlvObj;
    NCS_SCRLV_ITEMINFO info;

    scrlvWnd = GetDlgItem (self->hwnd, IDC_SCROLLVIEW);
    scrlvObj = (mScrollView*)ncsObjFromHandle(scrlvWnd);

    if (!scrlvObj)
        return FALSE;

// START_OF_ADDITEMS
    _c(scrlvObj)->freeze(scrlvObj, TRUE);
    _c(scrlvObj)->setItemCmpFunc(scrlvObj, scrlv_cmp_item);
    _c(scrlvObj)->setItemDraw(scrlvObj, scrlv_draw_item);

    for (i = 0; i < TABLESIZE(people); i++) {
        info.height  = 32;
        info.index   = i;
        info.addData = (DWORD)people[i];
        _c(scrlvObj)->addItem(scrlvObj, &info, NULL);
    }
    _c(scrlvObj)->freeze(scrlvObj, FALSE);
// END_OF_ADDITEMS
    return TRUE;
}

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();
    mDialogBox* mydlg =
        (mDialogBox *)ncsCreateMainWindowIndirect (&dialog_tmpl, HWND_DESKTOP);

    scrlv_init(mydlg);
    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);
    ncsUninitialize();
    return 0;
}
