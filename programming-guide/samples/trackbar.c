#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_TRB1     101
#define ID_TRB2     102
#define ID_RECT        200

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

static NCS_PROP_ENTRY trk_props [] = {
    {NCSP_TRKBAR_MINPOS, 0},
    {NCSP_TRKBAR_MAXPOS, 25},
    {NCSP_TRKBAR_CURPOS, 0},
    {NCSP_TRKBAR_LINESTEP, 5},
    {NCSP_TRKBAR_PAGESTEP, 5},
    {0, 0}
};

static void trackbar_notify(mTrackBar* self, int id, int code, DWORD add_data)
{
    mRectangle *rect = (mRectangle*)ncsGetChildObj(GetParent(self->hwnd), ID_RECT);

    if(rect)
    {
        DWORD fill_color = _c(rect)->getProperty(rect, NCSP_RECTANGLE_FILLCOLOR);
        int r = GetRValue(fill_color);
        int g = GetGValue(fill_color);
        int b = GetBValue(fill_color);
        int v = _c(self)->getProperty(self, NCSP_TRKBAR_CURPOS);
        switch(id)
        {
        case ID_TRB1:
            r = 10 * v;
            break;
        case ID_TRB2:
            g = 10 * v;
            break;
        }

        fill_color = MakeRGBA(r, g, b,255);

        const RECT rc = {10, 10, 230, 230};

        _c(rect)->setProperty(rect, NCSP_RECTANGLE_FILLCOLOR, fill_color);
        InvalidateRect(rect->hwnd, &rc, TRUE);
    }
}
static NCS_RDR_INFO track_rdr_info[] =
{
    {"flat", "flat", NULL},
    //{"skin", "skin", NULL},
    //{"classic", "classic", NULL},
    //{"fashion","fashion",NULL}
};


static NCS_EVENT_HANDLER trk1_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_TRKBAR_CHANGED, trackbar_notify),
    {0, NULL}
};

static NCS_EVENT_HANDLER trk2_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_TRKBAR_CHANGED, trackbar_notify),
    {0, NULL}
};


//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_RECTANGLE,
        ID_RECT,
        10, 10, 230, 230,
        WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL, //props,
        NULL,//btn2_rdr_info, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },

    {
        NCSCTRL_TRACKBAR,
        ID_TRB1,
        10, 260, 240, 40,
        WS_BORDER | WS_VISIBLE | NCSS_TRKBAR_NOTICK | NCSS_NOTIFY ,
        WS_EX_TRANSPARENT,
        "",
        trk_props, //props,
        track_rdr_info, //rdr_info
        trk1_handlers, //handlers,
        NULL, //controls
        0,
        0, //add data
        MakeRGBA(255,0,0,255)
    },
    {
        NCSCTRL_TRACKBAR,
        ID_TRB2,
        260, 10, 40, 240,
        WS_BORDER | WS_VISIBLE | NCSS_NOTIFY | NCSS_TRKBAR_VERTICAL,
        WS_EX_NONE,
        "",
        trk_props, //props,
        track_rdr_info, //rdr_info
        trk2_handlers, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate },
    {MSG_CLOSE, mymain_onClose },
    {0, NULL }
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 320, 330,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Trackbar Test ....",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    MakeRGBA(255,255,255,255)
};

int MiniGUIMain(int argc, const char* argv[])
{
    if(argc>1)
    {
        track_rdr_info[0].glb_rdr = argv[1];
        track_rdr_info[0].ctl_rdr = argv[1];
    }


    ncsInitialize();
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);
    return 0;
}

