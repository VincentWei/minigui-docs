#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_SPINNER1      101
#define ID_SHOWSPINNER1  201
#define ID_SPINNER2      102
#define ID_SHOWSPINNER2  202

#define MINVALUE        0
#define MAXVALUE        10
#define CURVALUE        5

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //START_GET_CTRLS
    mSpinner * spn1, *spn2;
    mStatic  * show1, * show2;
    spn1 = (mSpinner*)_c(self)->getChild(self, ID_SPINNER1);
    spn2 = (mSpinner*)_c(self)->getChild(self, ID_SPINNER2);
    show1 = (mStatic*)_c(self)->getChild(self, ID_SHOWSPINNER1);
    show2 = (mStatic*)_c(self)->getChild(self, ID_SHOWSPINNER2);
    //END_GET_CTRLS

    //START_CONNECT_PROPS
    ncsConnectBindProps(
        NCS_CMPT_PROP(spn1, NCSN_SPNR_CHANGED, NCSP_SPNR_CURPOS, NCS_BT_INT, NCS_PROP_FLAG_READ),
        NCS_CMPT_PROP(show1, 0, NCSP_WIDGET_TEXT, NCS_BT_STR, NCS_PROP_FLAG_WRITE),
        NCS_BPT_SIGNALE);

    ncsConnectBindProps(
        NCS_CMPT_PROP(spn2, NCSN_SPNR_CHANGED, NCSP_SPNR_CURPOS, NCS_BT_INT, NCS_PROP_FLAG_READ),
        NCS_CMPT_PROP(show2, 0, NCSP_WIDGET_TEXT, NCS_BT_STR, NCS_PROP_FLAG_WRITE),
        NCS_BPT_SIGNALE);
    //END_CONNECT_PROPS

    //START_UPDATE_CTRLS
    ncsRaiseComponentBindProps((mComponent*)spn1, NCSN_SPNR_CHANGED);
    ncsRaiseComponentBindProps((mComponent*)spn2, NCSN_SPNR_CHANGED);
    //END_UPDATE_CTRLS


    return TRUE;
}

static void mymain_onClose (mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

//START_SET_PROPS
//Propties for
static NCS_PROP_ENTRY spinbox_props [] = {
    {NCSP_SPNR_MINPOS, MINVALUE},
    {NCSP_SPNR_MAXPOS, MAXVALUE},
    {NCSP_SPNR_CURPOS, CURVALUE},
    {NCSP_SPNR_LINESTEP, 1},
    {0, 0}
};
//END_SET_PROPS

static NCS_RDR_INFO spin_rdr_info[] =
{
    {"skin", "skin", NULL},
    //{"fashion", "fashion", NULL},
    //{"flat", "flat", NULL},
};

//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_STATIC,
        ID_SHOWSPINNER1,
        100,40, 100,20,
        WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_SPINNER ,
        ID_SPINNER1,
        30, 40, 20, 20,
        WS_VISIBLE | NCSS_SPNBOX_VERTICAL | NCSS_NOTIFY,
        WS_EX_NONE,
        "spinbox",
        spinbox_props, //props,
        spin_rdr_info, //NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_STATIC,
        ID_SHOWSPINNER2,
        100, 100, 100, 20,
        WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        0,
        0
    },

    {
        NCSCTRL_SPINNER ,
        ID_SPINNER2,
        30, 100, 20, 20,
        WS_VISIBLE | NCSS_SPNBOX_HORIZONTAL | NCSS_NOTIFY,
        WS_EX_NONE,
        "spinbox",
        spinbox_props, //props,
        spin_rdr_info, //NULL, //rdr_info
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    }
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE,mymain_onCreate},
    {MSG_CLOSE,mymain_onClose},
    {0, NULL}
};

static NCS_RDR_INFO mymain_rdr_info[] =
{
    {"skin", "skin", NULL},
};


//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 260, 200,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Spinner Test ....",
    NULL,
    mymain_rdr_info,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
    if(argc>1)
    {
        spin_rdr_info[0].glb_rdr = argv[1];
        spin_rdr_info[0].ctl_rdr = argv[1];
    }


    ncsInitialize();
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);
    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

